#pragma once

#include <wx/app.h>
#include <DexFrame_MC.h>

namespace Dex
{
	class App : public wxApp
	{
	public:
		bool OnInit(void);
	};
}