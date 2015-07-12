#pragma once

#include "DexPreCompletion.h"
#include "DexBuffer.h"

namespace Dex
{
	class D_EXPORT IndexBuffer : public Buffer
	{
	public:
		IndexBuffer(UInt32 nIndexCount, IndexType eType);
		~IndexBuffer(void);

		UInt32 GetIndexCount(void);
		UInt32 GetSizeIndex(void);
		IndexType GetIndexType(void);

	protected:
		UInt32				m_nIndexCount;
		UInt32					m_nOffset;

		IndexType			m_eIndexType;
	};
}