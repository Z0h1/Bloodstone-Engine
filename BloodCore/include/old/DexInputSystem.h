#pragma once

#include "DexPreCompletion.h"
#include "DexSystem.h"

namespace DEX
{
	#define KeyState(x) x & 0x80 ? true : false

	class D_EXPORT InputSystem : public ISystem
	{
	public:
		InputSystem(const string& c_name, ofstream* logger, const SystemsType st, bool fw = false);
		virtual ~InputSystem(void);

		virtual InputDevice* CreateDevice(const _lParametor& lConfig) = 0;
	};
}