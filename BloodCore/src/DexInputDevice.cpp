#include <DexInputDevice.h>

namespace Dex
{
	IInputDevice::~IInputDevice( void )
	{
	}

	const String& IInputDevice::GetName( void )
	{
		return m_cName;
	}
}