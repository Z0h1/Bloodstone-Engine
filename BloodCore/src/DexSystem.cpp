#include "DexSystem.h"

namespace Dex
{
	ISystem::ISystem(const string& c_name, ofstream* logger, const SystemsType st, bool fw)
		: CoreObject(c_name, logger, WorkPriority::WP_SYSTEM, fw), m_Type(st)
	{
	}

	ISystem::~ISystem()
	{
	}

	const SystemsType ISystem::GetType()
	{
		return m_Type;
	}
}