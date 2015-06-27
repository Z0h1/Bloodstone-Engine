#pragma once

#include "BHead.h"
#include "BObject.h"

namespace Bloodstone
{
	class BLOODCORE_API BSystem : public BObject
	{
	public:
		BSystem(const char* name, ofstream* os);
		~BSystem();
	};
}

