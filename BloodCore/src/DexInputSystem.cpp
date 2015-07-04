#include "DexInputSystem.h"

namespace Dex
{
	IInputSystem::IInputSystem(const String& c_name, OFStream* logger, const SystemsType st, bool fw)
		: ISystem(c_name, logger, st, fw)
	{
	}

	IInputSystem::~IInputSystem(void)
	{
	}
}