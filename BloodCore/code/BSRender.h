#pragma once

#include "BSystem.h"

namespace Bloodstone
{
	class BLOODCORE_API BSRender : public BSystem
	{
	public:
		BSRender();
		~BSRender();

		virtual void Load(istream& is);
		virtual void Store(ostream& os);
	};
}