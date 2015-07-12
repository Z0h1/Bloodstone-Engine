#pragma once

#include "DexPreComplition_E.h"

namespace Dex
{
	class EditorMain : public wxApp
	{
	public:
		virtual bool OnInit() wxOVERRIDE;
	};

	wxIMPLEMENT_APP(EditorMain);
}