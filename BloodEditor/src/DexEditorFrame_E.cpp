#include "DexEditorFrame_E.h"
#include "DexObjectListTree_E.h"
#include "DexFileSystemInfo_E.h"

namespace Dex
{
	wxBEGIN_EVENT_TABLE(EditorFrame, wxFrame)
		EVT_MENU(EDITOR_QUIT, EditorFrame::OnQuit)
		EVT_MENU(EDITOR_ABOUT, EditorFrame::OnAbout)
		EVT_TIMER(EDITOR_MAINTIMER, EditorFrame::OnMainTimerTick)
		EVT_MENU(EDITOR_FILESYSTEM, EditorFrame::CallFileSystemSetting)
	wxEND_EVENT_TABLE()

	EditorFrame::EditorFrame(const wxString& title)
		: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1440, 900)),
		CoreObject("EDITOR_FRAME", new ofstream("DexEditor.log"), WorkPriority::WP_MAIN)
	{
		m_pCore = nullptr;
		m_pRenderSystem = nullptr;
		m_pScene = nullptr;
		m_pFileSystem = nullptr;

		//SetIcon(wxICON(sample));
		SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNHIGHLIGHT));

#if wxUSE_MENUS
		wxMenuBar* menuBar;
		menuBar = new wxMenuBar(0);
		wxMenu* fileMenu;
		fileMenu = new wxMenu();
		wxMenuItem* _menu_fileExit;
		_menu_fileExit = new wxMenuItem(fileMenu, EDITOR_QUIT, wxString(wxT("E&xit\tAlt-X")), wxT("Quit this program"), wxITEM_NORMAL);
		fileMenu->Append(_menu_fileExit);

		menuBar->Append(fileMenu, wxT("&File"));

		wxMenu* helpMenu;
		helpMenu = new wxMenu();
		wxMenuItem* _menu_helpAbout;
		_menu_helpAbout = new wxMenuItem(helpMenu, EDITOR_ABOUT, wxString(wxT("&About\tF1")), wxT("Show about dialog"), wxITEM_NORMAL);
		helpMenu->Append(_menu_helpAbout);

		menuBar->Append(helpMenu, wxT("&Help"));

		wxMenu* systemMenu;
		systemMenu = new wxMenu();
		wxMenuItem* _menu_systemFile;
		_menu_systemFile = new wxMenuItem(systemMenu, EDITOR_FILESYSTEM, wxString(wxT("File system")), wxEmptyString, wxITEM_NORMAL);
		systemMenu->Append(_menu_systemFile);

		menuBar->Append(systemMenu, wxT("Systems setting"));

		SetMenuBar(menuBar);
#endif // wxUSE_MENUS

		// START FRAME BUILDER

		m_pMainTimer.SetOwner(this, EDITOR_MAINTIMER);
		m_pMainTimer.Start(1000);

		wxBoxSizer* _mainSizer;
		_mainSizer = new wxBoxSizer(wxHORIZONTAL);

		wxBoxSizer* _InfoSizer;
		_InfoSizer = new wxBoxSizer(wxVERTICAL);

		wxBoxSizer* _ObjectIList;
		_ObjectIList = new wxBoxSizer(wxVERTICAL);

		m_pObjectList = new EObjectListTree(mOutFileStream, this, EDITOR_OBJECTLIST, wxDefaultPosition, wxSize(400, -1), wxTR_DEFAULT_STYLE);
		_ObjectIList->Add(m_pObjectList, 1, wxEXPAND | wxALL, 5);


		_InfoSizer->Add(_ObjectIList, 1, wxEXPAND, 0);

		wxBoxSizer* _ObjectInfo;
		_ObjectInfo = new wxBoxSizer(wxVERTICAL);

		wxButton* m_button1;
		m_button1 = new wxButton(this, wxID_ANY, wxT("MyButton"), wxDefaultPosition, wxDefaultSize, 0);
		_ObjectInfo->Add(m_button1, 1, wxALL | wxEXPAND, 5);


		_InfoSizer->Add(_ObjectInfo, 1, wxEXPAND, 0);


		_mainSizer->Add(_InfoSizer, 0, wxEXPAND, 0);

		wxBoxSizer* _WorkSizer;
		_WorkSizer = new wxBoxSizer(wxVERTICAL);

		m_pRenderWindow = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
		m_pRenderWindow->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));

		_WorkSizer->Add(m_pRenderWindow, 1, wxEXPAND, 0);


		_mainSizer->Add(_WorkSizer, 1, wxEXPAND, 0);

		// END FRAME BUILDER

		SetSizer(_mainSizer);
		Layout();

