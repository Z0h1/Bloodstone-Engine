#include "DexStream.h"

namespace DEX
{
	DataStream::DataStream(string cName)
	{
		m_cName = cName;
	}

	DataStream::~DataStream(void)
	{
	}

	FileStream::FileStream(string cName, string cFile, const OpenMode& eOpenMode)
		: DataStream(cName)
	{

		ios::openmode mode = ios::binary;

		if (eOpenMode == OM_READ)
		{
			mode |= ios::in;
		}
		else
		{
			mode |= ios::out;
		}

		m_pFileStream.open(cFile.c_str(), mode);

		if (!m_pFileStream.is_open())
		{
			//DrawLine( "FileStream: Невозможно открыть файл " + cFile, EZ_ERROR );
		}
	}

	FileStream::~FileStream(void)
	{
		Close();
	}

	void FileStream::Read(void* pBuf, size_t nCount)
	{
		m_pFileStream.read(static_cast<char*>(pBuf), static_cast<streamsize>(nCount));
	}

	void FileStream::Write(const void* pBuf, size_t nCount)
	{
		if (m_pFileStream)
		{
			m_pFileStream.write(static_cast<const char*>(pBuf), static_cast<streamsize>(nCount));
		}
	}

	void FileStream::Close(void)
	{
		m_pFileStream.close();
	}
}