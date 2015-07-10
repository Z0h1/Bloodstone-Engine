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

		virtual void GetAvailableDisplayMode(_lString& ls);
		virtual void GetAvailableAdpter(_lString& ls);

		virtual IRenderWindow * CreateRenderWindow(const _lParametor & config);

		void RenderWindow(const string& cName);
		virtual void RenderAllWindow(void);

		virtual IRenderWindow* GetWindow(const string& cNameWindow);
		virtual IRenderConnect* GetConnect(const string& cNameWindow);

	private:
		void InitSystem(void);
		void EnumerationAdapter(void);

		typedef vector< RenderAdapterD3D9* >		_lDriver;

		_lDriver			m_lDriver;

		// DirectX Setting
		IDirect3D9*			m_pD3D9;
	};
}