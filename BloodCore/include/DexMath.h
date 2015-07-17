#pragma once

#include "DexPreCompletion.h"
#include <assert.h>

namespace Dex
{
	//==================================================
	//=====Math Const===================================
	//==================================================

	const _point MDEX_PI = 3.141592654f;
	const _point MDEX_2PI = 6.283185307f;
	const _point MDEX_1DIVPI = 0.318309886f;
	const _point MDEX_1DIV2PI = 0.159154943f;
	const _point MDEX_PIDIV2 = 1.570796327f;
	const _point MDEX_PIDIV4 = 0.785398163f;

	const _32un MDEX_SELECT_0 = 0x00000000;
	const _32un MDEX_SELECT_1 = 0xFFFFFFFF;

	//==================================================
	//=====Class Point 2================================
	//==================================================

	class D_EXPORT _2point
	{
	public:
		_2point(void);
		_2point(_32un in_1, _32un in_2);
		_2point(_point in_1, _point in_2);
		_2point(_point in);
		_2point(const _2point& in);
		_2point(const _3point& in);
		_2point(const _4point& in);

		inline static _2point zero(void)
		{
			return _2point();
		}

		inline static _2point one(void)
		{
			return _2point(1.0f, 1.0f);
		}

		inline static _2point identityR0(void)
		{
			return _2point(1.0f, 0.0f);
		}

		inline static _2point identityR1(void)
		{
			return _2point(0.0f, 1.0f);
		}

		inline static _2point negidentityR0(void)
		{
			return _2point(-1.0f, 0.0f);
		}

		inline static _2point negidentityR1(void)
		{
			return _2point(0.0f, -1.0f);
		}

		// create select 3 point class
		inline static _2point select11(void)
		{
			return _2point(MDEX_SELECT_1, MDEX_SELECT_1);
		}

		inline static _2point select10(void)
		{
			return _2point(MDEX_SELECT_1, MDEX_SELECT_0);
		}

		inline static _2point select01(void)
		{
			return _2point(MDEX_SELECT_0, MDEX_SELECT_1);
		}

		inline static _2point select00(void)
		{
			return _2point(MDEX_SELECT_0, MDEX_SELECT_0);
		}

		// operator -  C(result 2 point) = A(this 2 point) - B(input 4 point)
		_2point operator -
		(
			const _4point& in_4point_B // input B 4 point
		) 
			const;

		// operator -  C(result 2 point) = A(this 2 point) - B(input 3 point)
		_2point operator -
		(
			const _3point& in_3point_B // input B 3 point
		)
			const;

		// operator -  C(result 2 point) = A(this 2 point) - B(input 2 point)
		_2point operator -
		(
			const _2point& in_2point_B // input B 2 point
		)
			const;

		// operator -  C(result 2 point) = A(this 2 point) - B(input point)
		_2point operator -
		(
			const _point& in_point_B // input B point
		)
			const;

		// operator +  C(result 2 point) = A(this 2 point) + B(input 4 point)
		_2point operator +
		(
			const _4point& in_4point_B
		)
			const;

		// operator +  C(result 2 point) = A(this 2 point) + B(input 3 point)
		_2point operator +
		(
			const _3point& in_3point_B
		)
			const;

		// operator +  C(result 2 point) = A(this 2 point) + B(input 2 point)
		_2point operator +
		(
			const _2point& in_2point_B
		)
			const;

		// operator +  C(result 2 point) = A(this 2 point) + B(input point)
		_2point operator +
		(
			const _point& in_point_B
		)
			const;

		union
		{
			_point	d_p32[2];
			_32un	d_u32[2];
		};
	};

	//==================================================
	//=====Class Point 3================================
	//==================================================

	class D_EXPORT _3point
	{
	public:
		_3point(void);
		_3point(_32un in_1, _32un in_2, _32un in_3);
		_3point(_point in_1, _point in_2, _point in_3);
		_3point(_point in_1, _point in_2);
		_3point(_point in);
		_3point(const _2point& in);
		_3point(const _3point& in);
		_3point(const _4point& in);

