#include "DexCore.h"
#include "DexRenderSystemD11_2.h"

namespace Dex
{
	extern "C"
	{
		void D_EXPORT_D11_1 Start_DexDynamicLibrary(Core* pCore)
		{
			pCore->AddSystem(new RenderSystemD11_2(pCore->GetLogger(), pCore->GetFileSystem()));
		}

		void D_EXPORT_D11_1 Stop_DexDynamicLibrary(Core* pCore)
		{
			ISystem* sysD11_1 = pCore->GetSystem(SystemsType::SYSTEM_RENDER_DIRECTX_11_1);

			if (sysD11_1) {
				pCore->RemoveSystem(sysD11_1);

				delete sysD11_1;
			}
		}
	}
}