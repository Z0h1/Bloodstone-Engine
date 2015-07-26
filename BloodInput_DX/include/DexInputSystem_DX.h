#pragma once

#include "DexPreComplition_ISDX.h"
#include "DexInputSystem.h"

namespace Dex
{
	typedef map<string, InputDevice_DX* >	_lInputDeviceDX;

	class D_EXPORT_ISDX InputSystem_DX : public InputSystem
	{
	public:
		InputSystem_DX(ofstream* logger);
		~InputSystem_DX();

		void EnumerationDevice(void);

		IDirectInput8* GetDirectInput8(void);

		InputDevice* CreateDevice(const _lParametor& lConfig);

	private:
		_lInputDeviceDX			m_lInputDeviceDX;

		IDirectInput8*			m_pDI;
		IDirectInputDevice8*	m_pIDevice_Mouse;
	};
}