#pragma once

#include "DexPreCompletion.h"

namespace Dex
{
	class D_EXPORT StringConverter
	{
	public:
		static void trim(string& s, bool left = true, bool right = true);

		// toString
		static string toString(const char* value);
		static string toString_on_off(bool value);
		static string toString_true_false(bool value);
		static string toString_1_0(bool value);
		static string toString(int value);
		static string toString(unsigned long value);
		static string toString(size_t value);
		static string toString(_point X, _point Y, _point Z);
		static string toString(const PrimitiveType& type);
		static string toString(int nWidth, int nHeight, int nBit);
		static string toStringPoint4(_point x, _point y, _point z, _point w);
		static string toString(_point x);

		// Parse
		static bool Parse_bool(string value, bool default_value = false);
		static int Parse_int(string value, int default_value = 0);
		static _point Parse_Point(string value, _point default_value = 0.0f);
		static _4point Parse_Point4(string value);
		static unsigned int Parse_unsigned_int(string value, unsigned int default_value = 0);
		static size_t Parse_size_t(string value, size_t default_value = 0);

		static void ParseDisplyaMode(const string& mode, _32un& Width, _32un& Height, _32un& bit);
		static void ParseXYZ(const string& str, _point& X, _point& Y, _point& Z);
		static void ParsePrimitiveType(const string& str, PrimitiveType& type);
	};
}