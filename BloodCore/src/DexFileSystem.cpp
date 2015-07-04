#include "DexFileSystem.h"

namespace Dex
{
	FileSystem::FileSystem(ofstream* logger, bool fw)
		: ISystem("DEX_FILE_SYSTEM", logger, SystemsType::SYSTEM_FILE_DEX, fw)
	{

	}

	FileSystem::~FileSystem()
	{

	}

	void FileSystem::AddResourceFolder(const string & cFolder)
	{
		DrawLine("AddResourceFolder(" + cFolder + ")");
	}

	void FileSystem::RemoveResourceFolder(const string & cFolder)
	{
		DrawLine("RemoveResourceFolder(" + cFolder + ")");
	}
}