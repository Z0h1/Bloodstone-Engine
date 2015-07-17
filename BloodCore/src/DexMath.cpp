#include "DexMath.h"

namespace Dex
{
	// 2 point class

	_2point::_2point(void)
	{
		d_p32[0] = 0;
		d_p32[1] = 0;
	}

	_2point::_2point(_32un in_1, _32un in_2)
	{
		d_u32[0] = in_1;
		d_u32[1] = in_2;
	}

	_2point::_2point(_point in_1, _point in_2)
	{
		d_p32[0] = in_1;
		d_p32[1] = in_2;
	}

	_2point::_2point(_point in)
	{
		d_p32[0] = in;
		d_p32[1] = 0.0f;
	}

	_2point::_2point(const _2point& in)
	{
		d_p32[0] = in.d_p32[0];
		d_p32[1] = in.d_p32[1];
	}

	_2point::_2point(const _3point& in)
	{
		d_p32[0] = in.d_p32[0];
		d_p32[1] = in.d_p32[1];
	}

	_2point::_2point(const _4point& in)
	{
		d_p32[0] = in.d_p32[0];
		d_p32[1] = in.d_p32[1];
	}

	_2point _2point::operator -
	(
		const _4point& in_4point_B // input B 4 point
	)
		const
	{
		return _2point(
			d_p32[0] - in_4point_B.d_p32[0],
			d_p32[1] - in_4point_B.d_p32[1]
		);
	}

	_2point _2point::operator -
	(
		const _3point& in_3point_B // input B 3 point
	)
		const
	{
		return _2point(
			d_p32[0] - in_3point_B.d_p32[0],
			d_p32[1] - in_3point_B.d_p32[1]
		);
	}

	_2point _2point::operator -
	(
		const _2point& in_2point_B // input B 2 point
	)
		const
	{
		return _2point(
			d_p32[0] - in_2point_B.d_p32[0],
			d_p32[1] - in_2point_B.d_p32[1]
		);
	}

	_2point _2point::operator -
	(
		const _point& in_point_B // input B point
	)
		const
	{
		return _2point(
			d_p32[0] - in_point_B
		);
	}

	_2point _2point::operator +
	(
		const _4point& in_4point_B
	)
		const
	{
		return _2point(
			d_p32[0] + in_4point_B.d_p32[0],
			d_p32[1] + in_4point_B.d_p32[1]
		);
	}

	_2point _2point::operator +
	(
		const _3point& in_3point_B
	)
		const
	{
		return _2point(
			d_p32[0] + in_3point_B.d_p32[0],
			d_p32[1] + in_3point_B.d_p32[1]
		);
	}

	_2point _2point::operator +
	(
		const _2point& in_2point_B
	)
		const
	{
		return _2point(
			d_p32[0] + in_2point_B.d_p32[0],
			d_p32[1] + in_2point_B.d_p32[1]
		);
	}

	_2point _2point::operator +
	(
		const _point& in_point_B
	)
		const
	{
		return _2point(
			d_p32[0] + in_point_B
		);
	}

	// 3 point class
	_3point::_3point(void)
	{
		d_p32[0] = 0;
		d_p32[1] = 0;
		d_p32[2] = 0;
	}

	_3point::_3point(_32un in_1, _32un in_2, _32un in_3)
	{
		d_u32[0] = in_1;
		d_u32[1] = in_2;
		d_u32[2] = in_3;
	}

	_3point::_3point(_point in_1, _point in_2, _point in_3)
	{
		d_p32[0] = in_1;
		d_p32[1] = in_2;
		d_p32[2] = in_3;
	}

	_3point::_3point(_point in_1, _point in_2)
	{
		d_p32[0] = in_1;
		d_p32[1] = in_2;
		d_p32[2] = 0.0f;
	}

	_3point::_3point(_point in)
	{
		d_p32[0] = in;
		d_p32[1] = 0.0f;
		d_p32[2] = 0.0f;
	}

	_3point::_3point(const _2point& in)
	{
		d_p32[0] = in.d_p32[0];
		d_p32[1] = in.d_p32[1];
		d_p32[2] = 0.0f;
	}

	_3point::_3point(const _3point& in)
	{
		d_p32[0] = in.d_p32[0];
		d_p32[1] = in.d_p32[1];
		d_p32[2] = in.d_p32[2];
	}

