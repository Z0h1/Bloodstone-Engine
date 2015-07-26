#pragma once

#include "DexPreComplition_ISDX.h"
#include "DexInputDevice.h"

namespace Dex
{
	class D_EXPORT_ISDX InputDevice_DX : public InputDevice
	{
	public:
		InputDevice_DX(IDirectInput8* pDI, ofstream* logger);
		~InputDevice_DX(void);

		bool Create(const _lParametor& lConfig);
		void Destroy(void);

	public:
		bool GetState(void* pBuf, int nSize);

	private:
		IDirectInput8*			m_pDI;
		IDirectInputDevice8*	m_pIDevice;

		DIDATAFORMAT			m_sFormat;

		HRESULT					m_nResultWin;
	};
}