#pragma once

#include "DexPreCompletion.h"
#include "DexCoreObject.h"

namespace Dex
{
	class D_EXPORT ISystem : public CoreObject
	{
	public:
		ISystem(const String& c_name, const SystemsType st, bool fw = false);
		virtual ~ISystem();

		const SystemsType GetType();

	protected:
		const SystemsType		m_Type;
	};
}
