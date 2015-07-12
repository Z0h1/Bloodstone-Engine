#include "DexFolder.h"

namespace Dex
{
	Folder::Folder(ofstream* logger, FolderType type, FileFormat format, Folder* pParent, const string& cPath, const string& cName)
		: CoreFile(logger, pParent, format, cPath, cName)
	{
		m_eType = type;
	}

	Folder::~Folder(void)
	{
		_lCoreFile::iterator itFile = m_lResource.begin();
		while (itFile != m_lResource.end()) {
			CoreFile*  file = itFile->second;

			itFile = m_lResource.erase(itFile);

			delete file;
			itFile = m_lResource.begin();
		}

		if (m_pParent)
		{
			m_pParent->RemoveCoreFile(m_cName);
		}
	}

	void Folder::AddCoreFile(CoreFile* pCF)
	{
		m_lResource.insert(_lCoreFile::value_type(pCF->GetName(), pCF));
	}

	void Folder::RemoveCoreFile(const string& cPath)
	{
		_lCoreFile::iterator it = m_lResource.find(cPath);

		if (it != m_lResource.end()) {
			m_lResource.erase(it);
		}
	}

	_lCoreFile::size_type Folder::GetCountFile(void)
	{
		return m_lResource.size();
	}

	void Folder::GetlFile(_lCoreFile& lFile)
	{
		lFile = m_lResource;
	}

	CoreFile* Folder::GetCFile(const string& cName)
	{
		if (m_lResource.find(cName) != m_lResource.end())
		{
			return m_lResource[cName];
		}

		return nullptr;
	}
}