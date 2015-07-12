#pragma once

#include "DexPreCompletion.h"
#include "DexCommon.h"
#include "DexSystem.h"

namespace Dex
{
	typedef map< string, IRenderWindow* >	_lWindow;

	class D_EXPORT IRenderSystem : public ISystem
	{
	public:
		IRenderSystem(const string& c_name, ofstream* logger, const SystemsType st, bool fw = false);
		virtual ~IRenderSystem(void);

		virtual RenderComponent* CreateRenderComponent(const string& c_name, SceneObject* parent) = 0;

		void SetActiveAdapter(UInt32 adapter);

		virtual void GetAvailableDisplayMode(_lString& ls) = 0;
		virtual void GetAvailableAdpter(_lString& ls) = 0;

		virtual IRenderWindow* CreateRenderWindow(const _lParametor& config) = 0;
		virtual void RenderAllWindow(void) = 0;

	protected:
		string					m_nAdapter;
		_lWindow				m_lWindow;
	};
}