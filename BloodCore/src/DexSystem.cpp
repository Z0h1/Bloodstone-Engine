#include "DexSystem.h"

namespace Dex
{
	ISystem::ISystem(const String& c_name, const SystemsType st, bool fw)
		: CoreObject(c_name, WorkPriority::WP_SYSTEM, fw), m_Type(st)
	{
		SetOutFileStream(new OFStream(c_name + ".log"));
	}

	ISystem::~ISystem()
	{
	}

	const SystemsType ISystem::GetType()
	{
		return m_Type;
	}
}