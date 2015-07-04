#include "DexCore.h"
#include "DexRenderSystemD3D9.h"

namespace Dex
{
	extern "C"
	{
		void D_EXPORT_D3D9 Start_DexDynamicLibrary(Core* pCore)
		{
			pCore->AddSystem(new RenderSystemD3D9(pCore->GetLogger()));
		}

		void D_EXPORT_D3D9 Stop_DexDynamicLibrary(Core* pCore)
		{
			ISystem* sysD3D9 = pCore->GetSystem(SystemsType::SYSTEM_RENDER_DIRECTX_9);

			if (sysD3D9 != nullptr) {
				pCore->RemoveSystem(sysD3D9);

				delete sysD3D9;
			}		
		}
	}
}