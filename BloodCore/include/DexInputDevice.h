#pragma once

#include "DexPreCompletion.h"
#include "DexCommon.h"

namespace Dex
{
	typedef struct _sMouseState
	{
		long lX;
		long lY;
		long lZ;
		unsigned char rgbButtons[4];

	} g_sMouseState;

	class D_EXPORT IInputDevice
	{
	public:
		virtual ~IInputDevice( void );

		const string& GetName( void );

	public:
		virtual bool GetState( void* pBuf, int nSize ) = 0;

	protected:
		HWND					m_hWnd;
		string					m_cName;
	};
}