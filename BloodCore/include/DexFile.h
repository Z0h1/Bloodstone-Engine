#pragma once

#include "DexPreCompletion.h"
#include "DexCoreFile.h"
#include "DexSerializer.h"

namespace Dex
{
	class D_EXPORT File : public CoreFile, public Serializer
	{
	public:
		File(ofstream* logger, Folder* pParent, const string& cPath, const string& cName);
		~File()
		{

		}
	};
}