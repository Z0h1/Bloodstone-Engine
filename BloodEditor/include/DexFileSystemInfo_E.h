#pragma once

#include "DexPreComplition_E.h"

namespace Dex
{
	enum
	{
		EDITOR_FILELIST = 1050
	};

	class TreeFileListDataE : public wxTreeItemData
	{
	public:
		TreeFileListDataE(CoreFile* desc)
			: m_desc(desc)
		{
		}

		CoreFile* GetCoreObject() const { return m_desc; }

	private:
		CoreFile*		m_desc;
	};

	class TreeFileListE : public wxTreeCtrl
	{
	public:
		TreeFileListE()
		{
		}

		TreeFileListE(wxWindow *parent, const wxWindowID id,
			const wxPoint& pos, const wxSize& size,
			long style);

		virtual ~TreeFileListE()
		{
		};

		void SetText(wxListCtrl* DynamicTextName, wxStaticText* name, wxStaticText* path);

		void OnActivated(wxTreeEvent& event);
		void OnTreeBeginDrag(wxTreeEvent& event);
		void OnTreeBeginLableEdit(wxTreeEvent& event);
		void OnTreeBeginRDrag(wxTreeEvent& event);
		void OnTreeDeletelitem(wxTreeEvent& event);
		void OnTreeEndDrag(wxTreeEvent& event);
		void OnTreeEndLableEdit(wxTreeEvent& event);
		void OnTreeitemCollapsed(wxTreeEvent& event);
		void OnTreeitemCollapsing(wxTreeEvent& event);
		void OnTreeitemExpanded(wxTreeEvent& event);
		void OnTreeitemExpanding(wxTreeEvent& event);
		void OnTreeitemMenu(wxTreeEvent& event);
		void OnTreeitemMiddeleClick(wxTreeEvent& event);
		void OnTreeitemRightClick(wxTreeEvent& event);
		void OnTreeKayDown(wxTreeEvent& event);
		void OnTreeSelChanged(wxTreeEvent& event);
		void OnTreeSelChanging(wxTreeEvent& event);

	private:
		wxDECLARE_EVENT_TABLE();

		wxListCtrl* m_pDynamicText;
		wxStaticText* m_pDynamicTextName;
		wxStaticText* m_pDynamicTextType;
	};

	class FileSystemInfoE : public wxDialog
	{

	private:
		TreeFileListE* m_pFileList;
		wxStaticText* m_pDynamicTextName;
		wxStaticText* m_pDynamicTextType;
		wxListCtrl* m_listCtrl1;

		FileSystem*		m_pFileSystem;

		void FillFolder(Folder* folder, wxTreeItemId& child);

	protected:

	public:

		FileSystemInfoE(wxWindow* parent, wxWindowID id = wxID_ANY,
			const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxSize(900, 600), long style = wxDEFAULT_DIALOG_STYLE);
		~FileSystemInfoE();

		void InitTree(FileSystem* file);
	};
}