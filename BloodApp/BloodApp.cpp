// BloodApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "DexCore.h"

using namespace Dex;

int _tmain(int argc, _TCHAR* argv[])
{
	Core* bc = new Core();
	//BSRender* rs = bc->LoadSystem(BS_RENDER, SV_D11);

	delete bc;

	return 0;
}

