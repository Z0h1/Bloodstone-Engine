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

		UInt32 GetSizeBuffer(void);
		UInt32 GetVertexCount(void);
		UInt32 GetOffsetBuffer(void);

	protected:
		_lVertexLayout			m_lVertexSemantic;

		UInt32					m_nVertexCount;
		UInt32					m_nOffset;
	};
}