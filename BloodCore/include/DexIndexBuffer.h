#pragma once

#include "DexPreCompletion.h"
#include "DexBuffer.h"

namespace Dex
{
	class D_EXPORT IndexBuffer : public Buffer
	{
	public:
		IndexBuffer(_intun nIndexCount, IndexType eType);
		~IndexBuffer(void);

		_intun GetIndexCount(void);
		_intun GetSizeIndex(void);
		IndexType GetIndexType(void);

	protected:
		_intun				m_nIndexCount;
		_intun					m_nOffset;

		IndexType			m_eIndexType;
	};
}