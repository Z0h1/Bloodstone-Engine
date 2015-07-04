#include "DexInputSystem.h"

namespace Dex
{
	IInputSystem::IInputSystem(const String& c_name, const SystemsType st, bool fw)
		: ISystem(c_name, st, fw)
	{
	}

	IInputSystem::~IInputSystem(void)
	{
	}
}