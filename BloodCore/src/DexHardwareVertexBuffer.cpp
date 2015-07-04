#include "DexHardwareVertexBuffer.h"

namespace Dex
{
	HardwareVertexBuffer::HardwareVertexBuffer( unsigned int nVertexCount )
	{
		m_nVertexCount = nVertexCount;
		m_nOffset = 0;

		m_pBuffer = 0;
	}

	HardwareVertexBuffer::~HardwareVertexBuffer( void )
	{
	}

	const g_lVertexSemantic& HardwareVertexBuffer::GetListVertexSemantic( void )
	{
		return m_lVertexSemantic;
	}

	void HardwareVertexBuffer::AddVertexSemantic( const VertexSemantics& eSemantics )
	{
		m_lVertexSemantic.Add( eSemantics );

		if ( eSemantics == VS_POSITION )
		{
			m_nOffset += 12;
		}
		else if ( eSemantics == VS_NORMAL )
		{
			m_nOffset += 12;
		}
		else if ( eSemantics == VS_TEX )
		{
			m_nOffset += 8;
		}

		m_pBuffer = realloc( m_pBuffer, m_nVertexCount * m_nOffset );
	}

	void HardwareVertexBuffer::RemoveVertexSemantic( const VertexSemantics& eSemantics )
	{
		m_lVertexSemantic.Remove( eSemantics );
	}

	int HardwareVertexBuffer::GetSizeBuffer( void )
	{
		return m_nVertexCount * m_nOffset;
	}

	int HardwareVertexBuffer::GetVertexCount( void )
	{
		return m_nVertexCount;
	}

	int HardwareVertexBuffer::GetOffsetBuffer( void )
	{
		return m_nOffset;
	}
}