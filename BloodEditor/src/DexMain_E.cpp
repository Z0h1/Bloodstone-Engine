#include "DexMain_E.h"
#include "DexEditorFrame_E.h"

namespace Dex
{
	bool EditorMain::OnInit()
	{
		if (!wxApp::OnInit())
			return false;

		EditorFrame *frame = new EditorFrame("Editor for BLOODSTONE Engine");
		frame->Show(true);

		return true;
	}
}