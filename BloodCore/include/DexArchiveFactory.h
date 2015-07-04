#pragma once

#include <DexPreCompletion.h>
#include <DexCommon.h>

namespace Dex
{
	class D_EXPORT ArchiveFactory
	{
	public:
		virtual FileStream* Open( const String& cResource ) = 0;

		const _lString& GetFileList( void );
		const ArchiveType& GetType( void );
		const String& GetLactation( void );

	protected:
		_lString			m_lFile;
		ArchiveType			m_eType;
		String				m_cLactation;
	};
}

