#include "DexMathFunction.h"
#include "Dex3DVector.h"

namespace DEX
{
	_3DVector Normalize(const _3DVector _in)
	{
		_3DVector result;

		_point length = _in.data.d_p32[0]
			+ _in.data.d_p32[1] + _in.data.d_p32[2] + _in.data.d_p32[3];

		result.data.d_p32[0] = _in.data.d_p32[0] / length;
		result.data.d_p32[1] = _in.data.d_p32[1] / length;
		result.data.d_p32[2] = _in.data.d_p32[2] / length;
		result.data.d_p32[3] = _in.data.d_p32[3] / length;

		return result;
	}
}