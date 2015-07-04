#pragma once

#include "DexPreCompletion.h"
#include "DexCommon.h"

namespace Dex
{
	class D_EXPORT HardwareBuffer
	{
	public:
		void* GetBuffer( void );

	protected:
		void*				m_pBuffer;
	};
}