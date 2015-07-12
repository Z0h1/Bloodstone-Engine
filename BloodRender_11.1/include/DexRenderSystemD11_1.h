#pragma once

#include "DexPreComplitionD11_1.h"
#include "DexRenderSystem.h"

namespace Dex
{
	typedef map< string, IDXGIAdapter* >	_lDXGIAdapter;

	class D_EXPORT_D11_1 RenderSystemD11_1 : public IRenderSystem
	{
	public:
		RenderSystemD11_1(ofstream* logger);
		~RenderSystemD11_1();

		virtual RenderComponent* CreateRenderComponent(const string& c_name, SceneObject* parent);

		virtual void GetAvailableDisplayMode(_lString& ls);
		virtual void GetAvailableAdpter(_lString& ls);

		virtual IRenderWindow* CreateRenderWindow(const _lParametor& config);
		virtual void RenderAllWindow(void);

	private:
		_lDXGIAdapter		m_lDXGIAdapter;
		IDXGIFactory1*		m_pFactory;
	};
}