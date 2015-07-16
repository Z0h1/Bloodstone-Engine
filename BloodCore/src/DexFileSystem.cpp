#include "DexFileSystem.h"
#include "DexFolder.h"
#include "DexFile.h"
#include "Windows.h"

namespace Dex
{
	FileSystem::FileSystem(ofstream* logger, bool fw)
		: ISystem("DEX_FILE_SYSTEM", logger, SystemsType::SYSTEM_FILE_DEX, fw)
	{

	}

	FileSystem::~FileSystem(void)
	{
		_lCoreFile::iterator itFile = m_lResource.begin();
		while (itFile != m_lResource.end()) {
			CoreFile*  file = itFile->second;

			itFile = m_lResource.erase(itFile);

			delete file;
			itFile = m_lResource.begin();
		}
	}

	Folder* FileSystem::GetFolder(CoreFile *pCFile)
	{
		if (pCFile)
		{
			if (pCFile->GetFormat() == FF_FOLDER)
			{
				return static_cast< Folder* >(pCFile);
			}
		}

		return nullptr;
	}

	CoreFile* FileSystem::GetCFile(const string& cPath, bool bCreate, const FileFormat& eFormat)
	{
		_lPath lPath;
		string::size_type cSlash_POS = string::npos;
		CoreFile *pCFile = nullptr;

		string cFileName;
		Fill(cPath, lPath, cFileName);

		if (cFileName == cPath)
		{
			if (m_lResource.find(cFileName) == m_lResource.end())
			{
				if (bCreate)
				{
					cSlash_POS = cFileName.find_first_of(".", 0);
					if (cSlash_POS == string::npos)
					{
						pCFile = new Folder(mOutFileStream, FT_FOLDER, FF_FOLDER, 0, cPath, cFileName);
						CreateDirectory(cPath.c_str(), nullptr);
						DrawLine("GetCFile: Создание папки " + cPath);

						m_lResource.insert(_lCoreFile::value_type(cFileName, pCFile));

						return pCFile;
					}
					else
					{
						return nullptr;
					}
				}
				else
				{
					return nullptr;
				}
			}
			else
			{
				return m_lResource[cFileName];
			}
		}

		Folder *pFolder = nullptr, *pBufferFolder = nullptr;
		string cNameFolder(*lPath.begin());
		pFolder = (Folder*)m_lResource[cNameFolder];
		pBufferFolder = pFolder;

		lPath.pop_front();

		while (!lPath.empty())
		{
			cNameFolder = *lPath.begin();
			lPath.pop_front();

			if (pFolder->GetCFile(cNameFolder))
			{
				pFolder = (Folder*)pFolder->GetCFile(cNameFolder);
			}
			else
			{
				if (bCreate)
				{
					string cNEWPath(pBufferFolder->GetPath() + "/" + cNameFolder);

					pFolder = new Folder(mOutFileStream, FT_FOLDER, FF_FOLDER, pBufferFolder, cNEWPath, cNameFolder);

					CreateDirectory(cNEWPath.c_str(), nullptr);
					DrawLine("ResourceManager:GetCFile Создание папки " + cPath);
				}
				else
				{
					return nullptr;
				}
			}

			pBufferFolder = pFolder;
		}

		pCFile = pFolder->GetCFile(cFileName);

		if (!pCFile)
		{
			if (bCreate)
			{
				cSlash_POS = cFileName.find_first_of(".", 0);
				if (cSlash_POS != string::npos)
				{
					//pCFile = new File(mOutFileStream, pFolder, eFormat, cPath, cFileName);

					ofstream pSTLFile(cPath);
					pSTLFile.close();
					DrawLine("ResourceManager:GetCFile Создание файла " + cPath);
				}
				else
				{
					pCFile = new Folder(mOutFileStream, FT_FOLDER, FF_FOLDER, pFolder, cPath, cFileName);
					CreateDirectory(cPath.c_str(), nullptr);
					DrawLine("ResourceManager:GetCFile Создание папки " + cPath);
				}
			}
			else
			{
				return nullptr;
			}
		}

		return pCFile;
	}

	bool FileSystem::CheckCFile(const string& cPath)
	{
		if (GetCFile(cPath))
		{
			return true;
		}

		return false;
	}

	void FileSystem::Remove(const string& cPath)
	{
		CoreFile *pCF = GetCFile(cPath);

		if (pCF)
		{
			Remove(pCF);
		}
	}

