#include <DexApp_MC.h>

namespace Dex
{
	bool App::OnInit(void)
	{
		if (!wxApp::OnInit())
			return false;

		Frame* m_pFrame = new Frame();
		m_pFrame->InitEngine();
		m_pFrame->Show();

		return true;
	}

	IMPLEMENT_APP(App)
}