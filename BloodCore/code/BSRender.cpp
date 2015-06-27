#include "BSRender.h"

namespace Bloodstone
{
	BSRender::BSRender(ofstream* os)
		: BSystem("RENDER_SYSTEM", os)
	{
		DrawLine("Test Message");
	}

	BSRender::~BSRender()
	{
	}

	void BSRender::Load(ifstream* is)
	{
	}

	void BSRender::Store(ofstream* os)
	{
		*os << "RENDER SYSTEM";
	}
}
