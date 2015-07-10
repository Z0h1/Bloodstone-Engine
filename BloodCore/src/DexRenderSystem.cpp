#include "DexRenderSystem.h"

namespace Dex
{
	IRenderSystem::IRenderSystem(const string& c_name, ofstream* logger, const SystemsType st, bool fw)
		: ISystem(c_name, logger, st, fw)
	{
	}

	IRenderSystem::~IRenderSystem(void)
	{
	}

	void IRenderSystem::SetActiveAdapter(UInt32 adapter)
	{
		m_nAdapter = adapter;
	}
}