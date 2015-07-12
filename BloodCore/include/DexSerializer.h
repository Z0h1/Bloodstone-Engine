#pragma once

#include "DexPreCompletion.h"
#include "DexCoreObject.h"

namespace Dex
{
	class D_EXPORT Serializer : public CoreObject
	{
	public:
		Serializer(const string& c_name, ofstream* logger, const string& path);
		virtual ~Serializer();

		void GetLine(string& cString);
		bool Eof(void);

		// Read
		void ReadCharPtr(void* pData, UInt32 nSize);
		void ReadString(void* pData, UInt32 nSize);
		void ReadHeader(void* pData);
		void ReadInt(void* pData);
		void ReadUInt(void* pData);
		void ReadBool(void* pData);
		void ReadFloat(void* pData);
		void ReadPtr(void* pData, UInt32 nSize);

		// Write
		void WriteCharPtr(const char* pData);
		void WriteString(const string& pData);
		void WriteHeader(int pData);
		void WriteUInt(UInt32 pData);
		void WriteInt(int pData);
		void WriteBool(bool pData);
		void WriteFloat(float pData);
		void WritePtr(const void* pData, UInt32 nSize);

		bool Open(long eOpenMode);
		void Close(void);

	private:
		void Read(void* pBuf, size_t nCount);
		void Write(const void* pBuf, size_t nCount);
		
		string			m_cPath;
		fstream			m_pStream;
	};
}