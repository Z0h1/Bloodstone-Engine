#pragma once

#include "DexPreCompletion.h"

namespace DEX
{
	class D_EXPORT Buffer
	{
	public:
		Buffer(void* buf)
			: m_pBuffer(buf)
		{
		}

		virtual ~Buffer()
		{
			if (m_pBuffer)
				delete m_pBuffer;
		}

		void* GetBuffer() const { return m_pBuffer;  }

	protected:
		void*	m_pBuffer;
	};
}