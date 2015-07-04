#pragma once

#include <DexPreCompletion.h>
#include <DexCommon.h>

namespace Dex
{
	class D_EXPORT DataStream
	{
	public:
		DataStream( String cName );
		virtual ~DataStream( void );

		virtual void Read( void* pBuf, size_t nCount ) = 0;
		virtual void Write( const void* pBuf, size_t nCount ) = 0;

		virtual void Close( void ) = 0;

	protected:
		String		m_cName;
	};

	class D_EXPORT FileStream : public DataStream
	{
	public:
		FileStream( String cName, String cFile, const OpenMode& eOpenMode );
		~FileStream( void );

		void Read( void* pBuf, size_t nCount );
		void Write( const void* pBuf, size_t nCount );

		void Close( void );

	private:
		std::fstream	m_pFileStream;
	};
}