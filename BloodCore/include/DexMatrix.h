#pragma once

#include "DexPreCompletion.h"
#include "DexMathConst.h"

namespace Dex
{
	//==================================================
	//=====Class Matrix 4x4=============================
	//==================================================

	class D_EXPORT _4matrix
	{
	public:
		_4matrix
		(
			_point m00, _point m01, _point m02, _point m03,
			_point m10, _point m11, _point m12, _point m13,
			_point m20, _point m21, _point m22, _point m23,
			_point m30, _point m31, _point m32, _point m33
		);
		_4matrix(void);

		inline ~_4matrix(void)
		{
		}

		static inline _4matrix identity(void)
		{
			return _4matrix();
		}

		static inline _4matrix zero(void)
		{
			return _4matrix(
				0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f
			);
		}

		_4matrix operator*(const _4matrix M);

		_4matrix_dat data;
	};
}