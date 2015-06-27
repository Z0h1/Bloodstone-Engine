#pragma once

#include <fstream>

using namespace std;

namespace Bloodstone
{

#ifdef BLOODCORE_EXPORTS
#define BLOODCORE_API __declspec(dllexport) 
#else
#define BLOODCORE_API __declspec(dllimport) 
#endif

	typedef unsigned int UInt32;

	class BObject;
	class BCollection;
	class BSortedCollection;
}