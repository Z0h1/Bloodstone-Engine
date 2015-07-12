#pragma once

#include "DexPreCompletion.h"

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/treectrl.h>
#include <wx/listctrl.h>

#include "Dex.h"

namespace Dex
{
#define DEX_TO_WX_NAME(obj) wxString(obj->GetName().c_str())

	class EditorMain;
	class DexEditorFrame;
	class EObjectListTreeData;
	class EObjectListTree;
}