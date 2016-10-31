#pragma once

#include "DexPreCompletion.h"
#include "DexCoreObject.h"

namespace DEX
{
	typedef vector< pair<string, string> >	_Configs;

	class D_EXPORT ConfigFile : public CoreObject
	{
	public:
		ConfigFile(const string& configfile, ofstream* logger);
		~ConfigFile();

		const _Configs& Get(void) { return mConfigs; };

	private:
		ifstream	mFile;
		_Configs	mConfigs;
	};
}