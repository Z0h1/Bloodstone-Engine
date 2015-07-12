#include "DexFileSystemInfo_E.h"

namespace Dex
{
	BEGIN_EVENT_TABLE(TreeFileListE, wxTreeCtrl)
		EVT_TREE_BEGIN_DRAG(EDITOR_FILELIST, TreeFileListE::OnTreeBeginDrag)
		EVT_TREE_BEGIN_LABEL_EDIT(EDITOR_FILELIST, TreeFileListE::OnTreeBeginLableEdit)
		EVT_TREE_BEGIN_RDRAG(EDITOR_FILELIST, TreeFileListE::OnTreeBeginRDrag)
		EVT_TREE_DELETE_ITEM(EDITOR_FILELIST, TreeFileListE::OnTreeDeletelitem)
		EVT_TREE_END_DRAG(EDITOR_FILELIST, TreeFileListE::OnTreeEndDrag)
		EVT_TREE_END_LABEL_EDIT(EDITOR_FILELIST, TreeFileListE::OnTreeEndLableEdit)
		EVT_TREE_ITEM_ACTIVATED(EDITOR_FILELIST, TreeFileListE::OnActivated)
		EVT_TREE_ITEM_COLLAPSED(EDITOR_FILELIST, TreeFileListE::OnTreeitemCollapsed)
		EVT_TREE_ITEM_COLLAPSING(EDITOR_FILELIST, TreeFileListE::OnTreeitemCollapsing)
		EVT_TREE_ITEM_EXPANDED(EDITOR_FILELIST, TreeFileListE::OnTreeitemExpanded)
		EVT_TREE_ITEM_EXPANDING(EDITOR_FILELIST, TreeFileListE::OnTreeitemExpanding)
		EVT_TREE_ITEM_MENU(EDITOR_FILELIST, TreeFileListE::OnTreeitemMenu)
		EVT_TREE_ITEM_MIDDLE_CLICK(EDITOR_FILELIST, TreeFileListE::OnTreeitemMiddeleClick)
		EVT_TREE_ITEM_RIGHT_CLICK(EDITOR_FILELIST, TreeFileListE::OnTreeitemRightClick)
		EVT_TREE_KEY_DOWN(EDITOR_FILELIST, TreeFileListE::OnTreeKayDown)
		EVT_TREE_SEL_CHANGED(EDITOR_FILELIST, TreeFileListE::OnTreeSelChanged)
		EVT_TREE_SEL_CHANGING(EDITOR_FILELIST, TreeFileListE::OnTreeSelChanging)
	END_EVENT_TABLE()

	TreeFileListE::TreeFileListE(wxWindow *parent, const wxWindowID id,
		const wxPoint& pos, const wxSize& size,
		long style)
		: wxTreeCtrl(parent, id, pos, size, style)
	{
	}

	void TreeFileListE::SetText(wxListCtrl* DynamicTextName, wxStaticText* name, wxStaticText* path)
	{
		m_pDynamicText = DynamicTextName;

		m_pDynamicTextName = name;
		m_pDynamicTextType = path;
	}

	void TreeFileListE::OnTreeBeginDrag(wxTreeEvent& WXUNUSED(event))
	{
		if (m_pDynamicText) m_pDynamicText->InsertItem(0, wxT("OnTreeBeginDrag"));
	}
	void TreeFileListE::OnTreeBeginLableEdit(wxTreeEvent& WXUNUSED(event))
	{
		if (m_pDynamicText) m_pDynamicText->InsertItem(0, wxT("OnTreeBeginLableEdit"));
	}
	void TreeFileListE::OnTreeBeginRDrag(wxTreeEvent& WXUNUSED(event))
	{
		if (m_pDynamicText) m_pDynamicText->InsertItem(0, wxT("OnTreeBeginRDrag"));
	}
	void TreeFileListE::OnTreeDeletelitem(wxTreeEvent& WXUNUSED(event))
	{
		if (m_pDynamicText) m_pDynamicText->InsertItem(0, wxT("OnTreeDeletelitem"));
	}
	void TreeFileListE::OnTreeEndDrag(wxTreeEvent& WXUNUSED(event))
	{
		if (m_pDynamicText) m_pDynamicText->InsertItem(0, wxT("OnTreeEndDrag"));
	}
	void TreeFileListE::OnTreeEndLableEdit(wxTreeEvent& WXUNUSED(event))
	{
		if (m_pDynamicText) m_pDynamicText->InsertItem(0, wxT("OnTreeEndLableEdit"));
	}

