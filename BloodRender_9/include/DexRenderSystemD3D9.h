#pragma once

#include "DexPreCompletionD3D9.h"
#include "DexRenderSystem.h"

namespace Dex
{
	class D_EXPORT_D3D9 RenderSystemD3D9 : public IRenderSystem
	{
	public:
		RenderSystemD3D9(OFStream* logger);
		~RenderSystemD3D9();

		const _lString& GetAvailableDisplayMode(void);
		const _lString& GetAvailableAdpter(void);

		IRenderWindow * CreateRenderWindow(const _lParametor & config, HWND h);

		void RenderWindow(const String& cName);
		void RenderAllWindow(void);

		IRenderWindow* GetWindow(const String& cNameWindow);
		IRenderConnect* GetConnect(const String& cNameWindow);

	private:
		void InitSystem(void);
		void EnumerationAdapter(void);

		typedef std::map< String, RenderWindowD3D9* >	_lWindow;
		typedef std::vector< RenderAdapterD3D9* >		_lDriver;

		_lWindow			m_lWindow;
		_lDriver			m_lDriver;

		// DirectX Setting
		IDirect3D9*			m_pD3D9;
	};
}