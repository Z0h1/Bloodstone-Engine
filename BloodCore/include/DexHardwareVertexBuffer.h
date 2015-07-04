#pragma once

#include "DexPreCompletion.h"
#include "DexCommon.h"
#include "DexHardwareBuffer.h"

namespace Dex
{
	typedef IndexedArray< VertexSemantics >			g_lVertexSemantic;

	class D_EXPORT HardwareVertexBuffer : public HardwareBuffer
	{
	public:
		HardwareVertexBuffer( unsigned int nVertexCount );
		~HardwareVertexBuffer( void );

		const g_lVertexSemantic& GetListVertexSemantic( void );
		void AddVertexSemantic( const VertexSemantics& eSemantics );
		void RemoveVertexSemantic( const VertexSemantics& eSemantics );

		int GetSizeBuffer( void );
		int GetVertexCount( void );
		int GetOffsetBuffer( void );

	protected:
		g_lVertexSemantic			m_lVertexSemantic;

		int							m_nVertexCount;
		int							m_nOffset;
	};
}