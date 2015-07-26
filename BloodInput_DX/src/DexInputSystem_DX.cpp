#include "DexInputSystem_DX.h"
#include "DexInputDevice_DX.h"

namespace Dex
{
	InputSystem_DX::InputSystem_DX(ofstream* logger)
		: InputSystem("INPUT_SYSTEM_DX", logger, SystemsType::SYSTEM_INPUT_DX)
	{
		DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDI, 0);
	}

	InputSystem_DX::~InputSystem_DX()
	{
		D_RELEASE(m_pDI);
	}

	InputDevice* InputSystem_DX::CreateDevice(const _lParametor& lConfig)
	{
		_lParametor::const_iterator it;

		it = lConfig.find("device_name");
		if (it != lConfig.end())
		{
			_lInputDeviceDX::iterator it_Device = m_lInputDeviceDX.find(it->second);

			if (it_Device == m_lInputDeviceDX.end())
			{
				InputDevice_DX* pInputDeviceDX = new InputDevice_DX(m_pDI, mOutFileStream);

				if (pInputDeviceDX->Create(lConfig))
				{
					m_lInputDeviceDX[it->second] = pInputDeviceDX;

					return pInputDeviceDX;
				}
			}
			else
			{
				DrawLine("CreateDevice: Устройство " + it->second + " уже существует", MT_WARNING);
			}
		}
		else
		{
			DrawLine("CreateDevice: Не указано имя устройства!", MT_WARNING);
		}

		return nullptr;
	}
}