		inline static _3point zero(void)
		{
			return _3point();
		}

		inline static _3point one(void)
		{
			return _3point(1.0f, 1.0f, 1.0f);
		}

		inline static _3point identityR0(void)
		{
			return _3point(1.0f, 0.0f, 0.0f);
		}

		inline static _3point identityR1(void)
		{
			return _3point(0.0f, 1.0f, 0.0f);
		}

		inline static _3point identityR2(void)
		{
			return _3point(0.0f, 0.0f, 1.0f);
		}

		inline static _3point negidentityR0(void)
		{
			return _3point(-1.0f, 0.0f, 0.0f);
		}

		inline static _3point negidentityR1(void)
		{
			return _3point(0.0f, -1.0f, 0.0f);
		}

		inline static _3point negidentityR2(void)
		{
			return _3point(0.0f, 0.0f, -1.0f);
		}

		// create select 3 point class
		inline static _3point select111(void)
		{
			return _3point(MDEX_SELECT_1, MDEX_SELECT_1, MDEX_SELECT_1);
		}

		inline static _3point select110(void)
		{
			return _3point(MDEX_SELECT_1, MDEX_SELECT_1, MDEX_SELECT_0);
		}

		inline static _3point select100(void)
		{
			return _3point(MDEX_SELECT_1, MDEX_SELECT_0, MDEX_SELECT_0);
		}

		inline static _3point select000(void)
		{
			return _3point(MDEX_SELECT_0, MDEX_SELECT_0, MDEX_SELECT_0);
		}

		// operator -  C(result 3 point) = A(this 3 point) - B(input 4 point)
		_3point operator -
		(
			const _4point& in_4point_B // input B 4 point
		) 
			const;

		// operator -  C(result 3 point) = A(this 3 point) - B(input 3 point)
		_3point operator -
		(
			const _3point& in_3point_B // input B 3 point
		)
			const;

		// operator -  C(result 3 point) = A(this 3 point) - B(input 2 point)
		_3point operator -
		(
			const _2point& in_2point_B // input B 2 point
		)
			const;

		// operator -  C(result 3 point) = A(this 3 point) - B(input point)
		_3point operator -
		(
			const _point& in_point_B // input B point
		)
			const;

		// operator +  C(result 3 point) = A(this 3 point) + B(input 4 point)
		_3point operator +
		(
			const _4point& in_4point_B
		)
			const;

		// operator +  C(result 3 point) = A(this 3 point) + B(input 3 point)
		_3point operator +
		(
			const _3point& in_3point_B
		)
			const;

		// operator +  C(result 3 point) = A(this 3 point) + B(input 2 point)
		_3point operator +
		(
			const _2point& in_2point_B
		)
			const;

		// operator +  C(result 3 point) = A(this 3 point) + B(input point)
		_3point operator +
		(
			const _point& in_point_B
		)
			const;

		union
		{
			_point	d_p32[3];
			_32un	d_u32[3];
		};
	};

	//==================================================
	//=====Class Point 4================================
	//==================================================

	class D_EXPORT _4point
	{
	public:
		_4point(void);
		_4point(_32un in_1, _32un in_2, _32un in_3, _32un in_4);
		_4point(_point in_1, _point in_2, _point in_3, _point in_4);
		_4point(_point in_1, _point in_2, _point in_3);
		_4point(_point in_1, _point in_2);
		_4point(_point in);
		_4point(const _2point& in);
		_4point(const _3point& in);
		_4point(const _4point& in);

		inline static _4point zero(void)
		{
			return _4point();
		}

		inline static _4point one(void)
		{
			return _4point(1.0f, 1.0f, 1.0f, 1.0f);
		}

		inline static _4point identityR0(void)
		{
			return _4point(1.0f, 0.0f, 0.0f, 0.0f);
		}

		inline static _4point identityR1(void)
		{
			return _4point(0.0f, 1.0f, 0.0f, 0.0f);
		}

