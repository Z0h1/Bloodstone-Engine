#include "DexRenderWindowD11_1.h"
#include "DexScene.h"
#include "DexSceneObject.h"
#include "DexGeometryFile.h"
#include "DexIndexBuffer.h"
#include "DexVertexBuffer.h"
#include "DexCameraComponent.h"
#include "DexRenderComponentD11_1.h"

namespace Dex
{
	RenderWindowD11_1::RenderWindowD11_1(ofstream* logger, IDXGIAdapter* adapter)
		: IRenderWindow("", logger)
	{
		m_nAdapter = adapter;
	}

	RenderWindowD11_1::~RenderWindowD11_1()
	{

	}

	bool RenderWindowD11_1::Create(const _lParametor& config)
	{
		_lParametor::const_iterator parametor;

		parametor = config.find("window_name");
		if (parametor != config.end()) {
			mObjectName = parametor->second;
		}

		HRESULT eResult = S_FALSE;

		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 1;

		parametor = config.find("display_format");
		if (parametor != config.end())
		{
			StringConverter::ParseDisplyaMode(parametor->second, m_nWidth, m_nHeight, sd.BufferDesc.RefreshRate.Numerator);
		}
		else
		{
			sd.BufferDesc.Width = m_nWidth;
			sd.BufferDesc.Height = m_nHeight;
			//sd.BufferDesc.RefreshRate.Numerator = m_nPP;
		}

		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

		parametor = config.find("window_handle");
		if (parametor != config.end())
		{
			sd.OutputWindow = (HWND)StringConverter::Parse_int(parametor->second);
		}
		else
		{
			DrawLine("RenderWindow_D11:RenderWindow_D11 \"window_handle\" не указан", MT_ERROR);
		}

		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;

		parametor = config.find("fullscrean");
		if (parametor != config.end())
		{
			m_bFullScrean = StringConverter::Parse_bool(parametor->second);
		}

		sd.Windowed = !m_bFullScrean;

		D3D_FEATURE_LEVEL eFeatureLevel;
		D3D_FEATURE_LEVEL eFeatureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1,
		};

		UINT nCreateDeviceFlags = 0;
#ifdef _DEBUG
		nCreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_DRIVER_TYPE type = D3D_DRIVER_TYPE_HARDWARE;

		parametor = config.find("device_type");
		if (parametor != config.end())
		{
			if (parametor->second == "Software")
			{
				type = D3D_DRIVER_TYPE_SOFTWARE;
			}
		}

		eResult = D3D11CreateDeviceAndSwapChain(m_nAdapter, type, NULL, nCreateDeviceFlags, eFeatureLevels, 3,
			D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pD3D11Device, &eFeatureLevel, &m_pImmediateContext);

		if (SUCCEEDED(eResult))
		{
			ID3D11Texture2D* pBackBuffer = 0;
			eResult = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

			if (SUCCEEDED(eResult))
			{
				eResult = m_pD3D11Device->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);

				if (SUCCEEDED(eResult))
				{
					m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);

					// Setup the viewport
					D3D11_VIEWPORT vp;
					vp.Width = (FLOAT)m_nWidth;
					vp.Height = (FLOAT)m_nHeight;
					vp.MinDepth = 0.0f;
					vp.MaxDepth = 1.0f;
					vp.TopLeftX = 0;
					vp.TopLeftY = 0;
					m_pImmediateContext->RSSetViewports(1, &vp);
				}

				pBackBuffer->Release();

