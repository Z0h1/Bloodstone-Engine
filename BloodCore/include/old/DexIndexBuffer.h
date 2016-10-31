#pragma once

#include "DexPreCompletion.h"
#include "DexBuffer.h"

namespace DEX
{
	class D_EXPORT IndexBuffer : public Buffer
	{
	public:
		IndexBuffer(_32un nIndexCount, IndexType eType);
		~IndexBuffer(void);

		_32un GetIndexCount(void);
		_32un GetSizeIndex(void);
		IndexType GetIndexType(void);

	protected:
		_32un				m_nIndexCount;
		_32un					m_nOffset;

		IndexType			m_eIndexType;
	};
}