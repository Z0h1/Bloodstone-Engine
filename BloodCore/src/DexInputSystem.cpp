#include "DexInputSystem.h"

namespace Dex
{
	IInputSystem::IInputSystem(const string& c_name, ofstream* logger, const SystemsType st, bool fw)
		: ISystem(c_name, logger, st, fw)
	{
	}

	IInputSystem::~IInputSystem(void)
	{
	}
}