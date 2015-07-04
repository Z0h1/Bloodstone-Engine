#pragma once

#include "DexPreCompletion.h"
#include "DexSystem.h"

namespace Dex
{
	class D_EXPORT FileSystem : public ISystem
	{
	public:
		FileSystem(ofstream* logger, bool fw = false);
		~FileSystem();

		void AddResourceFolder(const string& cFolder);
		void RemoveResourceFolder(const string& cFolder);

	private:

	};
}