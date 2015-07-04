#include "DexRenderWindow.h"

namespace Dex
{
	IRenderWindow::IRenderWindow(const string& c_name, ofstream* logger, bool fw)
		: CoreObject(c_name, logger, WorkPriority::WP_STEP_1, fw)
	{
	}

	IRenderWindow::~IRenderWindow()
	{
	}

	bool IRenderWindow::IsFullScrean( void )
	{
		return m_FullScrean;
	}

	bool IRenderWindow::IsActive( void )
	{
		return m_Active;
	}
}