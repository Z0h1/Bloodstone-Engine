#include <DexHardwareBufferData.h>
#include <DexHardwareVertexBuffer.h>
#include <DexHardwareIndexBuffer.h>

namespace Dex
{
	HardwareBufferData::HardwareBufferData( void )
	{
		m_pIndexBuffer = 0;
	}

	HardwareBufferData::~HardwareBufferData( void )
	{
	}

	HardwareVertexBuffer* HardwareBufferData::CreateVertexBuffer( unsigned int nVertexCount )
	{
		HardwareVertexBuffer* pVertexBuffer = new HardwareVertexBuffer( nVertexCount );
		m_lVertexBuffer.Add( pVertexBuffer );

		return pVertexBuffer;
	}

	HardwareIndexBuffer* HardwareBufferData::CreateIndexBuffer( unsigned int nIndexCount, const IndexType& eType )
	{
		HardwareIndexBuffer* pIndexBuffer = new HardwareIndexBuffer( nIndexCount, eType );
		m_pIndexBuffer = pIndexBuffer;

		return m_pIndexBuffer; 
	}

	const g_lVertexBuffer& HardwareBufferData::GetListVertexBuffer( void ) const
	{
		return m_lVertexBuffer;
	}

	int HardwareBufferData::GetVertexBufferCount( void ) const
	{
		return m_lVertexBuffer.Size();
	}

	HardwareIndexBuffer* HardwareBufferData::GetIndexBuffer( void ) const
	{
		return m_pIndexBuffer;
	}
}