#pragma once

#include "DexPreCompletion.h"
#include "DexCoreObject.h"

namespace Dex
{
	class D_EXPORT DynamicLibrary : public CoreObject
	{
	public:
		DynamicLibrary( const String& filename );
		~DynamicLibrary( void );

		void* GetAddress( const String& funcname );
		bool CheckWork( void ) const { return m_Work; }

	private:
		HINSTANCE	m_hDll;
		bool		m_Work;
		String		m_FileName;
	};
}