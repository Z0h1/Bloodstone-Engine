#pragma once

#include "DexPreCompletion.h"
#include "DexSystem.h"
#include "DexCommon.h"

namespace Dex
{
#define KeyState(x) x & 0x80 ? true : false

	class D_EXPORT IInputSystem : public ISystem
	{
	public:
		IInputSystem(const string& c_name, ofstream* logger, const SystemsType st, bool fw = false);
		virtual ~IInputSystem(void);
		virtual IInputDevice* CreateDevice(const _lParametor& lConfig) = 0;
	};
}