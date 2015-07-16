#pragma once

#include "DexPreComplition_E.h"

namespace Dex
{
	class EObjectListTreeData : public wxTreeItemData
	{
	public:
		EObjectListTreeData(CoreObject* obj);
		~EObjectListTreeData();

		CoreObject* GetObject();

	private:
		CoreObject*	m_pObject;
	};

	class EObjectListTree : public wxTreeCtrl, public CoreObject
	{
	public:
		EObjectListTree(ofstream* logger,
			wxWindow *parent, wxWindowID id = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxDefaultSize,
			long style = wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT,
			const wxValidator& validator = wxDefaultValidator,
			const wxString& name = wxTreeCtrlNameStr);
		~EObjectListTree();

		void SetEngine(Scene* s, RenderSystem* r);

		SceneObject* CreateSceneObject(const string& name);
		CoreComponent* CreateObjectComponent(SceneObject* obj, const _lParametor& parametors);

	private:
		Scene*			m_pScene;
		RenderSystem*	m_pRenderSystem;
	};
}