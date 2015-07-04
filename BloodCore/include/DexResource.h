#pragma once

#include <DexPreCompletion.h>

namespace Dex
{
	class D_EXPORT IResource
	{
	public:
		virtual void Load( const String& resource ) = 0;
	};
}