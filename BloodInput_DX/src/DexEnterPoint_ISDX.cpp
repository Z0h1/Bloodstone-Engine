#include "DexCore.h"
#include "DexInputSystem_DX.h"

namespace Dex
{
	extern "C"
	{
		void D_EXPORT_ISDX Start_DexDynamicLibrary(Core* pCore)
		{
			pCore->AddSystem(new InputSystem_DX(pCore->GetLogger()));
		}

		void D_EXPORT_ISDX Stop_DexDynamicLibrary(Core* pCore)
		{
			ISystem* sys = pCore->GetSystem(SystemsType::SYSTEM_INPUT_DX);

			if (sys) {
				pCore->RemoveSystem(sys);

				delete sys;
			}
		}
	}
}