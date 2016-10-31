#pragma once

#include "DexPreCompletion.h"
#include "DEXClass.h"

class DEXSystem : public DEXClass
{
	DEXSystem(DEX_PCore core);
};

#include "DexCoreObject.h"

namespace DEX
{
	class D_EXPORT ISystem : public CoreObject
	{
	public:
		ISystem(const string& c_name, ofstream* logger, const SystemsType st, bool fw = false);
		virtual ~ISystem();

		const SystemsType GetType();

	protected:
		const SystemsType		m_Type;
	};
}
