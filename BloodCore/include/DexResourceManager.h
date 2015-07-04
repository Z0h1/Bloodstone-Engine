#pragma once

#include "DexPreCompletion.h"
#include "DexCommon.h"

namespace Dex
{
	class D_EXPORT ResourceManager
	{
	public:
		ResourceManager( void );
		~ResourceManager( void );

		FileStream* LoadResource( const string& cName );

		bool CreateDexFile( const string& cName );

		void AddResourceLocation( const string& cLactation, const string& eType );
		void RemoveResourceLocation( const string& cLactation );

	private:
		typedef map< string, ArchiveFactory* >		_lPathResource;
		typedef vector< ArchiveFactory* >			_lArchive;

		_lArchive					m_lArchive;
		_lPathResource				m_lResource;
	};
}