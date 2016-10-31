#include "DexInputDevice.h"

namespace DEX
{
	InputDevice::InputDevice(ofstream* logger, const string& name)
		: CoreObject(name, logger, WorkPriority::WP_STEP_1)
	{
	}

	InputDevice::~InputDevice(void)
	{
	}

}