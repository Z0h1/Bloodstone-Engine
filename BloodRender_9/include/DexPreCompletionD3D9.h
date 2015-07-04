#pragma once

#include "DexPreCompletion.h"

#include <d3d9.h>
#include <d3dx9.h>
#include <DxErr.h>

namespace Dex
{
	// RS_D9_EXPORT
#if defined ( BLOODRENDER_9_EXPORTS )
#	define D_EXPORT_D3D9 __declspec( dllexport )
#else
#	define D_EXPORT_D3D9 __declspec( dllimport )
#endif

#define D_RELEASE(p) if (p) { (p)->Release(); (p)=NULL; }

	class RenderSystemD3D9;
	class RenderWindowD3D9;
	class RenderAdapterD3D9;
	class RenderComponentD3D9;
}