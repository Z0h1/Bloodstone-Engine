#pragma once

#include "DexPreCompletion.h"
#include "DexCommon.h"
#include "DexCoreObject.h"

namespace Dex
{
	class D_EXPORT Serializer : public CoreObject
	{
	public:
		Serializer(const String& c_name, bool fw = true);
		virtual ~Serializer();

		// Read
		void ReadHeader( void* pData );
		void ReadInt( void* pData );
		void ReadUInt( void* pData );
		void ReadBool( void* pData );
		void ReadPtr( void* pData, unsigned int nSize );

		// Write
		void WriteHeader( int pData );
		void WriteUInt( UInt32 pData );
		void WriteInt( int pData );
		void WriteBool( bool pData );
		void WritePtr( const void* pData, unsigned int nSize );

		void SetResource( const String& cResource );
		void SetStream( DataStream* pStream );

	private:
		DataStream*		m_pStream;
	};
}