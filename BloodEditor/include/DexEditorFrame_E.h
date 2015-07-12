#pragma once

#include "DexPreComplition_E.h"
#include "DexCoreObject.h"

namespace Dex
{
	enum
	{
		EDITOR_QUIT = wxID_EXIT,
		EDITOR_ABOUT = wxID_ABOUT,
		EDITOR_FILESYSTEM,
		EDITOR_MAINTIMER = 1000,
		EDITOR_OBJECTLIST
	};

	class EditorFrame : public wxFrame, public CoreObject
	{
	public:
		EditorFrame(const wxString& title);
		~EditorFrame();

		void OnQuit(wxCommandEvent& event);
		void OnAbout(wxCommandEvent& event);
		void OnMainTimerTick(wxTimerEvent& event);

		void FindAndAddObjectList(CoreObject* obj, CoreObject* add);
		void CallFileSystemSetting(wxCommandEvent& event);

	private:
		wxPanel*			m_pRenderWindow;
		wxTimer				m_pMainTimer;
		EObjectListTree*	m_pObjectList;

		void InitEngine();

		Core*				m_pCore;
		IRenderSystem*		m_pRenderSystem;
		Scene*				m_pScene;
		FileSystem*			m_pFileSystem;

		wxDECLARE_EVENT_TABLE();
	};
}