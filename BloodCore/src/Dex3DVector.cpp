#include "Dex3DVector.h"

namespace Dex
{
	_3DVector::_3DVector(_point in_1, _point in_2, _point in_3)
	{
		data.d_p32[0] = in_1;
		data.d_p32[1] = in_2;
		data.d_p32[2] = in_3;
		data.d_p32[3] = 0.0f;
	}

	_3DVector::_3DVector(_point in_1, _point in_2, _point in_3, _point in_4)
	{
		data.d_p32[0] = in_1;
		data.d_p32[1] = in_2;
		data.d_p32[2] = in_3;
		data.d_p32[3] = in_4;
	}

	_3DVector::_3DVector()
	{
		data.d_p32[0] = 0.0f;
		data.d_p32[1] = 0.0f;
		data.d_p32[2] = 0.0f;
		data.d_p32[3] = 0.0f;
	}

	_3DVector::~_3DVector()
	{

	}
}