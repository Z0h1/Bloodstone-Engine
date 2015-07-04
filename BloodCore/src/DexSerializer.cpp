#include <DexSerializer.h>
#include <DexCore.h>

namespace Dex
{
	Serializer::Serializer(const String& c_name, OFStream* logger, bool fw)
		: CoreObject(c_name, logger, WorkPriority::WP_STEP_1, fw)
	{
	}

	Serializer::~Serializer()
	{
	}

	void Serializer::ReadHeader( void* pData )
	{
		m_pStream->Read( pData, sizeof( int ) );
	}

	void Serializer::ReadInt( void* pData )
	{
		m_pStream->Read( pData, sizeof( int ) );
	}

	void Serializer::ReadUInt( void* pData )
	{
		m_pStream->Read( pData, sizeof( unsigned int ) );
	}

	void Serializer::ReadBool( void* pData )
	{
		m_pStream->Read( pData, sizeof( bool ) );
	}

	void Serializer::ReadPtr( void* pData, unsigned int nSize )
	{
		m_pStream->Read( pData, nSize );
	}

	void Serializer::WriteHeader( int pData )
	{
		WriteInt( pData );
	}

	void Serializer::WriteInt( int pData )
	{
		m_pStream->Write( &pData, sizeof( int ) );
	}

	void Serializer::WriteUInt( UInt32 pData )
	{
		m_pStream->Write( &pData, sizeof( unsigned int ) );
	}

	void Serializer::WriteBool( bool pData )
	{
		m_pStream->Write( &pData, sizeof( bool ) );
	}

	void Serializer::WritePtr( const void* pData, unsigned int nSize )
	{
		m_pStream->Write( pData, nSize );
	}

	void Serializer::SetResource( const String& cResource )
	{
		//m_pStream = Core::GetResourceManager()->LoadResource( cResource );
	}

	void Serializer::SetStream( DataStream* pStream )
	{
		m_pStream = pStream;
	}
}