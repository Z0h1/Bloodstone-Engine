#pragma once

#include "DexPreCompletion.h"
#include "DexCoreObject.h"

namespace Dex
{
	typedef std::vector< std::pair<String, String> >	_Configs;

	class D_EXPORT ConfigFile : public CoreObject
	{
	public:
		ConfigFile(const String& configfile, OFStream* logger);
		~ConfigFile();

		const _Configs& Get(void) { return mConfigs; };

	private:
		IFStream	mFile;
		_Configs	mConfigs;
	};
}