#if wxUSE_STATUSBAR
		CreateStatusBar(2);
		SetStatusText("Welcome to BLOODSTONE Editor!");
#endif // wxUSE_STATUSBAR

		Centre(wxBOTH);

		InitEngine();
	}

	EditorFrame::~EditorFrame()
	{
		if (m_pCore) {
			delete m_pCore;
			m_pCore = nullptr;
		}
	}

	void EditorFrame::CallFileSystemSetting(wxCommandEvent& WXUNUSED(event))
	{
		if (m_pCore && m_pFileSystem) {
			FileSystemInfoE *dialog = new FileSystemInfoE(this, wxID_ANY);
			dialog->InitTree(m_pFileSystem);
			dialog->Show(true);
		}
		else {
			wxMessageBox(wxT("Engine don't init or file system don't init"), wxT("Error init system"), wxOK | wxCANCEL, this);
		}
	}

	void EditorFrame::InitEngine()
	{
		m_pCore = new Core();

		if (m_pCore) {
			m_pRenderSystem = m_pCore->GetRenderSystem();
			if (m_pRenderSystem) {
				m_pScene = m_pCore->CreateScene("TEST_SCENE");
				m_pObjectList->SetEngine(m_pScene, m_pRenderSystem);

				_lParametor _P;
				_P["name"] = "light_component";
				_P["type"] = "light";
				_P["light_color"] = StringConverter::toStringPoint4(0.7f, 0.2f, 0.1f, 0.5f);
				_P["light_range"] = StringConverter::toString(0.7f);
				SceneObject* test_obj2 = m_pObjectList->CreateSceneObject("LIGHT_1");
				m_pObjectList->CreateObjectComponent(test_obj2, _P);

				SceneObject* test_obj3 = m_pObjectList->CreateSceneObject("TEST_SCENE_OBJECT2");
				SceneObject* test_obj4 = m_pObjectList->CreateSceneObject("TEST_SCENE_OBJECT3");

				_P.clear();
				_P["window_name"] = "EditorWindow";
				_P["full_screan_mode"] = "off";
				wxSize sz = m_pRenderWindow->GetSize();
				_P["display_mode"] = StringConverter::toString(sz.GetWidth(), sz.GetHeight(), 32);
				_P["window_handle"] = StringConverter::toString((int)m_pRenderWindow->GetHWND());
				IRenderWindow* window = m_pRenderSystem->CreateRenderWindow(_P);

				_P.clear();
				_P["name"] = "CAMERA_1_COMPONENT";
				_P["type"] = "camera";
				_P["camera_focus"] = StringConverter::toString(0.7f);
				SceneObject* camera_obj = m_pObjectList->CreateSceneObject("CAMERA_1");
				CameraComponent* camera = (CameraComponent*)m_pObjectList->CreateObjectComponent(camera_obj, _P);
				window->SetCamera(camera);
			}

			m_pFileSystem = m_pCore->GetFileSystem();
		}
	}

	void EditorFrame::FindAndAddObjectList(CoreObject* obj, CoreObject* add)
	{
		if (m_pObjectList) {
			wxTreeItemId root = m_pObjectList->GetRootItem();
			wxTreeItemIdValue cookie;
			wxTreeItemId item = m_pObjectList->GetFirstChild(root, cookie);

			while (item.IsOk())
			{
				EObjectListTreeData* data = (EObjectListTreeData*)m_pObjectList->GetItemData(item);

				if (data->GetObject() == obj) {
					m_pObjectList->AppendItem(item, DEX_TO_WX_NAME(add), -1, -1, new EObjectListTreeData(add));

					break;
				}

				item = m_pObjectList->GetNextChild(root, cookie);
			}
		}
	}

	void EditorFrame::OnMainTimerTick(wxTimerEvent& WXUNUSED(event))
	{
		if (m_pCore && m_pRenderSystem) {
			m_pRenderSystem->RenderAllWindow();
		}
	}

	void EditorFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
	{
		Close(true);
	}

	void EditorFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
	{
		wxMessageBox(wxString::Format
			(
				"Welcome to %s!\n"
				"\n"
				"This is the minimal wxWidgets sample\n"
				"running under %s.",
				wxVERSION_STRING,
				wxGetOsDescription()
				),
			"About wxWidgets minimal sample",
			wxOK | wxICON_INFORMATION,
			this);
	}
}