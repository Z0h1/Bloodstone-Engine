#include <DexRenderSystem.h>

namespace Dex
{
	IRenderSystem::IRenderSystem(const String& c_name, const SystemsType st, bool fw)
		: ISystem(c_name, st, fw)
	{
	}

	IRenderSystem::~IRenderSystem(void)
	{
	}

	void IRenderSystem::SetActiveAdapter(UInt32 adapter)
	{
		m_Adapter = adapter;
	}
}