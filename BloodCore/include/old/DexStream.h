#pragma once

#include "DexPreCompletion.h"

namespace DEX
{
	class D_EXPORT DataStream
	{
	public:
		DataStream(string cName);
		virtual ~DataStream(void);

		virtual void Read(void* pBuf, size_t nCount) = 0;
		virtual void Write(const void* pBuf, size_t nCount) = 0;

		virtual void Close(void) = 0;

	protected:
		string		m_cName;
	};

	class D_EXPORT FileStream : public DataStream
	{
	public:
		FileStream(string cName, string cFile, const OpenMode& eOpenMode);
		~FileStream(void);

		void Read(void* pBuf, size_t nCount);
		void Write(const void* pBuf, size_t nCount);

		void Close(void);

	private:
		fstream	m_pFileStream;
	};
}