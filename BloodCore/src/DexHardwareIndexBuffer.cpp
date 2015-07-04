#include <DexHardwareIndexBuffer.h>

namespace Dex
{
	HardwareIndexBuffer::HardwareIndexBuffer( unsigned int nIndexCount, const IndexType& eType )
	{
		m_nIndexCount = nIndexCount;
		m_eIndexType = eType;

		m_nOffset = sizeof( unsigned long );
		if ( m_eIndexType == IT_16 )
		{
			m_nOffset = sizeof( unsigned short );
		}

		m_pBuffer = malloc( m_nIndexCount * m_nOffset );
	}

	HardwareIndexBuffer::~HardwareIndexBuffer( void )
	{
	}

	int HardwareIndexBuffer::GetIndexCount( void )
	{
		return m_nIndexCount;
	}

	unsigned int HardwareIndexBuffer::GetSizeIndex( void )
	{
		return m_nIndexCount * m_nOffset;
	}

	const IndexType& HardwareIndexBuffer::GetIndexType( void )
	{
		return m_eIndexType;
	}
}