	void FileSystem::Remove(CoreFile* pCfile)
	{
		if (pCfile->GetFormat() == FF_FOLDER)
		{
			Folder* pFolder = static_cast< Folder* >(pCfile);

			_lCoreFile new_lFile;
			pFolder->GetlFile(new_lFile);

			_lCoreFile::const_iterator itFile;

			for (itFile = new_lFile.begin(); itFile != new_lFile.end(); ++itFile)
			{
				Remove(itFile->second);
			}

			RemoveDirectory(pCfile->GetPath().c_str());
			DrawLine("ResourceManager:Remove Удаление директории " + pCfile->GetName());
		}
		else
		{
			remove(pCfile->GetPath().c_str());
			DrawLine("ResourceManager:Remove Удаление файла " + pCfile->GetName());
		}

		Folder* pFolder = pCfile->GetParent();

		if (!pFolder)
		{
			RemoveResourceFolder(pCfile->GetName());
		}
	}

	void FileSystem::AddResourceFolder(const string& cFolder)
	{
		if (m_lResource.find(cFolder) == m_lResource.end())
		{
			Folder *pFolder = OpenFolder(cFolder);

			if (pFolder)
			{
				m_lResource.insert(_lCoreFile::value_type(cFolder, pFolder));
			}
			else
			{
				DrawLine("ResourceManager:AddResourceFolder Папка " + cFolder + " не найдена!", MT_WARNING);
			}
		}
	}

	Folder* FileSystem::OpenFolder(const string& cPath, Folder* pParent)
	{
		_finddata_t data;
		Folder* pFolder = nullptr;

		string cFullPath(cPath + "/*");

		intptr_t nHandleFile = _findfirst(cFullPath.c_str(), &data);

		if (nHandleFile != -1)
		{
			string cName(cPath);
			string::size_type cSlash_POS = cName.find_first_of("/", 0);

			while (cSlash_POS != string::npos)
			{
				cName = cName.substr(cSlash_POS + 1, cName.length());

				cSlash_POS = cName.find_first_of("/", 0);
			}

			pFolder = new Folder(mOutFileStream, FT_FOLDER, FF_FOLDER, pParent, cPath, cName);

			int res = 0;

			do
			{
				string cFileName(data.name);

				switch (data.attrib)
				{
				case _A_SUBDIR:
				{
					if (cFileName != "." && cFileName != "..")
					{
						OpenFolder(cPath + "/" + cFileName, pFolder);
					}
				}
				break;

				case _A_NORMAL | _A_ARCH:
				{
					string cFileFormat;

					string::size_type d_pos = cFileName.find_first_of(".", 0);
					cFileFormat = cFileName.substr(d_pos + 1, cFileName.size());

					if (cFileFormat == "dexp")
					{
					}
					else
					{
						FileFormat eFormat = FF_UNKNOWN;
						CoreFile* pFile = nullptr;
						string cFilePath(cPath + "/" + cFileName);

						if (cFileFormat == "dexg")
						{
							eFormat = FF_DEXG;
						}
						else if (cFileFormat == "dexm")
						{
							eFormat = FF_DEXM;
						}
						else if (cFileFormat == "dexvoi")
						{
							eFormat = FF_DEXVOI;
						}
						else if (cFileFormat == "dexs")
						{
							eFormat = FF_DEXS;
						}

						pFile = new File(mOutFileStream, pFolder, cFilePath, cFileName);
					}
				}
				break;
				}

				res = _findnext(nHandleFile, &data);
			} while (res == 0);
		}

		_findclose(nHandleFile);

		return pFolder;
	}

	void FileSystem::Fill(const string& cPath, _lPath& lPath, string& cName)
	{
		string cBuffer(cPath);
		string::size_type cSlash_POS = string::npos;

		cSlash_POS = cBuffer.find_first_of("/", 0);

		if (cSlash_POS != string::npos)
		{
			string cElement;

			while (cSlash_POS != string::npos)
			{
				cElement = cBuffer.substr(0, cSlash_POS);
				cBuffer = cBuffer.substr(cSlash_POS + 1, cBuffer.length());

				lPath.push_back(cElement);

				cSlash_POS = cBuffer.find_first_of("/", 0);
			}
		}

		cName = cBuffer;
	}

	void FileSystem::RemoveResourceFolder(const string& cFolder)
	{
		_lCoreFile::iterator itFile = m_lResource.find(cFolder);
		if (itFile != m_lResource.end())
		{
			m_lResource.erase(itFile);
		}
	}

	void FileSystem::GetlFile(_lCoreFile& lFile)
	{
		lFile = m_lResource;
	}
}