	_3point::_3point(const _4point& in)
	{
		d_p32[0] = in.d_p32[0];
		d_p32[1] = in.d_p32[1];
		d_p32[2] = in.d_p32[2];
	}

	_3point _3point::operator -
	(
		const _4point& in_4point_B // input B 4 point
	)
		const
	{
		return _3point(
			d_p32[0] - in_4point_B.d_p32[0],
			d_p32[1] - in_4point_B.d_p32[1],
			d_p32[2] - in_4point_B.d_p32[2]
		);
	}

	_3point _3point::operator -
	(
		const _3point& in_3point_B // input B 3 point
	)
		const
	{
		return _3point(
			d_p32[0] - in_3point_B.d_p32[0],
			d_p32[1] - in_3point_B.d_p32[1],
			d_p32[2] - in_3point_B.d_p32[2]
		);
	}

	_3point _3point::operator -
	(
		const _2point& in_2point_B // input B 2 point
	)
		const
	{
		return _3point(
			d_p32[0] - in_2point_B.d_p32[0],
			d_p32[1] - in_2point_B.d_p32[1]
		);
	}

	_3point _3point::operator -
	(
		const _point& in_point_B // input B point
	)
		const
	{
		return _3point(
			d_p32[0] - in_point_B
		);
	}

	_3point _3point::operator +
	(
		const _4point& in_4point_B
	)
		const
	{
		return _3point(
			d_p32[0] + in_4point_B.d_p32[0],
			d_p32[1] + in_4point_B.d_p32[1],
			d_p32[2] + in_4point_B.d_p32[2]
		);
	}

	_3point _3point::operator +
	(
		const _3point& in_3point_B
	)
		const
	{
		return _3point(
			d_p32[0] + in_3point_B.d_p32[0],
			d_p32[1] + in_3point_B.d_p32[1],
			d_p32[2] + in_3point_B.d_p32[2]
		);
	}

	_3point _3point::operator +
	(
		const _2point& in_2point_B
	)
		const
	{
		return _3point(
			d_p32[0] + in_2point_B.d_p32[0],
			d_p32[1] + in_2point_B.d_p32[1]
		);
	}

	_3point _3point::operator +
	(
		const _point& in_point_B
	)
		const
	{
		return _3point(
			d_p32[0] + in_point_B
		);
	}

	// 4 point class
	_4point::_4point(void)
	{
		d_p32[0] = 0;
		d_p32[1] = 0;
		d_p32[2] = 0;
		d_p32[3] = 0;
	}

	_4point::_4point(_32un in_1, _32un in_2, _32un in_3, _32un in_4)
	{
		d_u32[0] = in_1;
		d_u32[1] = in_2;
		d_u32[2] = in_3;
		d_u32[3] = in_4;
	}

	_4point::_4point(_point in_1, _point in_2, _point in_3, _point in_4)
	{
		d_p32[0] = in_1;
		d_p32[1] = in_2;
		d_p32[2] = in_3;
		d_p32[3] = in_4;
	}

	_4point::_4point(_point in_1, _point in_2, _point in_3)
	{
		d_p32[0] = in_1;
		d_p32[1] = in_2;
		d_p32[2] = in_3;
		d_p32[3] = 0.0f;
	}

	_4point::_4point(_point in_1, _point in_2)
	{
		d_p32[0] = in_1;
		d_p32[1] = in_2;
		d_p32[2] = 0.0f;
		d_p32[3] = 0.0f;
	}

	_4point::_4point(_point in)
	{
		d_p32[0] = in;
		d_p32[1] = 0.0f;
		d_p32[2] = 0.0f;
		d_p32[3] = 0.0f;
	}

	_4point::_4point(const _2point& in)
	{
		d_p32[0] = in.d_p32[0];
		d_p32[1] = in.d_p32[1];
		d_p32[2] = 0.0f;
		d_p32[3] = 0.0f;
	}

	_4point::_4point(const _3point& in)
	{
		d_p32[0] = in.d_p32[0];
		d_p32[1] = in.d_p32[1];
		d_p32[2] = in.d_p32[2];
		d_p32[3] = 0.0f;
	}

	_4point::_4point(const _4point& in)
	{
		d_p32[0] = in.d_p32[0];
		d_p32[1] = in.d_p32[1];
		d_p32[2] = in.d_p32[2];
		d_p32[3] = in.d_p32[3];
	}

