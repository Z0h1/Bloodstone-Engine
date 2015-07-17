#include "DexRenderWindowD11_2.h"
#include "DexRenderSystemD11_2.h"
#include "DexRenderComponentD11_2.h"
#include "DexScene.h"
#include "DexSceneObject.h"
#include "DexFile.h"
#include "DexIndexBuffer.h"
#include "DexVertexBuffer.h"
#include "DexCameraComponent.h"
#include "DexCoreComponent.h"
#include "DexShaderStructures.h"

using namespace D2D1;
using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;

namespace Dex
{
	RenderWindowD11_2::RenderWindowD11_2(ofstream* logger, RenderSystemD11_2* system)
		: RenderWindow("", logger)
	{
		m_pRSystem = system;
	}

	RenderWindowD11_2::~RenderWindowD11_2()
	{
	}

	// TODO create software window
	bool RenderWindowD11_2::Create(const _lParametor& config)
	{
		_lParametor::const_iterator parametor;
		HRESULT hr = S_FALSE;
		auto divace = m_pRSystem->GetD3DDevice();
		auto context = m_pRSystem->GetD3DDeviceContext();

		// ќчистить предыдуща€ размер окна конкретного контекста.
		ID3D11RenderTargetView* nullViews[] = { nullptr };
		context->OMSetRenderTargets(ARRAYSIZE(nullViews), nullViews, nullptr);
		m_d3dRenderTargetView = nullptr;
		m_d3dDepthStencilView = nullptr;
		context->Flush();

		parametor = config.find("window_name");
		if (parametor != config.end()) {
			mObjectName = parametor->second;
		}

		_32un bit = 0;
		parametor = config.find("display_mode");
		if (parametor != config.end())
		{
			StringConverter::ParseDisplyaMode(parametor->second, m_nWidth, m_nHeight, bit);
		}
		else
		{
			DrawLine("~RenderWindowD11_2: not set display_mode", MT_ERROR);
			return false;
		}

		parametor = config.find("full_screan_mode");
		if (parametor != config.end())
		{
			m_bFullScrean = StringConverter::Parse_bool(parametor->second);
		}
		else
		{
			DrawLine("~RenderWindowD11_2: not set full_screan_mode set in false");
			m_bFullScrean = false;
		}

		parametor = config.find("window_handle");
		if (parametor != config.end())
		{
			m_hWnd = StringConverter::Parse_int(parametor->second);
		}
		else
		{
			DrawLine("~RenderWindowD11_2: not set window_handle", MT_ERROR);
			return false;
		}

		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
		swapChainDesc.Width = m_nWidth;
		swapChainDesc.Height = m_nHeight;
		swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; // Ёто наиболее распространенный формат swap chain.
		swapChainDesc.Stereo = false;
		swapChainDesc.SampleDesc.Count = 1; // Don't use multi-sampling.
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 2; // Use double-buffering to minimize latency.
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL; // All Windows Store apps must use this SwapEffect.
		swapChainDesc.Flags = 0;
		swapChainDesc.Scaling = DXGI_SCALING_NONE;
		swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;

		ComPtr<IDXGIDevice2> dxgiDevice;
		divace->QueryInterface(IID_PPV_ARGS(&dxgiDevice));

		ComPtr<IDXGIAdapter> dxgiAdapter;
		dxgiDevice->GetAdapter(&dxgiAdapter);

		ComPtr<IDXGIFactory2> dxgiFactory;
		dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));

		hr = dxgiFactory->CreateSwapChainForHwnd(
			divace,			// pDevice [in]
			(HWND)m_hWnd,						// hWnd [in]
			&swapChainDesc,						// pDesc [in]
			nullptr,							// pFullscreenDesc [in, optional]
			nullptr,							// pRestrictToOutput [in, optional]
			&m_swapChain						// ppSwapChain [out]
			);

		if (FAILED(hr)) {
			DrawLine("~RenderWindowD11_2: " + RenderSystemD11_2::GetErrorHR(hr), MT_ERROR);
			return false;
		}

		// ”бедитесь, что DXGI не сто€ть в очереди больше, чем один кадр за один раз. Ёто и сокращает задержки и
		// √арантирует, что приложение будет оказывать только после каждого VSync, минимизиру€ потребление энергии.
		dxgiDevice->SetMaximumFrameLatency(1);

		// Create a render target view of the swap chain back buffer.
		ComPtr<ID3D11Texture2D> backBuffer;
		m_swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));

		divace->CreateRenderTargetView(
			backBuffer.Get(),
			nullptr,
			&m_d3dRenderTargetView
			);

		// Create a depth stencil view for use with 3D rendering if needed.
		CD3D11_TEXTURE2D_DESC depthStencilDesc(
			DXGI_FORMAT_D24_UNORM_S8_UINT,
			m_nWidth,
			m_nHeight,
			1, // This depth stencil view has only one texture.
			1, // Use a single mipmap level.
			D3D11_BIND_DEPTH_STENCIL
			);

		ComPtr<ID3D11Texture2D> depthStencil;
		divace->CreateTexture2D(
			&depthStencilDesc,
			nullptr,
			&depthStencil
			);

		CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
		divace->CreateDepthStencilView(
			depthStencil.Get(),
			&depthStencilViewDesc,
			&m_d3dDepthStencilView
			);

		// Set the 3D rendering viewport to target the entire window.
		m_screenViewport = CD3D11_VIEWPORT(
			0.0f,
			0.0f,
			(FLOAT)m_nWidth,
			(FLOAT)m_nHeight
			);

		context->RSSetViewports(1, &m_screenViewport);

		m_bInit = true;

		return true;
	}

	void RenderWindowD11_2::EndRender()
	{
		HRESULT hr = S_FALSE;

		if (m_bVSync)
		{
			hr = m_swapChain->Present(1, 0);
		}
		else
		{
			hr = m_swapChain->Present(0, 0);
		}

		if (hr == DXGI_ERROR_DEVICE_REMOVED)
		{
			m_pRSystem->RefreshResources();
		}
	}

	void RenderWindowD11_2::CalculateMatrix()
	{

	}

	void RenderWindowD11_2::RenderOneComponent(RenderComponentD11_2* component)
	{
		if (!component) {
			return;
		}

		auto sceneObject = component->GetSceneObject();

		//auto constantBuffer = component->GetConstantBufferStruct();

		if (!sceneObject->IsCalculateMatrix()) {
			//DirectX::D3DXMATRIX buffer;
			//D3DXMatrixIdentity(&m_WorldMatrixD3D9);

			//// Rotation X
			//D3DXMatrixIdentity(&buffer);
			//D3DXMatrixRotationX(&buffer, D3DXToRadian(rotation.x));
			//D3DXMatrixMultiply(&m_WorldMatrixD3D9, &buffer, &m_WorldMatrixD3D9);

			//// Rotation Y
			//D3DXMatrixIdentity(&buffer);
			//D3DXMatrixRotationY(&buffer, D3DXToRadian(rotation.y));
			//D3DXMatrixMultiply(&m_WorldMatrixD3D9, &buffer, &m_WorldMatrixD3D9);

			//// Rotation Z
			//D3DXMatrixIdentity(&buffer);
			//D3DXMatrixRotationZ(&buffer, D3DXToRadian(rotation.z));
			//D3DXMatrixMultiply(&m_WorldMatrixD3D9, &buffer, &m_WorldMatrixD3D9);

			//// Scaling
			//D3DXMatrixIdentity(&buffer);
			//D3DXMatrixScaling(&buffer, scale.x, scale.y, scale.z);
			//D3DXMatrixMultiply(&m_WorldMatrixD3D9, &buffer, &m_WorldMatrixD3D9);

			//// Translation
			//D3DXMatrixIdentity(&buffer);
			//D3DXMatrixTranslation(&buffer, position.x, position.y, position.z);
			//D3DXMatrixMultiply(&m_WorldMatrixD3D9, &buffer, &m_WorldMatrixD3D9);

			//constantBuffer.model = buffer;
		}

		component->Render(m_pRSystem->GetD3DDeviceContext());
	}

	void RenderWindowD11_2::BeginRender()
	{
		auto context = m_pRSystem->GetD3DDeviceContext();

		context->RSSetViewports(1, &m_screenViewport);

		ID3D11RenderTargetView *const targets[1] = { m_d3dRenderTargetView.Get() };
		context->OMSetRenderTargets(1, targets, m_d3dDepthStencilView.Get());

		context->ClearRenderTargetView(m_d3dRenderTargetView.Get(), DirectX::Colors::CornflowerBlue); // TODO SET COLOR
		context->ClearDepthStencilView(m_d3dDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

	void RenderWindowD11_2::Render()
	{
		BeginRender();

		// Render all render component from scene
		if (m_bActive && m_pSceneToRender && m_pCamera) {	
			_4matrix view = m_pCamera->GetMatrixView();


			_lSceneObject objects;
			m_pSceneToRender->GetSceneObjects(objects);

			for (auto object : objects)
			{
				_lCoreComponent components;
				object->GetObjectComponents(components);

				for (auto component : components)
				{
					switch (component->GetType())
					{
					case Dex::OCT_RENDER:
					{
						RenderOneComponent(dynamic_cast<RenderComponentD11_2*>(component));
					}
					break;

					case Dex::OCT_CAMERA:
						break;
					case Dex::OCT_LIGHT:
						break;
					}
				}
			}
		}

		EndRender();
	}
}