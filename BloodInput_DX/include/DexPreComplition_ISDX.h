#pragma once

#include "DexPreCompletion.h"
#include <dinput.h>

namespace Dex
{
	#define D_RELEASE(p) { if (p) { (p)->Release(); (p)=nullptr; } }

	// D_EXPORT_D11_1
	#if defined ( BLOODINPUT_DX_EXPORTS )
	#	define D_EXPORT_ISDX __declspec( dllexport )
	#else
	#	define D_EXPORT_ISDX __declspec( dllimport )
	#endif

	class InputSystem_DX;
	class InputDevice_DX;
}