		inline static _4point identityR2(void)
		{
			return _4point(0.0f, 0.0f, 1.0f, 0.0f);
		}

		inline static _4point identityR3(void)
		{
			return _4point(0.0f, 0.0f, 0.0f, 1.0f);
		}

		inline static _4point negidentityR0(void)
		{
			return _4point(-1.0f, 0.0f, 0.0f, 0.0f);
		}

		inline static _4point negidentityR1(void)
		{
			return _4point(0.0f, -1.0f, 0.0f, 0.0f);
		}

		inline static _4point negidentityR2(void)
		{
			return _4point(0.0f, 0.0f, -1.0f, 0.0f);
		}

		inline static _4point negidentityR3(void)
		{
			return _4point(0.0f, 0.0f, 0.0f, -1.0f);
		}

		// create select 4 point class
		inline static _4point select1111(void)
		{
			return _4point(MDEX_SELECT_1, MDEX_SELECT_1, MDEX_SELECT_1, MDEX_SELECT_1);
		}

		inline static _4point select1110(void)
		{
			return _4point(MDEX_SELECT_1, MDEX_SELECT_1, MDEX_SELECT_1, MDEX_SELECT_0);
		}

		inline static _4point select1100(void)
		{
			return _4point(MDEX_SELECT_1, MDEX_SELECT_1, MDEX_SELECT_0, MDEX_SELECT_0);
		}

		inline static _4point select1000(void)
		{
			return _4point(MDEX_SELECT_1, MDEX_SELECT_0, MDEX_SELECT_0, MDEX_SELECT_0);
		}

		inline static _4point select0000(void)
		{
			return _4point(MDEX_SELECT_0, MDEX_SELECT_0, MDEX_SELECT_0, MDEX_SELECT_0);
		}

		// operator -  C(result 4 point) = A(this 4 point) - B(input 4 point)
		_4point operator -
		(
			const _4point& in_4point_B // input B 4 point
		)
			const;

		// operator -  C(result 4 point) = A(this 4 point) - B(input 3 point)
		_4point operator -
		(
			const _3point& in_3point_B // input B 3 point
		)
			const;

		// operator -  C(result 4 point) = A(this 4 point) - B(input 2 point)
		_4point operator -
		(
			const _2point& in_2point_B // input B 2 point
		)
			const;

		// operator -  C(result 4 point) = A(this 4 point) - B(input point)
		_4point operator -
		(
			const _point& in_point_B // input B point
		)
			const;

		// operator +  C(result 4 point) = A(this 4 point) + B(input 4 point)
		_4point operator +
		(
			const _4point& in_4point_B
		)
			const;

		// operator +  C(result 4 point) = A(this 4 point) + B(input 3 point)
		_4point operator +
		(
			const _3point& in_3point_B
		)
			const;

		// operator +  C(result 4 point) = A(this 4 point) + B(input 2 point)
		_4point operator +
		(
			const _2point& in_2point_B
		)
			const;

		// operator +  C(result 4 point) = A(this 4 point) + B(input point)
		_4point operator +
		(
			const _point& in_point_B
		)
			const;

		union
		{
			_point	d_p32[4];
			_32un	d_u32[4];
		};
	};

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

		inline static _4matrix identity(void)
		{
			return _4matrix();
		}

		inline static _4matrix zero(void)
		{
			return _4matrix(
				0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f
			);
		}

