#include "DexIndexBuffer.h"

namespace Dex
{
	IndexBuffer::IndexBuffer(_intun nIndexCount, IndexType eType)
		: Buffer(nullptr)
	{
		m_nIndexCount = nIndexCount;
		m_eIndexType = eType;

		m_nOffset = sizeof(unsigned long);
		if (m_eIndexType == IT_16)
		{
			m_nOffset = sizeof(unsigned short);
		}

		m_pBuffer = malloc(m_nIndexCount * m_nOffset);
	}

	IndexBuffer::~IndexBuffer(void)
	{
	}

	_intun IndexBuffer::GetIndexCount(void)
	{
		return m_nIndexCount;
	}

	_intun IndexBuffer::GetSizeIndex(void)
	{
		return m_nIndexCount * m_nOffset;
	}

	IndexType IndexBuffer::GetIndexType(void)
	{
		return m_eIndexType;
	}
}