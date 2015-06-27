#include "BSRender.h"

namespace Bloodstone
{
	BSRender::BSRender()
		: BSystem("RENDER_SYSTEM")
	{
	}


	BSRender::~BSRender()
	{
	}

	void BSRender::Load(istream & is)
	{
	}

	void BSRender::Store(ostream & os)
	{
		os << "RENDER SYSTEM";
	}
}