				m_bInit = true;
			}
		}
		else {
			wchar_t cBuff_WCAHR[256];
			char cBuff_CHAR[256];
			DXGetErrorDescription(eResult, cBuff_WCAHR, 256);		
			WideCharToMultiByte(CP_ACP, NULL, cBuff_WCAHR, 256, cBuff_CHAR, 256, NULL, NULL);

			string str(cBuff_CHAR);
			str = str.substr(0, str.length() - 2);

			DrawLine("~RenderWindowD11_1: Ошибка - " + str);
		}

		return m_bInit;
	}

	void RenderWindowD11_1::IInit()
	{
		m_pScene = m_pCamera->GetSceneObject()->GetScene();
	}

	void RenderWindowD11_1::IRender()
	{
		_lSceneObject lObject;
		m_pScene->GetSceneObjects(lObject);

		for (auto object : lObject)
		{
			_lCoreComponent lComponent;
			object->GetObjectComponents(lComponent);

			for (auto component : lComponent)
			{
				switch (component->GetType())
				{
				case Dex::OCT_RENDER:
					RenderComponentD11_1* render = (RenderComponentD11_1*)component; // TODO

					GeometryFile* geometry = render->GetGeometry();
					if (render->IsActive() && geometry) {
						_lVertexBuffer vertexbuffers;
						geometry->GetVertexBuffer(vertexbuffers);

						for (auto vertex : vertexbuffers)
						{
							ID3D11Buffer* pD3D11Buffer = NULL;

							_lD3D11Buffer::iterator itD3D11Buff = m_lD3D11Buffer.find(geometry->GetName() + "_vertex");
							if (itD3D11Buff == m_lD3D11Buffer.end())
							{
								// LOADING !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
								HRESULT eResult = S_FALSE;

								_lVertexLayout lLayout;
								vector< D3D11_INPUT_ELEMENT_DESC > lD3D11Layout;
								vertex->GetVertexSemantics(lLayout);
								UINT nOffset = 0;

								for (auto vertexlayout : lLayout)
								{
									D3D11_INPUT_ELEMENT_DESC eIE;
									switch (vertexlayout)
									{
									case VertexLayout::VL_POSITION:
									{
										eIE.SemanticName = "POSITION";
										eIE.SemanticIndex = 0;
										eIE.Format = DXGI_FORMAT_R32G32B32_FLOAT;
										eIE.InputSlot = 0;
										eIE.AlignedByteOffset = nOffset;
										eIE.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
										eIE.InstanceDataStepRate = 0;

										nOffset += 12;
									}
									break;

									case VertexLayout::VL_TEXTURE:
									{
										eIE.SemanticName = "TEXTURE";
										eIE.SemanticIndex = 0;
										eIE.Format = DXGI_FORMAT_R32G32B32_FLOAT;
										eIE.InputSlot = 0;
										eIE.AlignedByteOffset = nOffset;
										eIE.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
										eIE.InstanceDataStepRate = 0;

										nOffset += 8;
									}
									break;

									case VertexLayout::VL_NORMAL:
									{
										eIE.SemanticName = "NORMAL";
										eIE.SemanticIndex = 0;
										eIE.Format = DXGI_FORMAT_R32G32B32_FLOAT;
										eIE.InputSlot = 0;
										eIE.AlignedByteOffset = nOffset;
										eIE.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
										eIE.InstanceDataStepRate = 0;

										nOffset += 12;
									}
									break;
									}

									lD3D11Layout.push_back(eIE);
								}

								//eResult = m_pD3D11Device->CreateInputLayout(lD3D11Layout.data(), lD3D11Layout.size(), pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &g_pVertexLayout);

								D3D11_BUFFER_DESC bd;
								ZeroMemory(&bd, sizeof(bd));

								bd.Usage = D3D11_USAGE_DEFAULT;
								bd.ByteWidth = vertex->GetSizeBuffer();
								bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
								bd.CPUAccessFlags = 0;

								D3D11_SUBRESOURCE_DATA InitData;
								ZeroMemory(&InitData, sizeof(InitData));

								InitData.pSysMem = vertex->GetBuffer();

								eResult = m_pD3D11Device->CreateBuffer(&bd, &InitData, &pD3D11Buffer);
								if (SUCCEEDED(eResult))
								{
									m_lD3D11Buffer.insert(_lD3D11Buffer::value_type(geometry->GetName() + "_vertex", pD3D11Buffer));
								}
								else
								{
									wchar_t cBuff_WCAHR[256];
									char cBuff_CHAR[256];
									DXGetErrorDescription(eResult, cBuff_WCAHR, 256);
									WideCharToMultiByte(CP_ACP, NULL, cBuff_WCAHR, 256, cBuff_CHAR, 256, NULL, NULL);

									string str(cBuff_CHAR);
									str = str.substr(0, str.length() - 2);

									DrawLine("IRender: Ошибка - " + str);
								}
							}
							else
							{
								pD3D11Buffer = itD3D11Buff->second;
							}

							UINT stride = vertex->GetSizeBuffer() / vertex->GetVertexCount();
							UINT offset = vertex->GetOffsetBuffer();

							m_pImmediateContext->IASetVertexBuffers(0, 1, &pD3D11Buffer, &stride, &offset);
						}

						IndexBuffer* indexbuffer = geometry->GetIndexBuffer();
					}
					break;
				/*case Dex::OCT_CAMERA:
					break;
				case Dex::OCT_LIGHT:
					break;*/
				}
			}
		}

		float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; //red,green,blue,alpha
		m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);
		m_pSwapChain->Present(0, 0);
	}
}