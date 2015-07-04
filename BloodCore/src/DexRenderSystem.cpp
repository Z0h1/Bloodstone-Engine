#include <DexRenderSystem.h>

namespace Dex
{
	IRenderSystem::IRenderSystem(const String& c_name, OFStream* logger, const SystemsType st, bool fw)
		: ISystem(c_name, logger, st, fw)
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