#pragma once

#include "DexPreCompletion.h"
#include "DexMathConst.h"

namespace Dex
{
	class D_EXPORT _3DMatrix
	{
	public:
		_3DMatrix(
			_point m00, _point m01, _point m02, _point m03,
			_point m10, _point m11, _point m12, _point m13,
			_point m20, _point m21, _point m22, _point m23,
			_point m30, _point m31, _point m32, _point m33
		);
		_3DMatrix();
		~_3DMatrix();

		inline static _3DMatrix Identity()
		{
			return _3DMatrix();
		}

		inline static _3DMatrix zero(void)
		{
			return _3DMatrix(
				0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f
			);
		}

		_3DMatrix operator*(const _3DMatrix M);

		_4matrix_dat data;
	};
}