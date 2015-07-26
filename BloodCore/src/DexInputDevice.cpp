#include "DexInputDevice.h"

namespace Dex
{
	InputDevice::InputDevice(ofstream* logger, const string& name)
		: CoreObject(name, logger, WorkPriority::WP_STEP_1)
	{
	}

	InputDevice::~InputDevice(void)
	{
	}

}