	void TreeFileListE::OnActivated(wxTreeEvent& event)
	{
		if (m_pDynamicText)
			m_pDynamicText->InsertItem(0, wxT("OnActivated"));

		wxTreeItemId itemId = event.GetItem();
		TreeFileListDataE *item = (TreeFileListDataE*)GetItemData(itemId);
		CoreFile* file = item->GetCoreFile();

		switch (file->GetFormat())
		{
		case Dex::FF_DEXG:
			GeometryFile* gfile = (GeometryFile*)file;
			gfile->ImportMesh();
			break;
		}

		event.Skip();
	}

	void TreeFileListE::OnTreeitemCollapsed(wxTreeEvent& WXUNUSED(event))
	{
		if (m_pDynamicText) m_pDynamicText->InsertItem(0, wxT("OnTreeitemCollapsed"));
	}
	void TreeFileListE::OnTreeitemCollapsing(wxTreeEvent& WXUNUSED(event))
	{
		if (m_pDynamicText) m_pDynamicText->InsertItem(0, wxT("OnTreeitemCollapsing"));
	}
	void TreeFileListE::OnTreeitemExpanded(wxTreeEvent& WXUNUSED(event))
	{
		if (m_pDynamicText) m_pDynamicText->InsertItem(0, wxT("OnTreeitemExpanded"));
	}
	void TreeFileListE::OnTreeitemExpanding(wxTreeEvent& WXUNUSED(event))
	{
		if (m_pDynamicText) m_pDynamicText->InsertItem(0, wxT("OnTreeitemExpanding"));
	}

	void TreeFileListE::OnTreeitemMenu(wxTreeEvent& event)
	{
		if (m_pDynamicText)
			m_pDynamicText->InsertItem(0, wxT("OnTreeitemMenu"));

		wxTreeItemId itemId = event.GetItem();

		TreeFileListDataE *item = (TreeFileListDataE*)GetItemData(itemId);
		wxPoint clientpt = event.GetPoint();
		wxPoint screenpt = ClientToScreen(clientpt);

		
		wxMenu menu(wxT("&Abasdasdasdasdout"));
		menu.Append(wxID_ANY, wxT("&About"));
		menu.AppendSeparator();
		menu.Append(wxID_ANY, wxT("&Highlight item"));
		menu.Append(wxID_ANY, wxT("&Dump"));

		PopupMenu(&menu, clientpt);
	}

	void TreeFileListE::OnTreeitemMiddeleClick(wxTreeEvent& WXUNUSED(event))
	{
		if (m_pDynamicText) m_pDynamicText->InsertItem(0, wxT("OnTreeitemMiddeleClick"));
	}
	void TreeFileListE::OnTreeitemRightClick(wxTreeEvent& WXUNUSED(event))
	{
		if (m_pDynamicText) m_pDynamicText->InsertItem(0, wxT("OnTreeitemRightClick"));
	}
	void TreeFileListE::OnTreeKayDown(wxTreeEvent& WXUNUSED(event))
	{
		if (m_pDynamicText) m_pDynamicText->InsertItem(0, wxT("OnTreeKayDown"));
	}