	// operator -  C(result 4 point) = A(this 4 point) - B(input 4 point)
	_4point _4point::operator -
	(
		const _4point& in_4point_B // input B 4 point
	)
		const
	{
		return _4point(
			d_p32[0] - in_4point_B.d_p32[0],
			d_p32[1] - in_4point_B.d_p32[1],
			d_p32[2] - in_4point_B.d_p32[2],
			d_p32[3] - in_4point_B.d_p32[3]
		);
	}

	// operator -  C(result 4 point) = A(this 4 point) - B(input 3 point)
	_4point _4point::operator -
	(
		const _3point& in_3point_B // input B 3 point
	)
		const
	{
		return _4point(
			d_p32[0] - in_3point_B.d_p32[0],
			d_p32[1] - in_3point_B.d_p32[1],
			d_p32[2] - in_3point_B.d_p32[2]
		);
	}

	// operator -  C(result 4 point) = A(this 4 point) - B(input 2 point)
	_4point _4point::operator -
	(
		const _2point& in_2point_B // input B 2 point
	)
		const
	{
		return _4point(
			d_p32[0] - in_2point_B.d_p32[0],
			d_p32[1] - in_2point_B.d_p32[1]
		);
	}

	// operator -  C(result 4 point) = A(this 4 point) - B(input point)
	_4point _4point::operator -
	(
		const _point& in_point_B // input B point
	)
		const
	{
		return _4point(
			d_p32[0] - in_point_B
		);
	}

	// operator +  C(result 4 point) = A(this 4 point) + B(input 4 point)
	_4point _4point::operator +
	(
		const _4point& in_4point_B
	)
		const
	{
		return _4point(
			d_p32[0] + in_4point_B.d_p32[0],
			d_p32[1] + in_4point_B.d_p32[1],
			d_p32[2] + in_4point_B.d_p32[2],
			d_p32[3] + in_4point_B.d_p32[3]
		);
	}

	// operator +  C(result 4 point) = A(this 4 point) + B(input 3 point)
	_4point _4point::operator +
	(
		const _3point& in_3point_B
	)
		const
	{
		return _4point(
			d_p32[0] + in_3point_B.d_p32[0],
			d_p32[1] + in_3point_B.d_p32[1],
			d_p32[2] + in_3point_B.d_p32[2]
		);
	}

	// operator +  C(result 4 point) = A(this 4 point) + B(input 2 point)
	_4point _4point::operator +
	(
		const _2point& in_2point_B
	)
		const
	{
		return _4point(
			d_p32[0] + in_2point_B.d_p32[0],
			d_p32[1] + in_2point_B.d_p32[1]
		);
	}

	// operator +  C(result 4 point) = A(this 4 point) + B(input point)
	_4point _4point::operator +
	(
		const _point& in_point_B
	)
		const
	{
		return _4point(
			d_p32[0] + in_point_B
		);
	}

	// matrix 4 class
	_4matrix::_4matrix
	(
		_point m00, _point m01, _point m02, _point m03,
		_point m10, _point m11, _point m12, _point m13,
		_point m20, _point m21, _point m22, _point m23,
		_point m30, _point m31, _point m32, _point m33
	)
	{
		d_p32[0][0] = m00;
		d_p32[0][1] = m01;
		d_p32[0][2] = m02;
		d_p32[0][3] = m03;

		d_p32[1][0] = m10;
		d_p32[1][1] = m11;
		d_p32[1][2] = m12;
		d_p32[1][3] = m13;

		d_p32[2][0] = m20;
		d_p32[2][1] = m21;
		d_p32[2][2] = m22;
		d_p32[2][3] = m23;

		d_p32[3][0] = m30;
		d_p32[3][1] = m31;
		d_p32[3][2] = m32;
		d_p32[3][3] = m33;
	}

	_4matrix::_4matrix(void)
	{
		d_p32[0][0] = 1;
		d_p32[0][1] = 0;
		d_p32[0][2] = 0;
		d_p32[0][3] = 0;

		d_p32[1][0] = 0;
		d_p32[1][1] = 1;
		d_p32[1][2] = 0;
		d_p32[1][3] = 0;

		d_p32[2][0] = 0;
		d_p32[2][1] = 0;
		d_p32[2][2] = 1;
		d_p32[2][3] = 0;

		d_p32[3][0] = 0;
		d_p32[3][1] = 0;
		d_p32[3][2] = 0;
		d_p32[3][3] = 1;
	}
}