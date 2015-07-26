#include "DexInputDevice_DX.h"
#include "DexStringConverter.h"

namespace Dex
{
	InputDevice_DX::InputDevice_DX(IDirectInput8* pDI, ofstream* logger)
		: InputDevice(logger, "")
	{
		m_pDI = pDI;
	}

	InputDevice_DX::~InputDevice_DX(void)
	{
		Destroy();
	}

	bool InputDevice_DX::Create(const _lParametor& lConfig)
	{
		_lParametor::const_iterator it;

		it = lConfig.find("device_name");
		if (it != lConfig.end())
		{
			mObjectName = it->second;
		}

		it = lConfig.find("window_handle");
		if (it != lConfig.end())
		{
			m_hWnd = StringConverter::Parse_int(it->second);
		}
		else
		{
			DrawLine("InputDevice_DX:Create \"window_handle\" не указан", MT_ERROR);
			return false;
		}

		it = lConfig.find("device_type");
		if (it != lConfig.end())
		{
			if (it->second == "Mouse")
			{
				m_sFormat = c_dfDIMouse;
				m_pDI->CreateDevice(GUID_SysMouse, &m_pIDevice, NULL);
			}
			else if (it->second == "Keyboard")
			{
				m_sFormat = c_dfDIKeyboard;
				m_pDI->CreateDevice(GUID_SysKeyboard, &m_pIDevice, NULL);
			}
		}

		it = lConfig.find("device_format");
		if (it == lConfig.end())
		{
			m_pIDevice->SetDataFormat(&m_sFormat);
		}

		m_nResultWin = m_pIDevice->SetCooperativeLevel((HWND)m_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND | DISCL_NOWINKEY);

		if (FAILED(m_nResultWin))
		{
			Destroy();
			return false;
		}

		m_nResultWin = m_pIDevice->Acquire();

		return true;
	}

	void InputDevice_DX::Destroy(void)
	{
		D_RELEASE(m_pIDevice);
	}

	bool InputDevice_DX::GetState(void* pBuf, int nSize)
	{
		m_nResultWin = m_pIDevice->Poll();

		if (FAILED(m_nResultWin))
		{
			m_nResultWin = m_pIDevice->Acquire();
			while (m_nResultWin == DIERR_INPUTLOST)
			{
				m_nResultWin = m_pIDevice->Acquire();
			}

			return false;
		}

		m_pIDevice->GetDeviceState(nSize, pBuf);

		return true;
	}
}