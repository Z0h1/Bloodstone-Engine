#pragma once

#include "DexPreCompletion.h"
#include "DexCoreObject.h"

namespace Dex
{
	class D_EXPORT DynamicLibrary : public CoreObject
	{
	public:
		DynamicLibrary(const string& filename, ofstream* logger);
		~DynamicLibrary(void);

		void* GetAddress(const string& funcname);
		bool CheckWork(void) const { return m_Work; }

	private:
		HINSTANCE	m_hDll;
		bool		m_Work;
		string		m_FileName;
	};
}