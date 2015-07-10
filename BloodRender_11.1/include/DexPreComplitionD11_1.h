#pragma once

#include <d3d11.h>
#include <d3dx11.h>
#include <Dex_dxerr.h>

#include "DexPreCompletion.h"

namespace Dex
{
	// D_EXPORT_D11_1
#if defined ( BLOODRENDER_11_1_EXPORTS )
#	define D_EXPORT_D11_1 __declspec( dllexport )
#else
#	define D_EXPORT_D11_1 __declspec( dllimport )
#endif

#define D_RELEASE(p) if (p) { (p)->Release(); (p)=NULL; }
}