	void TreeFileListE::OnTreeSelChanged(wxTreeEvent& WXUNUSED(event))
	{
		if (m_pDynamicText)
			m_pDynamicText->InsertItem(0, wxT("OnTreeSelChanged"));

		TreeFileListDataE* data = (TreeFileListDataE*)GetItemData(GetSelection());
		if (data) {
			CoreFile* file = data->GetCoreFile();

			m_pDynamicTextName->SetLabel(wxString(file->GetName().c_str()));

			switch (file->GetFormat())
			{
			case Dex::FF_FOLDER:
				m_pDynamicTextType->SetLabel(wxT("Folder"));
				break;
			case Dex::FF_DEXG:
				m_pDynamicTextType->SetLabel(wxT("DEX geometry"));
				break;
			case Dex::FF_DEXM:
				m_pDynamicTextType->SetLabel(wxT("DEX material"));
				break;
			case Dex::FF_DEXP:
				m_pDynamicTextType->SetLabel(wxT("DEX pack"));
				break;
			case Dex::FF_DEXVOI:
				m_pDynamicTextType->SetLabel(wxT("DEX Visual object"));
				break;
			case Dex::FF_DEXS:
				m_pDynamicTextType->SetLabel(wxT("DEX Shader"));
				break;
			case Dex::FF_UNKNOWN:
			default:
				m_pDynamicTextType->SetLabel(wxT("unknown"));
				break;
			}
		}
	}

	void TreeFileListE::OnTreeSelChanging(wxTreeEvent& WXUNUSED(event))
	{
		if (m_pDynamicText) m_pDynamicText->InsertItem(0, wxT("OnTreeSelChanging"));
	}

