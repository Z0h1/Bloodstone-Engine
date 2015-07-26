#include "DexMatrix.h"

namespace Dex
{
	// matrix 4 class
	_4matrix::_4matrix
	(
		_point m00, _point m01, _point m02, _point m03,
		_point m10, _point m11, _point m12, _point m13,
		_point m20, _point m21, _point m22, _point m23,
		_point m30, _point m31, _point m32, _point m33
	)
	{
		data.d_p32[0][0] = m00;
		data.d_p32[0][1] = m01;
		data.d_p32[0][2] = m02;
		data.d_p32[0][3] = m03;

		data.d_p32[1][0] = m10;
		data.d_p32[1][1] = m11;
		data.d_p32[1][2] = m12;
		data.d_p32[1][3] = m13;

		data.d_p32[2][0] = m20;
		data.d_p32[2][1] = m21;
		data.d_p32[2][2] = m22;
		data.d_p32[2][3] = m23;

		data.d_p32[3][0] = m30;
		data.d_p32[3][1] = m31;
		data.d_p32[3][2] = m32;
		data.d_p32[3][3] = m33;
	}

	_4matrix::_4matrix(void)
	{
		data.d_p32[0][0] = 1;
		data.d_p32[0][1] = 0;
		data.d_p32[0][2] = 0;
		data.d_p32[0][3] = 0;

		data.d_p32[1][0] = 0;
		data.d_p32[1][1] = 1;
		data.d_p32[1][2] = 0;
		data.d_p32[1][3] = 0;

		data.d_p32[2][0] = 0;
		data.d_p32[2][1] = 0;
		data.d_p32[2][2] = 1;
		data.d_p32[2][3] = 0;

		data.d_p32[3][0] = 0;
		data.d_p32[3][1] = 0;
		data.d_p32[3][2] = 0;
		data.d_p32[3][3] = 1;
	}

	_4matrix _4matrix::operator*(const _4matrix M)
	{
		_4matrix result = _4matrix::zero();

		_point this_col_1 = data.d_p32[0][0];
		_point this_col_2 = data.d_p32[0][1];
		_point this_col_3 = data.d_p32[0][2];
		_point this_col_4 = data.d_p32[0][3];

		result.data.d_p32[0][0] =
			(M.data.d_p32[0][0] * this_col_1)
			+ (M.data.d_p32[1][0] * this_col_2)
			+ (M.data.d_p32[2][0] * this_col_3)
			+ (M.data.d_p32[3][0] * this_col_4);

		result.data.d_p32[0][1] =
			(M.data.d_p32[0][1] * this_col_1)
			+ (M.data.d_p32[1][1] * this_col_2)
			+ (M.data.d_p32[2][1] * this_col_3)
			+ (M.data.d_p32[3][1] * this_col_4);

		result.data.d_p32[0][2] =
			(M.data.d_p32[0][2] * this_col_1)
			+ (M.data.d_p32[1][2] * this_col_2)
			+ (M.data.d_p32[2][2] * this_col_3)
			+ (M.data.d_p32[3][2] * this_col_4);

		result.data.d_p32[0][3] =
			(M.data.d_p32[0][3] * this_col_1)
			+ (M.data.d_p32[1][3] * this_col_2)
			+ (M.data.d_p32[2][3] * this_col_3)
			+ (M.data.d_p32[3][3] * this_col_4);

		this_col_1 = data.d_p32[1][0];
		this_col_2 = data.d_p32[1][1];
		this_col_3 = data.d_p32[1][2];
		this_col_4 = data.d_p32[1][3];

		result.data.d_p32[1][0] =
			(M.data.d_p32[0][0] * this_col_1)
			+ (M.data.d_p32[1][0] * this_col_2)
			+ (M.data.d_p32[2][0] * this_col_3)
			+ (M.data.d_p32[3][0] * this_col_4);

		result.data.d_p32[1][1] =
			(M.data.d_p32[0][1] * this_col_1)
			+ (M.data.d_p32[1][1] * this_col_2)
			+ (M.data.d_p32[2][1] * this_col_3)
			+ (M.data.d_p32[3][1] * this_col_4);

		result.data.d_p32[1][2] =
			(M.data.d_p32[0][2] * this_col_1)
			+ (M.data.d_p32[1][2] * this_col_2)
			+ (M.data.d_p32[2][2] * this_col_3)
			+ (M.data.d_p32[3][2] * this_col_4);

		result.data.d_p32[1][3] =
			(M.data.d_p32[0][3] * this_col_1)
			+ (M.data.d_p32[1][3] * this_col_2)
			+ (M.data.d_p32[2][3] * this_col_3)
			+ (M.data.d_p32[3][3] * this_col_4);

		this_col_1 = data.d_p32[2][0];
		this_col_2 = data.d_p32[2][1];
		this_col_3 = data.d_p32[2][2];
		this_col_4 = data.d_p32[2][3];

		result.data.d_p32[2][0] =
			(M.data.d_p32[0][0] * this_col_1)
			+ (M.data.d_p32[1][0] * this_col_2)
			+ (M.data.d_p32[2][0] * this_col_3)
			+ (M.data.d_p32[3][0] * this_col_4);

		result.data.d_p32[2][1] =
			(M.data.d_p32[0][1] * this_col_1)
			+ (M.data.d_p32[1][1] * this_col_2)
			+ (M.data.d_p32[2][1] * this_col_3)
			+ (M.data.d_p32[3][1] * this_col_4);

		result.data.d_p32[2][2] =
			(M.data.d_p32[0][2] * this_col_1)
			+ (M.data.d_p32[1][2] * this_col_2)
			+ (M.data.d_p32[2][2] * this_col_3)
			+ (M.data.d_p32[3][2] * this_col_4);

		result.data.d_p32[2][3] =
			(M.data.d_p32[0][3] * this_col_1)
			+ (M.data.d_p32[1][3] * this_col_2)
			+ (M.data.d_p32[2][3] * this_col_3)
			+ (M.data.d_p32[3][3] * this_col_4);

		this_col_1 = data.d_p32[3][0];
		this_col_2 = data.d_p32[3][1];
		this_col_3 = data.d_p32[3][2];
		this_col_4 = data.d_p32[3][3];

		result.data.d_p32[3][0] =
			(M.data.d_p32[0][0] * this_col_1)
			+ (M.data.d_p32[1][0] * this_col_2)
			+ (M.data.d_p32[2][0] * this_col_3)
			+ (M.data.d_p32[3][0] * this_col_4);

		result.data.d_p32[3][1] =
			(M.data.d_p32[0][1] * this_col_1)
			+ (M.data.d_p32[1][1] * this_col_2)
			+ (M.data.d_p32[2][1] * this_col_3)
			+ (M.data.d_p32[3][1] * this_col_4);

		result.data.d_p32[3][2] =
			(M.data.d_p32[0][2] * this_col_1)
			+ (M.data.d_p32[1][2] * this_col_2)
			+ (M.data.d_p32[2][2] * this_col_3)
			+ (M.data.d_p32[3][2] * this_col_4);

		result.data.d_p32[3][3] =
			(M.data.d_p32[0][3] * this_col_1)
			+ (M.data.d_p32[1][3] * this_col_2)
			+ (M.data.d_p32[2][3] * this_col_3)
			+ (M.data.d_p32[3][3] * this_col_4);

		return result;
	}
}