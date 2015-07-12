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
		static string toString(Point X, Point Y, Point Z);
		static string toString(const PrimitiveType& type);
		static string toString(int nWidth, int nHeight, int nBit);
		static string toStringPoint4(Point x, Point y, Point z, Point w);
		static string toString(Point x);

		// Parse
		static bool Parse_bool(string value, bool default_value = false);
		static int Parse_int(string value, int default_value = 0);
		static Point Parse_Point(string value, Point default_value = 0.0f);
		static Point4 Parse_Point4(string value);
		static unsigned int Parse_unsigned_int(string value, unsigned int default_value = 0);
		static size_t Parse_size_t(string value, size_t default_value = 0);

		static void ParseDisplyaMode(const string& mode, UInt32& Width, UInt32& Height, UInt32& bit);
		static void ParseXYZ(const string& str, Point& X, Point& Y, Point& Z);
		static void ParsePrimitiveType(const string& str, PrimitiveType& type);
	};
}