#include "DexRenderWindowD11_1.h"

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

	void RenderWindowD11_1::IRender()
	{
		float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; //red,green,blue,alpha
		m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);
		m_pSwapChain->Present(0, 0);
	}
}