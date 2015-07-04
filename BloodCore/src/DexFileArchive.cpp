#include "DexFileArchive.h"

namespace Dex
{
	FileArchive::FileArchive( const String& cLocation )
	{
		m_eType = AT_FILE;
		m_cLactation = cLocation;

		String full_path = m_cLactation + "/*";

		_finddata_t data;
		intptr_t nHandleFile = _findfirst( full_path.c_str(), &data );

		if ( nHandleFile != -1 )
		{
			int res = 0;
			do
			{
				if ( data.attrib != _A_SUBDIR )
				{
					m_lFile.Add( data.name );
				}

				res = _findnext( nHandleFile, &data );
			}
			while ( res == 0 );
		}

		_findclose( nHandleFile );
	}

	FileArchive::~FileArchive( void )
	{
	}

	FileStream* FileArchive::Open( const String& cResource )
	{
		String cPath = m_cLactation + "/" + cResource;

		return new FileStream( cResource, cPath, OM_READ );
	}
}