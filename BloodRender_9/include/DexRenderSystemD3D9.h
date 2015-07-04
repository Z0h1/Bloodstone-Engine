#pragma once

#include "DexPreCompletionD3D9.h"
#include "DexRenderSystem.h"

namespace Dex
{
	class D_EXPORT_D3D9 RenderSystemD3D9 : public IRenderSystem
	{
	public:
		RenderSystemD3D9(ofstream* logger);
		~RenderSystemD3D9();

		const _lString& GetAvailableDisplayMode(void);
		const _lString& GetAvailableAdpter(void);

		IRenderWindow * CreateRenderWindow(const _lParametor & config, HWND h);

		void RenderWindow(const string& cName);
		void RenderAllWindow(void);

		IRenderWindow* GetWindow(const string& cNameWindow);
		IRenderConnect* GetConnect(const string& cNameWindow);

	private:
		void InitSystem(void);
		void EnumerationAdapter(void);

		typedef map< string, RenderWindowD3D9* >	_lWindow;
		typedef vector< RenderAdapterD3D9* >		_lDriver;

		_lWindow			m_lWindow;
		_lDriver			m_lDriver;

		// DirectX Setting
		IDirect3D9*			m_pD3D9;
	};
}