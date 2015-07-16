#include "DexRenderSystem.h"

namespace Dex
{
	RenderSystem::RenderSystem(const string& c_name, ofstream* logger, const SystemsType st, bool fw)
		: ISystem(c_name, logger, st, fw)
	{
		m_nActiveAdapter = "";
		m_bInit = false;
	}

	RenderSystem::~RenderSystem(void)
	{
	}

	void RenderSystem::SetActiveAdapter(const string& adapter)
	{
		m_nActiveAdapter = adapter;

		ISetAdapter();
	}

	void RenderSystem::RenderAllWindow(void)
	{
		for (auto window : m_lWindow)
		{
			RenderOneWindow(window.second);
		}
	}

	void RenderSystem::ReloadAllWindows(void)
	{
		for (auto window : m_lWindow)
		{
			ReloadWindow(window.second);
		}
	}
}