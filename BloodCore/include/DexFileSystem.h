#pragma once

#include "DexPreCompletion.h"
#include "DexSystem.h"

namespace Dex
{
	typedef list< string >		_lPath;

	class D_EXPORT FileSystem : public ISystem
	{
	public:
		FileSystem(ofstream* logger, bool fw = false);
		~FileSystem(void);

		static Folder* GetFolder(CoreFile *pCFile);

		// Load and Create Folder or File
		CoreFile* GetCFile(const string& cPath, bool bCreate = false, const FileFormat& eFormat = FF_UNKNOWN);
		bool CheckCFile(const string& cPath);

		void Fill(const string& cPath, _lPath& lPath, string& cName);

		void Remove(CoreFile* pCfile);
		void Remove(const string& cPath);

		void AddResourceFolder(const string& cFolder);
		void RemoveResourceFolder(const string& cFolder);

		void GetlFile(_lCoreFile& lFile);

	private:
		Folder* OpenFolder(const string& cPath, Folder* pParent = nullptr);

		_lCoreFile				m_lResource;
	};
}