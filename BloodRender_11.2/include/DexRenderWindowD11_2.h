#pragma once

#include "DexPreComplitionD11_2.h"
#include "DexRenderWindow.h"

namespace Dex
{
	class D_EXPORT_D11_1 RenderWindowD11_2 : public RenderWindow
	{
	public:
		RenderWindowD11_2(ofstream* logger, RenderSystemD11_2* system);
		~RenderWindowD11_2();

		virtual bool Create(const _lParametor& config);

		void Render();

	private:
		void BeginRender();
		void EndRender();
		void RenderOneComponent(RenderComponentD11_2* component);

		void CalculateMatrix();

		Microsoft::WRL::ComPtr<IDXGISwapChain1>			m_swapChain;

		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	m_d3dRenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	m_d3dDepthStencilView;
		D3D11_VIEWPORT									m_screenViewport;

		RenderSystemD11_2*								m_pRSystem;
	};
}