		union
		{
			_4point d_4p32[4];
			_point	d_p32[4][4];
			_32un	d_u32[4][4];
		};
	};

	//==================================================
	//=====Math vector method===========================
	//==================================================

	inline D_EXPORT _4point Vector3Dot(const _4point& in_p1, const _4point& in_p2)
	{
		float fValue = in_p1.d_p32[0] * in_p2.d_p32[0] + in_p1.d_p32[1] * in_p2.d_p32[1] + in_p1.d_p32[2] * in_p2.d_p32[2];
		_4point vResult;
		vResult.d_p32[0] = fValue;
		vResult.d_p32[1] = fValue;
		vResult.d_p32[2] = fValue;
		vResult.d_p32[3] = fValue;

		return vResult;
	};

	inline D_EXPORT _4point Vector3LengthSq(const _4point& in_p)
	{
		return Vector3Dot(in_p, in_p);
	};

	inline D_EXPORT _4point VectorSqrt(const _4point& in_p)
	{
		_4point Result;
		Result.d_p32[0] = sqrtf(in_p.d_p32[0]);
		Result.d_p32[1] = sqrtf(in_p.d_p32[1]);
		Result.d_p32[2] = sqrtf(in_p.d_p32[2]);
		Result.d_p32[3] = sqrtf(in_p.d_p32[3]);
		return Result;
	};

	inline D_EXPORT _4point Vector3Length(const _4point& in_p)
	{
		_4point Result;

		Result = Vector3LengthSq(in_p);
		Result = VectorSqrt(Result);

		return Result;
	};

	inline D_EXPORT _4point Vector3Normalize(const _4point& in_p)
	{
		_point fLength;
		_4point vResult;

		vResult = Vector3Length(in_p);
		fLength = vResult.d_p32[0];

		if (fLength > 0) {
			fLength = 1.0f / fLength;
		}

		vResult.d_p32[0] = in_p.d_p32[0] * fLength;
		vResult.d_p32[1] = in_p.d_p32[1] * fLength;
		vResult.d_p32[2] = in_p.d_p32[2] * fLength;
		vResult.d_p32[3] = in_p.d_p32[3] * fLength;
		return vResult;
	};

	inline D_EXPORT _4point VectorMergeXY(const _4point& in_p1, const _4point& in_p2)
	{
		_4point Result;
		Result.d_p32[0] = in_p1.d_p32[0];
		Result.d_p32[1] = in_p2.d_p32[0];
		Result.d_p32[2] = in_p1.d_p32[1];
		Result.d_p32[3] = in_p2.d_p32[1];
		return Result;
	};

	inline D_EXPORT _4point VectorMergeZW(const _4point& in_p1, const _4point& in_p2)
	{
		_4point Result;
		Result.d_p32[0] = in_p1.d_p32[2];
		Result.d_p32[1] = in_p2.d_p32[2];
		Result.d_p32[2] = in_p1.d_p32[3];
		Result.d_p32[3] = in_p2.d_p32[3];
		return Result;
	};

	inline D_EXPORT _4point Vector3Cross(const _4point& in_p1, const _4point& in_p2)
	{
		_4point vResult = _4point(
			(in_p1.d_p32[1] * in_p2.d_p32[2]) - (in_p1.d_p32[2] * in_p2.d_p32[1]),
			(in_p1.d_p32[2] * in_p2.d_p32[0]) - (in_p1.d_p32[0] * in_p2.d_p32[2]),
			(in_p1.d_p32[0] * in_p2.d_p32[1]) - (in_p1.d_p32[1] * in_p2.d_p32[0]),
			0.0f
		);
		return vResult;
	};

	inline D_EXPORT _4point VectorNegate(const _4point& in_p)
	{
		_4point Result;
		Result.d_p32[0] = -in_p.d_p32[0];
		Result.d_p32[1] = -in_p.d_p32[1];
		Result.d_p32[2] = -in_p.d_p32[2];
		Result.d_p32[3] = -in_p.d_p32[3];
		return Result;
	};

	inline D_EXPORT _4point VectorSelect(const _4point& in_p1, const _4point& in_p2, const _4point& inControl)
	{
		_4point Result;
		Result.d_u32[0] = (in_p1.d_u32[0] & ~inControl.d_u32[0]) | (in_p2.d_u32[0] & inControl.d_u32[0]);
		Result.d_u32[1] = (in_p1.d_u32[1] & ~inControl.d_u32[1]) | (in_p2.d_u32[1] & inControl.d_u32[1]);
		Result.d_u32[2] = (in_p1.d_u32[2] & ~inControl.d_u32[2]) | (in_p2.d_u32[2] & inControl.d_u32[2]);
		Result.d_u32[3] = (in_p1.d_u32[3] & ~inControl.d_u32[3]) | (in_p2.d_u32[3] & inControl.d_u32[3]);
		return Result;
	};

	// C = A - B
	//inline D_EXPORT _2point VectorSubtract
	//(
	//	const _2point& in_2point_A, // in point 2 A
	//	const _2point& in_2point_B	// in point 2 B
	//)
	//{
	//	_2point Result;
	//	Result.d_p32[0] = in_2point_A.d_p32[0] - in_2point_B.d_p32[0];
	//	Result.d_p32[1] = in_2point_A.d_p32[1] - in_2point_B.d_p32[1];
	//	return Result;
	//};



	//inline D_EXPORT _4point VectorSubtract(const _4point& in_p1, const _4point& in_p2)
	//{
	//	_4point Result;
	//	Result.d_p32[0] = in_p1.d_p32[0] - in_p2.d_p32[0];
	//	Result.d_p32[1] = in_p1.d_p32[1] - in_p2.d_p32[1];
	//	Result.d_p32[2] = in_p1.d_p32[2] - in_p2.d_p32[2];
	//	Result.d_p32[3] = in_p1.d_p32[3] - in_p2.d_p32[3];
	//	return Result;
	//};

	inline D_EXPORT bool Vector3Equal(const _4point& in_p1, const _4point& in_p2)
	{
		return (((in_p1.d_p32[0] == in_p2.d_p32[0]) && (in_p1.d_p32[1] == in_p2.d_p32[1]) && (in_p1.d_p32[2] == in_p2.d_p32[2])) != 0);
	};

	#define XMISNAN(x)  ((*(_32un*)&(x) & 0x7F800000) == 0x7F800000 && (*(_32un*)&(x) & 0x7FFFFF) != 0)
	#define XMISINF(x)  ((*(_32un*)&(x) & 0x7FFFFFFF) == 0x7F800000)

	inline D_EXPORT bool Vector3IsInfinite(const _4point& in_p)
	{
		return (
			XMISINF(in_p.d_p32[0]) || XMISINF(in_p.d_p32[1]) || XMISINF(in_p.d_p32[2])
		);
	};

	inline D_EXPORT bool ScalarNearEqual
	(
		_point S1,
		_point S2,
		_point Epsilon
	)
	{
		float Delta = S1 - S2;
		return (fabsf(Delta) <= Epsilon);
	}

	inline D_EXPORT void ScalarSinCos
	(
		_point* pSin,
		_point* pCos,
		_point  Value
	)
	{
		assert(pSin);
		assert(pCos);

		// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
		float quotient = MDEX_1DIV2PI*Value;
		if (Value >= 0.0f)
		{
			quotient = (float)((int)(quotient + 0.5f));
		}
		else
		{
			quotient = (float)((int)(quotient - 0.5f));
		}
		float y = Value - MDEX_2PI*quotient;

		// Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
		float sign;
		if (y > MDEX_PIDIV2)
		{
			y = MDEX_PI - y;
			sign = -1.0f;
		}
		else if (y < -MDEX_PIDIV2)
		{
			y = -MDEX_PI - y;
			sign = -1.0f;
		}
		else
		{
			sign = +1.0f;
		}

		float y2 = y * y;

		// 11-degree minimax approximation
		*pSin = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;

		// 10-degree minimax approximation
		float p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
		*pCos = sign*p;
	}

	//==================================================
	//=====Math matrix method===========================
	//==================================================

	inline D_EXPORT _4matrix MatrixPerspectiveFovRH(const _point& FovAngleY, const _point& AspectHByW, const _point& NearZ, const _point& FarZ)
	{
		assert(!ScalarNearEqual(FovAngleY, 0.0f, 0.00001f * 2.0f));
		assert(!ScalarNearEqual(AspectHByW, 0.0f, 0.00001f));
		assert(!ScalarNearEqual(FarZ, NearZ, 0.00001f));

		_point SinFov;
		_point CosFov;
		ScalarSinCos(&SinFov, &CosFov, 0.5f * FovAngleY);

		_point Height = CosFov / SinFov;
		_point Width = Height / AspectHByW;
		_point fRange = FarZ / (NearZ - FarZ);

		_4matrix M;
		M.d_p32[0][0] = Width;
		M.d_p32[0][1] = 0.0f;
		M.d_p32[0][2] = 0.0f;
		M.d_p32[0][3] = 0.0f;

		M.d_p32[1][0] = 0.0f;
		M.d_p32[1][1] = Height;
		M.d_p32[1][2] = 0.0f;
		M.d_p32[1][3] = 0.0f;

		M.d_p32[2][0] = 0.0f;
		M.d_p32[2][1] = 0.0f;
		M.d_p32[2][2] = fRange;
		M.d_p32[2][3] = -1.0f;

		M.d_p32[3][0] = 0.0f;
		M.d_p32[3][1] = 0.0f;
		M.d_p32[3][2] = fRange * NearZ;
		M.d_p32[3][3] = 0.0f;
		return M;
	};

	inline D_EXPORT _4matrix MatrixTranspose(const _4matrix& in)
	{
		_4matrix P;
		P.d_4p32[0] = VectorMergeXY(in.d_4p32[0], in.d_4p32[2]);
		P.d_4p32[1] = VectorMergeXY(in.d_4p32[1], in.d_4p32[3]);
		P.d_4p32[2] = VectorMergeZW(in.d_4p32[0], in.d_4p32[2]);
		P.d_4p32[3] = VectorMergeZW(in.d_4p32[1], in.d_4p32[3]);

		_4matrix MT;
		MT.d_4p32[0] = VectorMergeXY(P.d_4p32[0], P.d_4p32[1]);
		MT.d_4p32[1] = VectorMergeZW(P.d_4p32[0], P.d_4p32[1]);
		MT.d_4p32[2] = VectorMergeXY(P.d_4p32[2], P.d_4p32[3]);
		MT.d_4p32[3] = VectorMergeZW(P.d_4p32[2], P.d_4p32[3]);

		return MT;
	};

	inline D_EXPORT _4matrix MatrixLookToLH(const _4point& eyePosition, const _4point& eyeDirection, const _4point& upDirection)
	{
		assert(!Vector3Equal(eyeDirection, _4point::zero()));
		assert(!Vector3IsInfinite(eyeDirection));
		assert(!Vector3Equal(upDirection, _4point::zero()));
		assert(!Vector3IsInfinite(upDirection));

		_4point R2 = Vector3Normalize(eyeDirection);

		_4point R0 = Vector3Cross(upDirection, R2);
		R0 = Vector3Normalize(R0);

		_4point R1 = Vector3Cross(R2, R0);

		_4point NegEyePosition = VectorNegate(eyePosition);

		_4point D0 = Vector3Dot(R0, NegEyePosition);
		_4point D1 = Vector3Dot(R1, NegEyePosition);
		_4point D2 = Vector3Dot(R2, NegEyePosition);

		_4matrix M;
		M.d_4p32[0] = VectorSelect(D0, R0, _4point::select1110());
		M.d_4p32[1] = VectorSelect(D1, R1, _4point::select1110());
		M.d_4p32[2] = VectorSelect(D2, R2, _4point::select1110());
		M.d_4p32[3] = _4point::identityR3();

		M = MatrixTranspose(M);

		return M;
	};

	inline D_EXPORT _4matrix MatrixLookAtRH(const _4point& eyePosition, const _4point& focusPosition, const _4point& upDirection)
	{
		_4point NegEyeDirection = eyePosition - focusPosition;
		return MatrixLookToLH(eyePosition, NegEyeDirection, upDirection);
	};
}