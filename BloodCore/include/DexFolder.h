#pragma once

#include "DexPreCompletion.h"
#include "DexCoreFile.h"

namespace Dex
{
	class D_EXPORT Folder : public CoreFile
	{
	public:
		Folder(ofstream* logger, FolderType type, FileFormat format, Folder* pParent, const string& cPath, const string& cName);
		~Folder(void);

		void AddCoreFile(CoreFile* pCF);
		void RemoveCoreFile(const string& cPath);

		_lCoreFile::size_type GetCountFile(void);

		void GetlFile(_lCoreFile& lFile);

		CoreFile* GetCFile(const string& cName);

	private:
		FolderType		m_eType;
		_lCoreFile		m_lResource;
	};
}