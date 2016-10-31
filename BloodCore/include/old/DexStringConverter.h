#pragma once

#include "DexPreCompletion.h"

void DEXTrim(string& s, bool left = true, bool right = true);

// toString
string D_EXPORT DEXtoString(const char* value);
string D_EXPORT DEXtoString_on_off(bool value);
string D_EXPORT DEXtoString_true_false(bool value);
string D_EXPORT DEXtoString_1_0(bool value);
string D_EXPORT DEXtoString(int value);
string D_EXPORT DEXtoString(unsigned long value);
string D_EXPORT DEXtoString(size_t value);
//string D_EXPORT DEXtoString(_point X, _point Y, _point Z);
//string D_EXPORT DEXtoString(const PrimitiveType& type);
string D_EXPORT DEXtoString(int nWidth, int nHeight, int nBit);
//string D_EXPORT DEXtoString(_point x, _point y, _point z, _point w);
//string D_EXPORT DEXtoString(_point x);
//string D_EXPORT DEXtoString(const _3DMatrix& x);

// Parse
bool D_EXPORT DEXParse_bool(string value, bool default_value = false);
int	D_EXPORT DEXParse_int(string value, int default_value = 0);
//_point D_EXPORT DEXParse_Point(string value, _point default_value = 0.0f);
//_4point D_EXPORT DEXParse_Point4(string value);
unsigned int D_EXPORT DEXParse_unsigned_int(string value, unsigned int default_value = 0);
size_t D_EXPORT DEXParse_size_t(string value, size_t default_value = 0);

//void D_EXPORT DEXParseDisplyaMode(const string& mode, _32un& Width, _32un& Height, _32un& bit);
//void D_EXPORT DEXParseXYZ(const string& str, _point& X, _point& Y, _point& Z);
//void D_EXPORT DEXParsePrimitiveType(const string& str, PrimitiveType& type);