#pragma once

#include "DexPreCompletion.h"
#include "DexCommon.h"
#include "DexSystem.h"

namespace Dex
{
	class D_EXPORT IRenderSystem : public ISystem
	{
	public:
		IRenderSystem(const String& c_name, OFStream* logger, const SystemsType st, bool fw = false);
		virtual ~IRenderSystem(void);

		void SetActiveAdapter(UInt32 adapter);

		virtual const _lString& GetAvailableDisplayMode(void) = 0;
		virtual const _lString& GetAvailableAdpter(void) = 0;

		virtual IRenderWindow* CreateRenderWindow(const _lParametor& config, HWND h) = 0;
		virtual void RenderAllWindow(void) = 0;

		virtual IRenderWindow* GetWindow(const String& cNameWindow) = 0;
		virtual IRenderConnect* GetConnect(const String& cNameWindow) = 0;

	protected:
		UInt32					m_Adapter;
		_lString				m_lAdapter;
	};
}