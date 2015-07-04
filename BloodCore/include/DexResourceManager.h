#pragma once

#include <DexPreCompletion.h>
#include <DexCommon.h>

namespace Dex
{
	class D_EXPORT ResourceManager
	{
	public:
		ResourceManager( void );
		~ResourceManager( void );

		FileStream* LoadResource( const String& cName );

		bool CreateDexFile( const String& cName );

		void AddResourceLocation( const String& cLactation, const String& eType );
		void RemoveResourceLocation( const String& cLactation );

	private:
		typedef std::map< String, ArchiveFactory* >		_lPathResource;
		typedef std::vector< ArchiveFactory* >			_lArchive;

		_lArchive					m_lArchive;
		_lPathResource				m_lResource;
	};
}