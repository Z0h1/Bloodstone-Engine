#pragma once

#include <DexPreCompletion.h>
#include <DexArchiveFactory.h>

namespace Dex
{
	class D_EXPORT FileArchive : public ArchiveFactory
	{
	public:
		FileArchive( const String& cLocation );
		~FileArchive( void );

		FileStream* Open( const String& cResource );
	};
}

