#pragma once

#include "DexPreCompletion.h"
#include "DexSystem.h"

namespace Dex
{
	typedef map< string, RenderWindow* >	_lWindow;

	class D_EXPORT RenderSystem : public ISystem
	{
	public:
		RenderSystem(const string& c_name, ofstream* logger, const SystemsType st, bool fw = false);
		virtual ~RenderSystem(void);

		virtual bool Init(const _lParametor& parametor) = 0;

		virtual RenderComponent* CreateRenderComponent(const string& c_name, SceneObject* parent) = 0;

		const string& GetActiveAdapter() const { return m_nActiveAdapter; };
		void SetActiveAdapter(const string& adapter);
		virtual void GetAvailableAdpter(_lString& ls) = 0;

		virtual void GetAvailableDisplayMode(_lString& ls) = 0;

		virtual RenderWindow* CreateRenderWindow(const _lParametor& config) = 0;

		void RenderAllWindow(void);
		virtual void RenderOneWindow(RenderWindow* window) = 0;

		void ReloadAllWindows(void);
		virtual void ReloadWindow(RenderWindow* window) = 0;

	protected:
		virtual void ISetAdapter() = 0;

		bool				m_bInit;
		string				m_nActiveAdapter;
		_lWindow			m_lWindow;
	};
}