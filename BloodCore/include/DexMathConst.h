#pragma once

namespace Dex
{
	const _point MDEX_PI = 3.141592654f;
	const _point MDEX_2PI = 6.283185307f;
	const _point MDEX_1DIVPI = 0.318309886f;
	const _point MDEX_1DIV2PI = 0.159154943f;
	const _point MDEX_PIDIV2 = 1.570796327f;
	const _point MDEX_PIDIV4 = 0.785398163f;

	const _32un MDEX_SELECT_0 = 0x00000000;
	const _32un MDEX_SELECT_1 = 0xFFFFFFFF;

	typedef struct
	{
		union
		{
			_point			d_p32[2];
			_32un			d_u32[2];
		};
	} _2point_dat;

	typedef struct
	{
		union
		{
			_point			d_p32[3];
			_32un			d_u32[3];
		};
	} _3point_dat;

	typedef struct
	{
		union
		{
			_point			d_p32[4];
			_32un			d_u32[4];
		};
	} _4point_dat;

	typedef struct
	{
		union
		{
			_4point_dat	   d_4p32[4];
			_point			d_p32[4][4];
			_32un			d_u32[4][4];
		};
	} _4matrix_dat;
}