#include <DexResourceManager.h>
#include <DexFileArchive.h>

namespace Dex
{
	ResourceManager::ResourceManager( void )
	{
	}

	ResourceManager::~ResourceManager( void )
	{
	}

	FileStream* ResourceManager::LoadResource( const String& name )
	{
		return m_lResource[name]->Open( name );
	}

	bool ResourceManager::CreateDexFile( const String& cName )
	{
		return true;
	}

	void ResourceManager::AddResourceLocation( const String& cLactation, const String& eType )
	{
		ArchiveFactory* pArchive = 0;

		if ( eType == "File" )
		{
			pArchive = new FileArchive( cLactation );
		}
		else if ( eType == "Zip" )
		{
			//pArchive = new ZipArchive( cLactation );
		}

		assert( pArchive );
		m_lArchive.push_back( pArchive );

		const _lString& lFile = pArchive->GetFileList();
		for ( int i = 0; i < lFile.Size(); ++i )
		{
			m_lResource[lFile[i]] = pArchive;
		}
	}

	void ResourceManager::RemoveResourceLocation( const String& cLactation )
	{
		ArchiveFactory* pArchive = 0;

		for ( size_t i = 0; i < m_lArchive.size(); ++i )
		{
			if ( m_lArchive.at( i )->GetLactation() == cLactation )
			{
				pArchive = m_lArchive[i];
				break;
			}
		}

		const _lString& lFile = pArchive->GetFileList();
		for ( int i = 0; i < lFile.Size(); ++i )
		{
			m_lResource.erase( lFile[i] );
		}

		delete pArchive;
	}
}