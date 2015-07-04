#pragma once

#include "DexPreCompletion.h"
#include "DexArchiveFactory.h"

namespace Dex
{
	class D_EXPORT FileArchive : public ArchiveFactory
	{
	public:
		FileArchive( const string& cLocation );
		~FileArchive( void );

		FileStream* Open( const string& cResource );
	};
}

