#include "DexSerializer.h"

namespace Dex
{
	Serializer::Serializer(const string& path)
	{
		mPath = path;
	}

	Serializer::~Serializer()
	{
		Close();
	}

	bool Serializer::IsOpen(void)
	{
		return m_pStream.is_open();
	}

	void Serializer::ReadLine(string& cString, _intun nSize)
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

	void Serializer::ReadCharPtr(void* pData, _intun nSize)
	{
		Read(pData, nSize);
	}

	void Serializer::ReadString(string& pData)
	{
		_intun read_size = 0;
		ReadUInt(&read_size);

		unique_ptr<char[], default_delete<char[]> > read_charptr(new char[read_size]);
		Read(read_charptr.get(), read_size);

		strncpy_s(read_charptr.get(), read_size + 1, read_charptr.get(), read_size);
		pData = read_charptr.get();

		read_charptr.release();
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
		Read(pData, sizeof(_intun));
	}

	void Serializer::ReadBool(void* pData)
	{
		Read(pData, sizeof(bool));
	}

	void Serializer::ReadFloat(void* pData)
	{
		Read(pData, sizeof(float));
	}

	void Serializer::ReadPtr(void* pData, _intun nSize)
	{
		Read(pData, nSize);
	}

	void Serializer::ReadByte(void* pData)
	{
		Read(pData, sizeof(unsigned char));
	}

	void Serializer::WriteByte(unsigned char pData)
	{
		Write(&pData, sizeof(unsigned char));
	}

	void Serializer::WriteCharPtr(const char* pData, _intun size)
	{
		Write(pData, size);
	}

	void Serializer::WriteString(const string& pData)
	{
		_intun write_size = pData.size();
		WriteUInt(write_size);

		WriteCharPtr(pData.c_str(), write_size);
	}

	void Serializer::WriteHeader(int pData)
	{
		WriteInt(pData);
	}

	void Serializer::WriteInt(int pData)
	{
		Write(&pData, sizeof(int));
	}

	void Serializer::WriteUInt(_intun pData)
	{
		Write(&pData, sizeof(_intun));
	}

	void Serializer::WriteBool(bool pData)
	{
		Write(&pData, sizeof(bool));
	}

	void Serializer::WriteFloat(float pData)
	{
		Write(&pData, sizeof(float));
	}

	void Serializer::WritePtr(const void* pData, _intun nSize)
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

		m_pStream.open(mPath.c_str(), mode);

		return m_pStream.is_open();
	}

	void Serializer::Close(void)
	{
		if (m_pStream.is_open())
		{
			m_pStream.close();
		}
	}
}