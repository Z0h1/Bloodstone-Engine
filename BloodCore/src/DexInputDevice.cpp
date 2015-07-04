#include "DexInputDevice.h"

namespace Dex
{
	IInputDevice::~IInputDevice( void )
	{
	}

	const string& IInputDevice::GetName( void )
	{
		return m_cName;
	}
}