#pragma once

#include "DexPreCompletion.h"
#include "DexMathConst.h"

namespace DEX
{
	class D_EXPORT _3DVector
	{
	public:
		_3DVector(_point in_1, _point in_2, _point in_3);
		_3DVector(_point in_1, _point in_2, _point in_3, _point in_4);
		_3DVector();
		~_3DVector();

		_4point_dat data;
	};
}