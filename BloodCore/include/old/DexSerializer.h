#pragma once

#include "DexPreCompletion.h"

namespace DEX
{
	class D_EXPORT Serializer
	{
	public:
		Serializer(const string& path);
		virtual ~Serializer();

		bool IsOpen(void);
		bool Eof(void);

		// Read
		void ReadByte(void* pData);
		void GetLine(string& cString);
		void ReadLine(string& pData, _32un nSize);
		void ReadCharPtr(void* pData, _32un nSize);
		void ReadString(string& pData);
		void ReadHeader(void* pData);
		void ReadInt(void* pData);
		void ReadUInt(void* pData);
		void ReadBool(void* pData);
		void ReadFloat(void* pData);
		void ReadPtr(void* pData, _32un nSize);

		// Write
		void WriteByte(unsigned char pData);
		void WriteCharPtr(const char* pData, _32un size);
		void WriteString(const string& pData);
		void WriteHeader(int pData);
		void WriteUInt(_32un pData);
		void WriteInt(int pData);
		void WriteBool(bool pData);
		void WriteFloat(float pData);
		void WritePtr(const void* pData, _32un nSize);

		bool Open(long eOpenMode);
		void Close(void);

	protected:
		string			mPath;

	private:
		void Read(void* pBuf, size_t nCount);
		void Write(const void* pBuf, size_t nCount);
		
		fstream			m_pStream;
	};
}