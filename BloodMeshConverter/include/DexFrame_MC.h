#pragma once

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/filepicker.h>
#include <Dex.h>

namespace Dex
{
	struct OBJ_File
	{
		Point3 position;
		Point2 texcoord;
		Point3 normal;
	};

	#define GEOMETRY_VERSION_CONVERTER 3

	class Frame : public wxFrame, public Serializer
	{
	public:
		Frame(void);
		~Frame(void);

		void InitEngine(void);

	protected:
		void StartConvert(wxCommandEvent& pEvent);

	private:
		enum
		{
			ID_FRAME = 1000,
			ID_FILESELECT,
			ID_PROGRESSBAR,
			ID_CHECKBOX_VERTEX,
			ID_CHECKBOX_INDEX,
			ID_CHECKBOX_TEXCOORD,
			ID_GO,
		};

		int AddVertex(OBJ_File* sVertex);

	private:
		wxFilePickerCtrl* m_FileSelect;
		wxGauge* m_ProgressBar;
		wxCheckBox* m_CheckBox_Vertex;
		wxCheckBox* m_CheckBox_Index;
		wxCheckBox* m_CheckBox_Texcoord;
		wxButton* m_Go;

		std::vector< OBJ_File >			m_lVertices;
		std::vector< unsigned long >	m_lIndices;

		Core*		m_pCore;

		DECLARE_EVENT_TABLE()
	};
}