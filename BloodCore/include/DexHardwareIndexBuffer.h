#pragma once

#include <DexPreCompletion.h>
#include <DexCommon.h>
#include <DexHardwareBuffer.h>

namespace Dex
{
	class D_EXPORT HardwareIndexBuffer : public HardwareBuffer
	{
	public:
		HardwareIndexBuffer( unsigned int nIndexCount, const IndexType& eType );
		~HardwareIndexBuffer( void );

		int GetIndexCount( void );
		unsigned int GetSizeIndex( void );
		const IndexType& GetIndexType( void );

	protected:
		unsigned int			m_nIndexCount;
		int						m_nOffset;

		IndexType				m_eIndexType;
	};
}