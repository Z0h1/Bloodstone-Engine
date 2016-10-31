#pragma once

#include "DexPreCompletion.h"
#include "DexMathConst.h"

namespace DEX
{
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

		inline ~_2point(void)
		{
		}

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

		_2point_dat data;
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

		inline ~_3point(void)
		{
		}

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

		_3point_dat data;
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

		inline ~_4point(void)
		{
		}

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

		inline _4point_dat operator =
			(
				const _4point_dat& in_point_B
				)
		{
			data.d_p32[0] = in_point_B.d_p32[0];

			return data;
		}

		_4point_dat data;
	};
}