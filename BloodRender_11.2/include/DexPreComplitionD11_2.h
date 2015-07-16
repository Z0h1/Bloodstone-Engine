#pragma once

#include <wrl.h>
#include <wrl/client.h>
#include <d3d11_2.h>
#include <d2d1_2.h>
#include <d2d1effects_1.h>
#include <dwrite_2.h>
#include <wincodec.h>
#include <DirectXColors.h>
#include <DirectXMath.h>
#include <memory>
#include <D3Dcompiler.h>
//#include <agile.h>
#include <concrt.h>

#include "DexPreCompletion.h"

namespace Dex
{
	// D_EXPORT_D11_1
#if defined ( BLOODRENDER_11_1_EXPORTS )
#	define D_EXPORT_D11_1 __declspec( dllexport )
#else
#	define D_EXPORT_D11_1 __declspec( dllimport )
#endif

#define D_DELETE(p)		{ if(p){delete (p); (p)=nullptr;} }
#define D_DELETE_ARRAY(p)	{ if(p){delete[] (p); (p)=nullptr;} }
#define D_RELEASE(p)		{ if(p){(p)->Release(); (p)=nullptr;} }
#define D_CLOSE(p)		{ if(p){(p)->Close(); delete (p); (p)=nullptr;} }

	class RenderSystemD11_2;
	class RenderWindowD11_2;
	class RenderComponentD11_2;
}