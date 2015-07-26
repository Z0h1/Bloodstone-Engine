#include "DexPoint.h"

namespace Dex
{
	// 2 point class

	_2point::_2point(void)
	{
		data.d_p32[0] = 0;
		data.d_p32[1] = 0;
	}

	_2point::_2point(_32un in_1, _32un in_2)
	{
		data.d_u32[0] = in_1;
		data.d_u32[1] = in_2;
	}

	_2point::_2point(_point in_1, _point in_2)
	{
		data.d_p32[0] = in_1;
		data.d_p32[1] = in_2;
	}

	_2point::_2point(_point in)
	{
		data.d_p32[0] = in;
		data.d_p32[1] = 0.0f;
	}

	_2point::_2point(const _2point& in)
	{
		data.d_p32[0] = in.data.d_p32[0];
		data.d_p32[1] = in.data.d_p32[1];
	}

	_2point::_2point(const _3point& in)
	{
		data.d_p32[0] = in.data.d_p32[0];
		data.d_p32[1] = in.data.d_p32[1];
	}

	_2point::_2point(const _4point& in)
	{
		data.d_p32[0] = in.data.d_p32[0];
		data.d_p32[1] = in.data.d_p32[1];
	}

	_2point _2point::operator -
	(
		const _4point& in_4point_B // input B 4 point
	)
		const
	{
		return _2point(
			data.d_p32[0] - in_4point_B.data.d_p32[0],
			data.d_p32[1] - in_4point_B.data.d_p32[1]
		);
	}

	_2point _2point::operator -
	(
		const _3point& in_3point_B // input B 3 point
	)
		const
	{
		return _2point(
			data.d_p32[0] - in_3point_B.data.d_p32[0],
			data.d_p32[1] - in_3point_B.data.d_p32[1]
		);
	}

	_2point _2point::operator -
	(
		const _2point& in_2point_B // input B 2 point
	)
		const
	{
		return _2point(
			data.d_p32[0] - in_2point_B.data.d_p32[0],
			data.d_p32[1] - in_2point_B.data.d_p32[1]
		);
	}

	_2point _2point::operator -
	(
		const _point& in_point_B // input B point
	)
		const
	{
		return _2point(
			data.d_p32[0] - in_point_B
		);
	}

	_2point _2point::operator +
	(
		const _4point& in_4point_B
	)
		const
	{
		return _2point(
			data.d_p32[0] + in_4point_B.data.d_p32[0],
			data.d_p32[1] + in_4point_B.data.d_p32[1]
		);
	}

	_2point _2point::operator +
	(
		const _3point& in_3point_B
	)
		const
	{
		return _2point(
			data.d_p32[0] + in_3point_B.data.d_p32[0],
			data.d_p32[1] + in_3point_B.data.d_p32[1]
		);
	}

	_2point _2point::operator +
	(
		const _2point& in_2point_B
	)
		const
	{
		return _2point(
			data.d_p32[0] + in_2point_B.data.d_p32[0],
			data.d_p32[1] + in_2point_B.data.d_p32[1]
		);
	}

	_2point _2point::operator +
	(
		const _point& in_point_B
	)
		const
	{
		return _2point(
			data.d_p32[0] + in_point_B
		);
	}

	// 3 point class
	_3point::_3point(void)
	{
		data.d_p32[0] = 0;
		data.d_p32[1] = 0;
		data.d_p32[2] = 0;
	}

	_3point::_3point(_32un in_1, _32un in_2, _32un in_3)
	{
		data.d_u32[0] = in_1;
		data.d_u32[1] = in_2;
		data.d_u32[2] = in_3;
	}

	_3point::_3point(_point in_1, _point in_2, _point in_3)
	{
		data.d_p32[0] = in_1;
		data.d_p32[1] = in_2;
		data.d_p32[2] = in_3;
	}

	_3point::_3point(_point in_1, _point in_2)
	{
		data.d_p32[0] = in_1;
		data.d_p32[1] = in_2;
		data.d_p32[2] = 0.0f;
	}

	_3point::_3point(_point in)
	{
		data.d_p32[0] = in;
		data.d_p32[1] = 0.0f;
		data.d_p32[2] = 0.0f;
	}

	_3point::_3point(const _2point& in)
	{
		data.d_p32[0] = in.data.d_p32[0];
		data.d_p32[1] = in.data.d_p32[1];
		data.d_p32[2] = 0.0f;
	}

	_3point::_3point(const _3point& in)
	{
		data.d_p32[0] = in.data.d_p32[0];
		data.d_p32[1] = in.data.d_p32[1];
		data.d_p32[2] = in.data.d_p32[2];
	}

	_3point::_3point(const _4point& in)
	{
		data.d_p32[0] = in.data.d_p32[0];
		data.d_p32[1] = in.data.d_p32[1];
		data.d_p32[2] = in.data.d_p32[2];
	}

	_3point _3point::operator -
	(
		const _4point& in_4point_B // input B 4 point
	)
		const
	{
		return _3point(
			data.d_p32[0] - in_4point_B.data.d_p32[0],
			data.d_p32[1] - in_4point_B.data.d_p32[1],
			data.d_p32[2] - in_4point_B.data.d_p32[2]
		);
	}

	_3point _3point::operator -
	(
		const _3point& in_3point_B // input B 3 point
	)
		const
	{
		return _3point(
			data.d_p32[0] - in_3point_B.data.d_p32[0],
			data.d_p32[1] - in_3point_B.data.d_p32[1],
			data.d_p32[2] - in_3point_B.data.d_p32[2]
		);
	}

