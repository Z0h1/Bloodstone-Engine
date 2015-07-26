//#pragma once
//
//#include "DexPreCompletion.h"
//#include "DexMathConst.h
//#include "DexMatrix.h"
//#include "DexPoint.h"
//
//namespace Dex
//{
//	//==================================================
//	//=====Math vector method===========================
//	//==================================================
//
//	inline D_EXPORT _4point Vector3Dot(const _4point& in_p1, const _4point& in_p2)
//	{
//		float fValue = in_p1.data.d_p32[0] * in_p2.data.d_p32[0] + in_p1.data.d_p32[1] * in_p2.data.d_p32[1] + in_p1.data.d_p32[2] * in_p2.data.d_p32[2];
//		_4point vResult;
//		vResult.data.d_p32[0] = fValue;
//		vResult.data.d_p32[1] = fValue;
//		vResult.data.d_p32[2] = fValue;
//		vResult.data.d_p32[3] = fValue;
//
//		return vResult;
//	};
//
//	inline D_EXPORT _4point Vector3LengthSq(const _4point& in_p)
//	{
//		return Vector3Dot(in_p, in_p);
//	};
//
//	inline D_EXPORT _4point VectorSqrt(const _4point& in_p)
//	{
//		_4point Result;
//		Result.data.d_p32[0] = sqrtf(in_p.data.d_p32[0]);
//		Result.data.d_p32[1] = sqrtf(in_p.data.d_p32[1]);
//		Result.data.d_p32[2] = sqrtf(in_p.data.d_p32[2]);
//		Result.data.d_p32[3] = sqrtf(in_p.data.d_p32[3]);
//		return Result;
//	};
//
//	inline D_EXPORT _4point Vector3Length(const _4point& in_p)
//	{
//		_4point Result;
//
//		Result = Vector3LengthSq(in_p);
//		Result = VectorSqrt(Result);
//
//		return Result;
//	};
//
//	inline D_EXPORT _4point Vector3Normalize(const _4point& in_p)
//	{
//		_point fLength;
//		_4point vResult;
//
//		vResult = Vector3Length(in_p);
//		fLength = vResult.data.d_p32[0];
//
//		if (fLength > 0) {
//			fLength = 1.0f / fLength;
//		}
//
//		vResult.data.d_p32[0] = in_p.data.d_p32[0] * fLength;
//		vResult.data.d_p32[1] = in_p.data.d_p32[1] * fLength;
//		vResult.data.d_p32[2] = in_p.data.d_p32[2] * fLength;
//		vResult.data.d_p32[3] = in_p.data.d_p32[3] * fLength;
//		return vResult;
//	};
//
//	inline D_EXPORT _4point_dat VectorMergeXY(const _4point_dat& in_p1, const _4point_dat& in_p2)
//	{
//		_4point_dat result;
//		result.d_p32[0] = in_p1.d_p32[0];
//		result.d_p32[1] = in_p1.d_p32[0];
//		result.d_p32[2] = in_p1.d_p32[1];
//		result.d_p32[3] = in_p1.d_p32[1];
//		return result;
//	};
//
//	inline D_EXPORT _4point_dat VectorMergeZW(const _4point_dat& in_p1, const _4point_dat& in_p2)
//	{
//		_4point_dat result;
//		result.d_p32[0] = in_p1.d_p32[2];
//		result.d_p32[1] = in_p1.d_p32[2];
//		result.d_p32[2] = in_p1.d_p32[3];
//		result.d_p32[3] = in_p1.d_p32[3];
//		return result;
//	};
//
//	inline D_EXPORT _4point Vector3Cross(const _4point& in_p1, const _4point& in_p2)
//	{
//		_4point vResult = _4point(
//			(in_p1.data.d_p32[1] * in_p2.data.d_p32[2]) - (in_p1.data.d_p32[2] * in_p2.data.d_p32[1]),
//			(in_p1.data.d_p32[2] * in_p2.data.d_p32[0]) - (in_p1.data.d_p32[0] * in_p2.data.d_p32[2]),
//			(in_p1.data.d_p32[0] * in_p2.data.d_p32[1]) - (in_p1.data.d_p32[1] * in_p2.data.d_p32[0]),
//			0.0f
//			);
//		return vResult;
//	};
//
//	inline D_EXPORT _4point VectorNegate(const _4point& in_p)
//	{
//		_4point Result;
//		Result.data.d_p32[0] = -in_p.data.d_p32[0];
//		Result.data.d_p32[1] = -in_p.data.d_p32[1];
//		Result.data.d_p32[2] = -in_p.data.d_p32[2];
//		Result.data.d_p32[3] = -in_p.data.d_p32[3];
//		return Result;
//	};
//
//	inline D_EXPORT _4point_dat VectorSelect(const _4point& in_p1, const _4point& in_p2, const _4point& inControl)
//	{
//		_4point_dat Result;
//		Result.d_u32[0] = (in_p1.data.d_u32[0] & ~inControl.data.d_u32[0]) | (in_p2.data.d_u32[0] & inControl.data.d_u32[0]);
//		Result.d_u32[1] = (in_p1.data.d_u32[1] & ~inControl.data.d_u32[1]) | (in_p2.data.d_u32[1] & inControl.data.d_u32[1]);
//		Result.d_u32[2] = (in_p1.data.d_u32[2] & ~inControl.data.d_u32[2]) | (in_p2.data.d_u32[2] & inControl.data.d_u32[2]);
//		Result.d_u32[3] = (in_p1.data.d_u32[3] & ~inControl.data.d_u32[3]) | (in_p2.data.d_u32[3] & inControl.data.d_u32[3]);
//		return Result;
//	};
//
//	// C = A - B
//	//inline D_EXPORT _2point VectorSubtract
//	//(
//	//	const _2point& in_2point_A, // in point 2 A
//	//	const _2point& in_2point_B	// in point 2 B
//	//)
//	//{
//	//	_2point Result;
//	//	Result.data.d_p32[0] = in_2point_A.data.d_p32[0] - in_2point_B.data.d_p32[0];
//	//	Result.data.d_p32[1] = in_2point_A.data.d_p32[1] - in_2point_B.data.d_p32[1];
//	//	return Result;
//	//};
//
//
//
//	//inline D_EXPORT _4point VectorSubtract(const _4point& in_p1, const _4point& in_p2)
//	//{
//	//	_4point Result;
//	//	Result.data.d_p32[0] = in_p1.data.d_p32[0] - in_p2.data.d_p32[0];
//	//	Result.data.d_p32[1] = in_p1.data.d_p32[1] - in_p2.data.d_p32[1];
//	//	Result.data.d_p32[2] = in_p1.data.d_p32[2] - in_p2.data.d_p32[2];
//	//	Result.data.d_p32[3] = in_p1.data.d_p32[3] - in_p2.data.d_p32[3];
//	//	return Result;
//	//};
//
//	inline D_EXPORT bool Vector3Equal(const _4point& in_p1, const _4point& in_p2)
//	{
//		return (((in_p1.data.d_p32[0] == in_p2.data.d_p32[0]) && (in_p1.data.d_p32[1] == in_p2.data.d_p32[1]) && (in_p1.data.d_p32[2] == in_p2.data.d_p32[2])) != 0);
//	};
//
//#define XMISNAN(x)  ((*(_32un*)&(x) & 0x7F800000) == 0x7F800000 && (*(_32un*)&(x) & 0x7FFFFF) != 0)
//#define XMISINF(x)  ((*(_32un*)&(x) & 0x7FFFFFFF) == 0x7F800000)
//
//	inline D_EXPORT bool Vector3IsInfinite(const _4point& in_p)
//	{
//		return (
//			XMISINF(in_p.data.d_p32[0]) || XMISINF(in_p.data.d_p32[1]) || XMISINF(in_p.data.d_p32[2])
//			);
//	};
//
//	inline D_EXPORT bool ScalarNearEqual
//		(
//			_point S1,
//			_point S2,
//			_point Epsilon
//			)
//	{
//		float Delta = S1 - S2;
//		return (fabsf(Delta) <= Epsilon);
//	}
//
//	inline D_EXPORT void ScalarSinCos
//		(
//			_point* pSin,
//			_point* pCos,
//			_point  Value
//			)
//	{
//		assert(pSin);
//		assert(pCos);
//
//		// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
//		float quotient = MDEX_1DIV2PI*Value;
//		if (Value >= 0.0f)
//		{
//			quotient = (float)((int)(quotient + 0.5f));
//		}
//		else
//		{
//			quotient = (float)((int)(quotient - 0.5f));
//		}
//		float y = Value - MDEX_2PI*quotient;
//
//		// Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
//		float sign;
//		if (y > MDEX_PIDIV2)
//		{
//			y = MDEX_PI - y;
//			sign = -1.0f;
//		}
//		else if (y < -MDEX_PIDIV2)
//		{
//			y = -MDEX_PI - y;
//			sign = -1.0f;
//		}
//		else
//		{
//			sign = +1.0f;
//		}
//
//		float y2 = y * y;
//
//		// 11-degree minimax approximation
//		*pSin = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;
//
//		// 10-degree minimax approximation
//		float p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
//		*pCos = sign*p;
//	}
//
//	//==================================================
//	//=====Math matrix method===========================
//	//==================================================
//
//	inline D_EXPORT _4matrix MatrixPerspectiveFovRH(const _point& FovAngleY, const _point& AspectHByW, const _point& NearZ, const _point& FarZ)
//	{
//		assert(!ScalarNearEqual(FovAngleY, 0.0f, 0.00001f * 2.0f));
//		assert(!ScalarNearEqual(AspectHByW, 0.0f, 0.00001f));
//		assert(!ScalarNearEqual(FarZ, NearZ, 0.00001f));
//
//		_point SinFov;
//		_point CosFov;
//		ScalarSinCos(&SinFov, &CosFov, 0.5f * FovAngleY);
//
//		_point Height = CosFov / SinFov;
//		_point Width = Height / AspectHByW;
//		_point fRange = FarZ / (NearZ - FarZ);
//
//		_4matrix M;
//		M.data.d_p32[0][0] = Width;
//		M.data.d_p32[0][1] = 0.0f;
//		M.data.d_p32[0][2] = 0.0f;
//		M.data.d_p32[0][3] = 0.0f;
//
//		M.data.d_p32[1][0] = 0.0f;
//		M.data.d_p32[1][1] = Height;
//		M.data.d_p32[1][2] = 0.0f;
//		M.data.d_p32[1][3] = 0.0f;
//
//		M.data.d_p32[2][0] = 0.0f;
//		M.data.d_p32[2][1] = 0.0f;
//		M.data.d_p32[2][2] = fRange;
//		M.data.d_p32[2][3] = -1.0f;
//
//		M.data.d_p32[3][0] = 0.0f;
//		M.data.d_p32[3][1] = 0.0f;
//		M.data.d_p32[3][2] = fRange * NearZ;
//		M.data.d_p32[3][3] = 0.0f;
//		return M;
//	};
//
//	inline D_EXPORT _4matrix MatrixTranspose(const _4matrix& in)
//	{
//		_4matrix P;
//		P.data.d_4p32[0] = VectorMergeXY(in.data.d_4p32[0], in.data.d_4p32[2]);
//		P.data.d_4p32[1] = VectorMergeXY(in.data.d_4p32[1], in.data.d_4p32[3]);
//		P.data.d_4p32[2] = VectorMergeZW(in.data.d_4p32[0], in.data.d_4p32[2]);
//		P.data.d_4p32[3] = VectorMergeZW(in.data.d_4p32[1], in.data.d_4p32[3]);
//
//		_4matrix MT;
//		MT.data.d_4p32[0] = VectorMergeXY(P.data.d_4p32[0], P.data.d_4p32[1]);
//		MT.data.d_4p32[1] = VectorMergeZW(P.data.d_4p32[0], P.data.d_4p32[1]);
//		MT.data.d_4p32[2] = VectorMergeXY(P.data.d_4p32[2], P.data.d_4p32[3]);
//		MT.data.d_4p32[3] = VectorMergeZW(P.data.d_4p32[2], P.data.d_4p32[3]);
//
//		return MT;
//	};
//
//	inline D_EXPORT _4matrix MatrixLookToLH(const _4point& eyePosition, const _4point& eyeDirection, const _4point& upDirection)
//	{
//		assert(!Vector3Equal(eyeDirection, _4point::zero()));
//		assert(!Vector3IsInfinite(eyeDirection));
//		assert(!Vector3Equal(upDirection, _4point::zero()));
//		assert(!Vector3IsInfinite(upDirection));
//
//		_4point R2 = Vector3Normalize(eyeDirection);
//
//		_4point R0 = Vector3Cross(upDirection, R2);
//		R0 = Vector3Normalize(R0);
//
//		_4point R1 = Vector3Cross(R2, R0);
//
//		_4point NegEyePosition = VectorNegate(eyePosition);
//
//		_4point D0 = Vector3Dot(R0, NegEyePosition);
//		_4point D1 = Vector3Dot(R1, NegEyePosition);
//		_4point D2 = Vector3Dot(R2, NegEyePosition);
//
//		_4matrix M;
//		M.data.d_4p32[0] = VectorSelect(D0, R0, _4point::select1110());
//		M.data.d_4p32[1] = VectorSelect(D1, R1, _4point::select1110());
//		M.data.d_4p32[2] = VectorSelect(D2, R2, _4point::select1110());
//		M.data.d_4p32[3] = _4point::identityR3().data;
//
//		M = MatrixTranspose(M);
//
//		return M;
//	};
//
//	inline D_EXPORT _4matrix MatrixLookAtRH(const _4point& eyePosition, const _4point& focusPosition, const _4point& upDirection)
//	{
//		_4point NegEyeDirection = eyePosition - focusPosition;
//		return MatrixLookToLH(eyePosition, NegEyeDirection, upDirection);
//	};
//}