#pragma once

#include "DexPreCompletion.h"
#include "DexBuffer.h"

namespace Dex
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

		_intun GetSizeBuffer(void);
		_intun GetVertexCount(void);
		_intun GetOffsetBuffer(void);

	protected:
		_lVertexLayout			m_lVertexSemantic;

		_intun					m_nVertexCount;
		_intun					m_nOffset;
	};
}