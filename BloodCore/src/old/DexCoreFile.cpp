#include "DexCoreFile.h"
#include "DexFolder.h"

namespace DEX
{
	CoreFile::CoreFile(ofstream* logger, Folder* pParent, const FileFormat eFormat, const string& cPath, const string& cName)
		: CoreObject(cName, logger, WorkPriority::WP_FILE)
	{
		m_eFormat = eFormat;
		m_cPath = cPath;
		m_cName = cName;
		m_pParent = pParent;

		if (m_pParent)
		{
			m_pParent->AddCoreFile(this);
		}
	}

	CoreFile::~CoreFile(void)
	{
		if (m_pParent)
		{
			m_pParent->RemoveCoreFile(m_cName);
		}
	}

	const FileFormat CoreFile::GetFormat(void)
	{
		return m_eFormat;
	}

	const string& CoreFile::GetName(void)
	{
		return m_cName;
	}

	const string& CoreFile::GetPath(void)
	{
		return m_cPath;
	}

	Folder* CoreFile::GetParent(void)
	{
		return m_pParent;
	}
}