#pragma once

#include "DexPreCompletion.h"
#include "DexCoreObject.h"

namespace DEX
{
	class D_EXPORT CoreFile : public CoreObject
	{
	public:
		CoreFile(ofstream* logger, Folder* pParent, const FileFormat eFormat, const string& cPath, const string& cName);
		virtual ~CoreFile(void);

		const FileFormat GetFormat(void);
		const string& GetName(void);
		const string& GetPath(void);
		Folder* GetParent(void);

	protected:
		FileFormat		m_eFormat;
		string			m_cPath;
		string			m_cName;
		Folder*			m_pParent;
	};
}