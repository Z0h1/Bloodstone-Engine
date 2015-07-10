#include "DexDynamicLibrary.h"
#include "Windows.h"

namespace Dex
{
	DynamicLibrary::DynamicLibrary(const string& filename, ofstream* logger)
		: CoreObject(filename, logger, WorkPriority::WP_MAIN)
	{
		m_Work = true;
		mObjectName = filename;

		if (filename.substr(filename.length() - 4, 4) != ".dll")
		{
			mObjectName += ".dll";
		}

		m_hDll = (int)LoadLibraryEx(mObjectName.c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);

		if (!m_hDll)
		{
			LPVOID ErrorBuffer;
			FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&ErrorBuffer, 0, NULL);

			string error = (char*)ErrorBuffer;
			LocalFree(ErrorBuffer);

			DrawLine("DynamicLibrary: " + error.substr(0, error.length() - 2), MT_ERROR);

			m_Work = false;
		}
	}

	DynamicLibrary::~DynamicLibrary(void)
	{
		if (!FreeLibrary((HMODULE)m_hDll))
		{
			DrawLine("DynamicLibrary: Невозможно выгрузить модуль", MT_ERROR);
		}
	}

	void* DynamicLibrary::GetAddress(const char* funcname)
	{
		return GetProcAddress((HMODULE)m_hDll, funcname);
	}
}