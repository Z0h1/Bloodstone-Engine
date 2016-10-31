#pragma once

//#pragma warning (disable : 4786)
//#pragma warning (disable : 4231)

// STD Function
#include <vector>
//#include <cstdlib>

#include "DEXPlatform.h"

typedef unsigned char       DEX_BYTE;
typedef unsigned short      DEX_WORD;
typedef unsigned long		DEX_DWORD;
typedef int                 DEX_INT;
typedef unsigned int        DEX_UINT;
typedef void	            *DEX_PVOID;
typedef bool	            DEX_BOOL;

#define DEX_MAX_INT			0xffffffff // 4 Byte

struct DEXMemory
{
	DEX_PVOID pFirstAddres;
	DEX_UINT nCountBlock;
	DEX_UINT nSizeOneBlock;
};
typedef DEXMemory			*DEX_PMemory;

typedef class DEXCore		*DEX_PCore;
typedef class DEXClass		*DEX_PClass;
typedef class DEXSystem		*DEX_PSystem;
typedef class template DEXCollection<typename T>		*DEX_PCollection;

// D11_2 D_10_1 D12 OGL_2
#define DEX_USES_GRAPHIC_SYSTEM D11_2

#if defined ( BLOODCORE_EXPORTS )
#	define DEX_EXPORT __declspec( dllexport )
#   define DEX_TEMPLATE
#else
#	define DEX_EXPORT __declspec( dllimport )
#   define DEX_TEMPLATE extern
#endif