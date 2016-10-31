#pragma once

#include "DexPreCompletion.h"
#include "DexBuffer.h"

namespace DEX
{
	typedef list< VertexLayout >			_lVertexLayout;

	class D_EXPORT VertexBuffer : public Buffer
	{
	public:
		VertexBuffer(unsigned int nVertexCount);
		~VertexBuffer(void);

		void GetVertexSemantics(_lVertexLayout& sl);
		void AddVertexSemantic(VertexLayout eSemantics);
		void RemoveVertexSemantic(VertexLayout eSemantics);

		_32un GetSizeBuffer(void);
		_32un GetVertexCount(void);
		_32un GetOffsetBuffer(void);

	protected:
		_lVertexLayout			m_lVertexSemantic;

		_32un					m_nVertexCount;
		_32un					m_nOffset;
	};
}