	_3point _3point::operator -
	(
		const _2point& in_2point_B // input B 2 point
	)
		const
	{
		return _3point(
			data.d_p32[0] - in_2point_B.data.d_p32[0],
			data.d_p32[1] - in_2point_B.data.d_p32[1]
		);
	}

	_3point _3point::operator -
	(
		const _point& in_point_B // input B point
	)
		const
	{
		return _3point(
			data.d_p32[0] - in_point_B
		);
	}

	_3point _3point::operator +
	(
		const _4point& in_4point_B
	)
		const
	{
		return _3point(
			data.d_p32[0] + in_4point_B.data.d_p32[0],
			data.d_p32[1] + in_4point_B.data.d_p32[1],
			data.d_p32[2] + in_4point_B.data.d_p32[2]
		);
	}

	_3point _3point::operator +
	(
		const _3point& in_3point_B
	)
		const
	{
		return _3point(
			data.d_p32[0] + in_3point_B.data.d_p32[0],
			data.d_p32[1] + in_3point_B.data.d_p32[1],
			data.d_p32[2] + in_3point_B.data.d_p32[2]
		);
	}

	_3point _3point::operator +
	(
		const _2point& in_2point_B
	)
		const
	{
		return _3point(
			data.d_p32[0] + in_2point_B.data.d_p32[0],
			data.d_p32[1] + in_2point_B.data.d_p32[1]
		);
	}

	_3point _3point::operator +
	(
		const _point& in_point_B
	)
		const
	{
		return _3point(
			data.d_p32[0] + in_point_B
		);
	}

	// 4 point class
	_4point::_4point(void)
	{
		data.d_p32[0] = 0;
		data.d_p32[1] = 0;
		data.d_p32[2] = 0;
		data.d_p32[3] = 0;
	}

	_4point::_4point(_32un in_1, _32un in_2, _32un in_3, _32un in_4)
	{
		data.d_u32[0] = in_1;
		data.d_u32[1] = in_2;
		data.d_u32[2] = in_3;
		data.d_u32[3] = in_4;
	}

	_4point::_4point(_point in_1, _point in_2, _point in_3, _point in_4)
	{
		data.d_p32[0] = in_1;
		data.d_p32[1] = in_2;
		data.d_p32[2] = in_3;
		data.d_p32[3] = in_4;
	}

	_4point::_4point(_point in_1, _point in_2, _point in_3)
	{
		data.d_p32[0] = in_1;
		data.d_p32[1] = in_2;
		data.d_p32[2] = in_3;
		data.d_p32[3] = 0.0f;
	}

	_4point::_4point(_point in_1, _point in_2)
	{
		data.d_p32[0] = in_1;
		data.d_p32[1] = in_2;
		data.d_p32[2] = 0.0f;
		data.d_p32[3] = 0.0f;
	}

	_4point::_4point(_point in)
	{
		data.d_p32[0] = in;
		data.d_p32[1] = 0.0f;
		data.d_p32[2] = 0.0f;
		data.d_p32[3] = 0.0f;
	}

	_4point::_4point(const _2point& in)
	{
		data.d_p32[0] = in.data.d_p32[0];
		data.d_p32[1] = in.data.d_p32[1];
		data.d_p32[2] = 0.0f;
		data.d_p32[3] = 0.0f;
	}

	_4point::_4point(const _3point& in)
	{
		data.d_p32[0] = in.data.d_p32[0];
		data.d_p32[1] = in.data.d_p32[1];
		data.d_p32[2] = in.data.d_p32[2];
		data.d_p32[3] = 0.0f;
	}

	_4point::_4point(const _4point& in)
	{
		data.d_p32[0] = in.data.d_p32[0];
		data.d_p32[1] = in.data.d_p32[1];
		data.d_p32[2] = in.data.d_p32[2];
		data.d_p32[3] = in.data.d_p32[3];
	}

	// operator -  C(result 4 point) = A(this 4 point) - B(input 4 point)
	_4point _4point::operator -
	(
		const _4point& in_4point_B // input B 4 point
	)
		const
	{
		return _4point(
			data.d_p32[0] - in_4point_B.data.d_p32[0],
			data.d_p32[1] - in_4point_B.data.d_p32[1],
			data.d_p32[2] - in_4point_B.data.d_p32[2],
			data.d_p32[3] - in_4point_B.data.d_p32[3]
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
			data.d_p32[0] - in_3point_B.data.d_p32[0],
			data.d_p32[1] - in_3point_B.data.d_p32[1],
			data.d_p32[2] - in_3point_B.data.d_p32[2]
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
			data.d_p32[0] - in_2point_B.data.d_p32[0],
			data.d_p32[1] - in_2point_B.data.d_p32[1]
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
			data.d_p32[0] - in_point_B
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
			data.d_p32[0] + in_4point_B.data.d_p32[0],
			data.d_p32[1] + in_4point_B.data.d_p32[1],
			data.d_p32[2] + in_4point_B.data.d_p32[2],
			data.d_p32[3] + in_4point_B.data.d_p32[3]
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
			data.d_p32[0] + in_3point_B.data.d_p32[0],
			data.d_p32[1] + in_3point_B.data.d_p32[1],
			data.d_p32[2] + in_3point_B.data.d_p32[2]
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
			data.d_p32[0] + in_2point_B.data.d_p32[0],
			data.d_p32[1] + in_2point_B.data.d_p32[1]
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
			data.d_p32[0] + in_point_B
		);
	}
}