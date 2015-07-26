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

		void OnKayDown(wxKeyEvent& event);
		void OnQuit(wxCommandEvent& event);
		void OnAbout(wxCommandEvent& event);
		void OnMainTimerTick(wxTimerEvent& event);

		void FindAndAddObjectList(CoreObject* obj, CoreObject* add);
		void CallFileSystemSetting(wxCommandEvent& event);

		bool KeyPressed(int nKey);

	private:
		wxPanel*			m_pRenderWindow;
		wxTimer				m_pMainTimer;
		EObjectListTree*	m_pObjectList;

		void InitEngine();

		Core*				m_pCore;
		RenderSystem*		m_pRenderSystem;
		Scene*				m_pScene;
		FileSystem*			m_pFileSystem;
		SceneObject*		m_pCamera;
		InputDevice*		m_pMouse;
		InputDevice*		m_pKeyboard;
		InputSystem*		m_pInputSystem;
		char				m_KeyBuffer[256];

		wxDECLARE_EVENT_TABLE();
	};
}