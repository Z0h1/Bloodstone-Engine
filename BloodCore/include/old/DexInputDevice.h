#pragma once

#include "DexPreCompletion.h"
#include "DexCoreObject.h"

namespace DEX
{
	typedef struct
	{
		long lX;
		long lY;
		long lZ;
		unsigned char rgbButtons[4];

	} _mouseState;

	class D_EXPORT InputDevice : public CoreObject
	{
	public:
		InputDevice(ofstream* logger, const string& name);
		virtual ~InputDevice(void);

		virtual bool GetState(void* pBuf, int nSize) = 0;

	protected:
		int						m_hWnd;
	};
}