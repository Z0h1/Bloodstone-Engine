#pragma once

#include "BSystem.h"

namespace Bloodstone
{
	class BLOODCORE_API BSRender : public BSystem
	{
	public:
		BSRender(ofstream* os);
		~BSRender();

		virtual void Load(ifstream* is);
		virtual void Store(ofstream* os);
	};
}