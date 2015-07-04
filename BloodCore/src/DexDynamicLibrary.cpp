#include "DexDynamicLibrary.h"
#include "DexCore.h"

namespace Dex
{
	DynamicLibrary::DynamicLibrary(const string& filename, ofstream* logger)
		: CoreObject("DynamicLibrary_" + filename, logger, WorkPriority::WP_MAIN)
	{
		m_Work = true;
		m_FileName = filename;

		if ( filename.substr( filename.length() - 4, 4 ) != ".dll" )
		{
			m_FileName += ".dll";
		}

		m_hDll = LoadLibraryEx( m_FileName.c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH );

		if ( !m_hDll )
		{
			LPVOID ErrorBuffer; 
			FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
				NULL, GetLastError(), MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), (LPTSTR) &ErrorBuffer, 0, NULL );

			string error = (char*)ErrorBuffer;
			LocalFree( ErrorBuffer );

			DrawLine("DynamicLibrary: " + error, MT_ERROR );
			m_Work = false;
		}
	}

	DynamicLibrary::~DynamicLibrary( void )
	{
		if ( !FreeLibrary( m_hDll ) )
		{
			DrawLine("DynamicLibrary: ���������� ��������� ������", MT_ERROR );
		}
	}

	void* DynamicLibrary::GetAddress( const string& funcname )
	{
		return GetProcAddress( m_hDll, funcname.c_str() );
	}
}