	FileSystemInfoE::FileSystemInfoE(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
		: wxDialog(parent, id, title, pos, size, style)
	{
		SetSizeHints(wxDefaultSize, wxDefaultSize);

		// START

		wxBoxSizer* _sizer_main;
		_sizer_main = new wxBoxSizer(wxHORIZONTAL);

		wxBoxSizer* _sizer_fileListSizer;
		_sizer_fileListSizer = new wxBoxSizer(wxVERTICAL);

		wxBoxSizer* bSizer14;
		bSizer14 = new wxBoxSizer(wxVERTICAL);

		m_pFileList = new TreeFileListE(this, EDITOR_FILELIST, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE);
		bSizer14->Add(m_pFileList, 1, wxEXPAND, 5);


		_sizer_fileListSizer->Add(bSizer14, 1, wxEXPAND, 5);

		wxBoxSizer* bSizer15;
		bSizer15 = new wxBoxSizer(wxVERTICAL);

		m_listCtrl1 = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_LIST);
		bSizer15->Add(m_listCtrl1, 1, wxALL | wxEXPAND, 5);
		_sizer_fileListSizer->Add(bSizer15, 1, wxEXPAND, 5);


		_sizer_main->Add(_sizer_fileListSizer, 1, wxEXPAND | wxALL, 5);

		wxStaticBoxSizer* _sizer_info;
		_sizer_info = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, wxT("File info:")), wxVERTICAL);

		wxBoxSizer* _sizer_infoName;
		_sizer_infoName = new wxBoxSizer(wxHORIZONTAL);

		wxBoxSizer* _sizer_infoStaticName;
		_sizer_infoStaticName = new wxBoxSizer(wxVERTICAL);

		wxStaticText* m_pStaticTextName;
		m_pStaticTextName = new wxStaticText(_sizer_info->GetStaticBox(), wxID_ANY, wxT("Name:"), wxDefaultPosition, wxDefaultSize, 0);
		m_pStaticTextName->Wrap(-1);
		_sizer_infoStaticName->Add(m_pStaticTextName, 0, wxALL, 5);


		_sizer_infoName->Add(_sizer_infoStaticName, 1, wxEXPAND, 5);

		wxBoxSizer* _sizer_infoDynamicName;
		_sizer_infoDynamicName = new wxBoxSizer(wxVERTICAL);

		m_pDynamicTextName = new wxStaticText(_sizer_info->GetStaticBox(), wxID_ANY, wxT("228_gh_out1"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
		m_pDynamicTextName->Wrap(-1);
		_sizer_infoDynamicName->Add(m_pDynamicTextName, 1, wxALL | wxALIGN_RIGHT, 5);


		_sizer_infoName->Add(_sizer_infoDynamicName, 1, 0, 5);


		_sizer_info->Add(_sizer_infoName, 0, wxEXPAND, 5);

		wxBoxSizer* _sizer_infoType;
		_sizer_infoType = new wxBoxSizer(wxHORIZONTAL);

		wxBoxSizer* _sizer_infoStaticType;
		_sizer_infoStaticType = new wxBoxSizer(wxVERTICAL);

		wxStaticText* m_pStaticTextType;
		m_pStaticTextType = new wxStaticText(_sizer_info->GetStaticBox(), wxID_ANY, wxT("Type:"), wxDefaultPosition, wxDefaultSize, 0);
		m_pStaticTextType->Wrap(-1);
		_sizer_infoStaticType->Add(m_pStaticTextType, 0, wxALL, 5);


		_sizer_infoType->Add(_sizer_infoStaticType, 1, wxEXPAND, 5);

		wxBoxSizer* _sizer_infoDynamicType;
		_sizer_infoDynamicType = new wxBoxSizer(wxVERTICAL);

		m_pDynamicTextType = new wxStaticText(_sizer_info->GetStaticBox(), wxID_ANY, wxT("228_gh_out1"), wxDefaultPosition, wxDefaultSize, 0);
		m_pDynamicTextType->Wrap(-1);
		_sizer_infoDynamicType->Add(m_pDynamicTextType, 1, wxALL, 5);


		_sizer_infoType->Add(_sizer_infoDynamicType, 1, wxEXPAND, 5);


		_sizer_info->Add(_sizer_infoType, 0, wxEXPAND, 5);


		_sizer_info->Add(200, 0, 1, wxEXPAND, 5);


		_sizer_main->Add(_sizer_info, 0, wxEXPAND | wxALL, 5);

		// END

		SetSizer(_sizer_main);
		Layout();

		Centre(wxBOTH);
		m_pFileList->SetText(m_listCtrl1, m_pDynamicTextName, m_pDynamicTextType);
	}

	FileSystemInfoE::~FileSystemInfoE()
	{
	}

	void FileSystemInfoE::InitTree(FileSystem* file)
	{
		m_pFileSystem = file;

		wxTreeItemId root = m_pFileList->AddRoot(wxT("Files"));

		_lCoreFile _files;
		m_pFileSystem->GetlFile(_files);
		wxTreeItemId wx_folder;

		for (auto n : _files)
		{
			CoreFile* core_file = n.second;

			switch (core_file->GetFormat())
			{
			case Dex::FF_UNKNOWN:
			case Dex::FF_DEXG:
			case Dex::FF_DEXM:
			case Dex::FF_DEXVOI:
			case Dex::FF_DEXS:
				m_pFileList->AppendItem(root, wxString(core_file->GetName().c_str()), -1, -1, new TreeFileListDataE(core_file));
				break;
			case Dex::FF_FOLDER:
				wx_folder = m_pFileList->AppendItem(root, wxString(core_file->GetName().c_str()), -1, -1, new TreeFileListDataE(core_file));
				FillFolder((Folder*)core_file, wx_folder);
				break;
			case Dex::FF_DEXP:
				break;
			}
		}


		m_pFileList->ExpandAll();
	}

	void FileSystemInfoE::FillFolder(Folder* folder, wxTreeItemId& child)
	{
		_lCoreFile _files;
		folder->GetlFile(_files);
		wxTreeItemId wx_folder;

		for (auto n : _files)
		{
			CoreFile* core_file = n.second;

			switch (core_file->GetFormat())
			{
			case Dex::FF_UNKNOWN:
			case Dex::FF_DEXG:
			case Dex::FF_DEXM:
			case Dex::FF_DEXVOI:
			case Dex::FF_DEXS:
				m_pFileList->AppendItem(child, wxString(core_file->GetName().c_str()), -1, -1, new TreeFileListDataE(core_file));
				break;
			case Dex::FF_FOLDER:
				wx_folder = m_pFileList->AppendItem(child, wxString(core_file->GetName().c_str()), -1, -1, new TreeFileListDataE(core_file));
				FillFolder((Folder*)core_file, wx_folder);
				break;
			case Dex::FF_DEXP:
				break;
			}
		}
	}
}