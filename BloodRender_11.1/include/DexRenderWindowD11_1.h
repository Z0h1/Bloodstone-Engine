#pragma once

#include "DexPreComplitionD11_1.h"
#include "DexRenderWindow.h"

namespace Dex
{
	typedef map< UInt32, ID3D11Buffer* >		_lD3D11Buffer;

	class D_EXPORT_D11_1 RenderWindowD11_1 : public IRenderWindow
	{
	public:
		RenderWindowD11_1(ofstream* logger, IDXGIAdapter* adapter);
		~RenderWindowD11_1();

		virtual bool Create(const _lParametor& config);

		virtual void IRender();

	private:
		IDXGIAdapter*				m_nAdapter;
		ID3D11Device*				m_pD3D11Device;
		ID3D11DeviceContext*		m_pImmediateContext;
		IDXGISwapChain*				m_pSwapChain;
		ID3D11RenderTargetView*		m_pRenderTargetView;

		_lD3D11Buffer				m_lD3D11Buffer;
	};
}