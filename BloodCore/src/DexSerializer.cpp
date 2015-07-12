#include "DexSerializer.h"
#include "DexStream.h"

namespace Dex
{
	Serializer::Serializer(const string& c_name, ofstream* logger, const string& path)
		: CoreObject(c_name, logger, WorkPriority::WP_FILE)
	{
		m_cPath = path;
	}

	Serializer::~Serializer()
	{
		Close();
	}

	void Serializer::GetLine(string& cString)
	{
		if (m_pStream.is_open())
		{
			char cBuffer[256];
			m_pStream.getline(cBuffer, 256);

			cString.append(cBuffer);
		}
	}

	bool Serializer::Eof(void)
	{
		return m_pStream.eof();
	}

	void Serializer::Read(void* pBuf, size_t nCount)
	{
		if (m_pStream.is_open())
		{
			m_pStream.read(static_cast< char* >(pBuf), static_cast< streamsize >(nCount));
		}
	}

	void Serializer::Write(const void* pBuf, size_t nCount)
	{
		if (m_pStream.is_open())
		{
			m_pStream.write(static_cast< const char* >(pBuf), static_cast< streamsize >(nCount));
		}
	}

	void Serializer::ReadCharPtr(void* pData, UInt32 nSize)
	{
		Read(pData, nSize);
	}

	void Serializer::ReadString(void* pData, UInt32 nSize)
	{
		Read(pData, nSize);
	}

	void Serializer::ReadHeader(void* pData)
	{
		Read(pData, sizeof(int));
	}

	void Serializer::ReadInt(void* pData)
	{
		Read(pData, sizeof(int));
	}

	void Serializer::ReadUInt(void* pData)
	{
		Read(pData, sizeof(UInt32));
	}

	void Serializer::ReadBool(void* pData)
	{
		Read(pData, sizeof(bool));
	}

	void Serializer::ReadFloat(void* pData)
	{
		Read(pData, sizeof(float));
	}

	void Serializer::ReadPtr(void* pData, UInt32 nSize)
	{
		Read(pData, nSize);
	}

	void Serializer::WriteCharPtr(const char* pData)
	{
		Write(&pData, sizeof(pData));
	}

	void Serializer::WriteString(const string& pData)
	{
		Write(&pData, pData.size());
	}

	void Serializer::WriteHeader(int pData)
	{
		WriteInt(pData);
	}

	void Serializer::WriteInt(int pData)
	{
		Write(&pData, sizeof(int));
	}

	void Serializer::WriteUInt(UInt32 pData)
	{
		Write(&pData, sizeof(UInt32));
	}

	void Serializer::WriteBool(bool pData)
	{
		Write(&pData, sizeof(bool));
	}

	void Serializer::WriteFloat(float pData)
	{
		Write(&pData, sizeof(float));
	}

	void Serializer::WritePtr(const void* pData, UInt32 nSize)
	{
		Write(pData, nSize);
	}

	bool Serializer::Open(long eOpenMode)
	{
		ios::openmode mode;

		if (eOpenMode & OPEN_MODE_READ)
		{
			mode = ios::in;
		}

		if (eOpenMode & OPEN_MODE_WRITE)
		{
			mode = ios::out;
		}

		if (eOpenMode & OPEN_MODE_BINARY)
		{
			mode |= ios::binary;
		}

		m_pStream.open(m_cPath.c_str(), mode);

		if (!m_pStream.is_open())
		{
			DrawLine("Open: Невозможно открыть файл " + mObjectName, MT_ERROR);
			return false;
		}

		return true;
	}

	void Serializer::Close(void)
	{
		if (m_pStream.is_open())
		{
			m_pStream.close();
		}
	}
}