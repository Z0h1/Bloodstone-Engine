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

		void* GetAddress(const char* funcname);
		bool CheckWork(void) const { return m_Work; }

	private:
		int			m_hDll;
		bool		m_Work;
	};
}