#include "DexStringConverter.h"
#include "DexMath.h"

void DEXTrim(string& s, bool left, bool right)
{
	const string delims = " \t\r";

	if (right)
	{
		s.erase(s.find_last_not_of(delims) + 1); // trim right
	}

	if (left)
	{
		s.erase(0, s.find_first_not_of(delims)); // trim left
	}
}

string DEXtoString(const char* value)
{
	stringstream String;
	String << value;
	return String.str();
}

string DEXtoString_on_off(bool value)
{
	string result;
	if (value)
	{
		result = "on";
	}
	else
	{
		result = "off";
	}
	return result;
}

string DEXtoString_true_false(bool value)
{
	string result;
	if (value)
	{
		result = "true";
	}
	else
	{
		result = "false";
	}
	return result;
}

string DEXtoString_1_0(bool value)
{
	string result;
	if (value)
	{
		result = "0";
	}
	else
	{
		result = "1";
	}
	return result;
}

string DEXtoString(int value)
{
	stringstream String;
	String << value;
	return String.str();
}

string DEXtoString(unsigned long value)
{
	stringstream String;
	String << value;
	return String.str();
}

string DEXtoString(size_t value)
{
	stringstream String;
	String << value;
	return String.str();
}

//string DEXtoString(_point X, _point Y, _point Z)
//{
//	stringstream String;
//	String << X << " " << Y << " " << Z;
//	return String.str();
//}

//string DEXtoString(const PrimitiveType& type)
//{
//	string str = "";
//
//	if (type == PT_POINT)
//	{
//		str == "_point";
//	}
//	else if (type == PT_LINE)
//	{
//		str == "line";
//	}
//	else if (type == PT_POLYGON)
//	{
//		str == "polygon";
//	}
//
//	return str;
//}

string DEXtoString(int nWidth, int nHeight, int nBit)
{
	stringstream cString;

	cString << nWidth << "x" << nHeight << "-" << nBit;

	return cString.str();
}

//string DEXtoStringPoint4(_point x, _point y, _point z, _point w)
//{
//	stringstream cString;
//
//	cString << x << " " << y << " " << z << " " << w;
//
//	return cString.str();
//}

//string DEXtoString(_point x)
//{
//	stringstream cString;
//
//	cString << x;
//
//	return cString.str();
//}
//
//string DEXtoString(const _3DMatrix& x)
//{
//	stringstream str;
//	str << endl;
//	str << x.data.d_p32[0][0] << " " << x.data.d_p32[0][1] << " " << x.data.d_p32[0][2] << " " << x.data.d_p32[0][3] << endl;
//	str << x.data.d_p32[1][0] << " " << x.data.d_p32[1][1] << " " << x.data.d_p32[1][2] << " " << x.data.d_p32[1][3] << endl;
//	str << x.data.d_p32[2][0] << " " << x.data.d_p32[2][1] << " " << x.data.d_p32[2][2] << " " << x.data.d_p32[2][3] << endl;
//	str << x.data.d_p32[3][0] << " " << x.data.d_p32[3][1] << " " << x.data.d_p32[3][2] << " " << x.data.d_p32[3][3] << endl;
//	str << endl;
//	return str.str();
//}

bool DEXParse_bool(string value, bool default_value)
{
	bool result = default_value;
	if (value == "on" || value == "true" || value == "1")
	{
		result = true;
	}
	else if (value == "off" || value == "false" || value == "0")
	{
		result = false;
	}

	return result;
}

int DEXParse_int(string value, int default_value)
{
	stringstream String(value);
	int result = default_value;
	if (!(String >> result))
		return default_value;

	return result;
}

//_point DEXParse_Point(string value, _point default_value)
//{
//	stringstream String(value);
//	_point result = default_value;
//	if (!(String >> result))
//		return default_value;
//
//	return result;
//}
//
//_4point DEXParse_Point4(string value)
//{
//	stringstream String(value);
//	_point x, y, z, w;
//	String >> x >> y >> z >> w;
//
//	return _4point(x, y, z, w);
//}

unsigned int DEXParse_unsigned_int(string value, unsigned int default_value)
{
	stringstream String(value);
	unsigned int result = default_value;
	if (!(String >> result))
		return default_value;

	return result;
}

size_t DEXParse_size_t(string value, size_t default_value)
{
	stringstream String(value);
	size_t result = default_value;
	if (!(String >> result))
		return default_value;

	return result;
}

//void DEXParseDisplyaMode(const string& mode, _32un& Width, _32un& Height, _32un& bit)
//{
//	string buffer;
//
//	string::size_type x_pos = mode.find_first_of("x", 0);
//	string::size_type space_pos = mode.find_first_of("-", 0);
//
//	buffer = mode.substr(0, x_pos);
//	Width = atoi(buffer.c_str());
//
//	buffer = mode.substr(x_pos + 1, space_pos);
//	Height = atoi(buffer.c_str());
//
//	buffer = mode.substr(space_pos + 1, mode.length());
//	bit = atoi(buffer.c_str());
//}

void DEXParseXYZ(const string& str, float& X, float& Y, float& Z)
{
	stringstream stream;

	stream << str;

	stream >> X >> Y >> Z;
}

//void DEXParsePrimitiveType(const string& str, PrimitiveType& type)
//{
//	if (str == "_point")
//	{
//		type = PT_POINT;
//	}
//	else if (str == "line")
//	{
//		type = PT_LINE;
//	}
//	else if (str == "polygon")
//	{
//		type = PT_POLYGON;
//	}
//}