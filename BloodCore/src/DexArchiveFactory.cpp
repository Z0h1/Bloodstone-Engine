#include "DexArchiveFactory.h"

namespace Dex
{
	const _lString& ArchiveFactory::GetFileList( void )
	{
		return m_lFile;
	}

	const ArchiveType& ArchiveFactory::GetType( void )
	{
		return m_eType;
	}

	const string& ArchiveFactory::GetLactation( void )
	{
		return m_cLactation;
	}
}