#include "BHead.h"
#include "BSystem.h"

namespace Bloodstone
{
	BSystem::BSystem(const char* name, ofstream* os)
		: BObject(name, WP_SYSTEM)
	{
		SetOutFileStream(os);
	}


	BSystem::~BSystem()
	{
	}
}
