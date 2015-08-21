#include "Dex.h"
#include "DEXString.h"
#include "DEXCOL.h"

#include <iostream>

using namespace Dex;

void main()
{
	//Core* cr = new Core();

	/*_3DMatrix m1(
		1.0f, 2.0f, 3.0f, 5.0f,
		4.0f, -9.0f, 12.0f, 4.0f,
		0.0f, 4.0f, -1.0f, 9.0f,
		11.0f, -5.0f, 3.0f, 7.0f
	);
	_3DMatrix m2(
		8.0f, 6.0f, 5.0f, 3.0f,
		9.0f, -9.0f, 17.0f, 2.0f,
		5.0f, 6.0f, -2.0f, 6.0f,
		41.0f, -1.0f, 2.0f, 4.0f
	);

	m1 = m1 * m2;

	_3DVector v1(1.5f, 2.1f, 6.0f);
	_3DVector v1_n;

	v1_n = Normalize(v1);*/

	/*DEXString str("hallo world");

	std::cout << str.Get();*/

	/*DEXIndexedDynamicArray a;

	for (DEXUINT n = 0; n < 1999; n++)
	{
		a.Insert(new DEXUINT(static_cast<DEXUINT>(rand() % 1999)));

		std::cout << a[n];
	}

	a.Clear();*/

	DEXUINT* a = DEXArrayNew<DEXUINT>(2000);
	a[0] = static_cast<DEXUINT>(15);
	for (DEXUINT n = 1; n < DEXArrayGetCount<DEXUINT>(a); n++)
	{
		a[n] = static_cast<DEXUINT>(rand() % 1999);
	}
	a[2000] = static_cast<DEXUINT>(15);

	DEXUINT index = 0;
	if (DEXArraySearchFirst<DEXUINT>(a, 15, index)) {
		std::cout << index << std::endl;
	}

	if (DEXArraySearchLast<DEXUINT>(a, 15, index)) {
		std::cout << index << std::endl;
	}

	for (DEXUINT n = 1; n < DEXArrayGetCount<DEXUINT>(a); n++)
	{
		std::cout << a[n] << std::endl;
	}
	DEXARRAYDELETE(DEXUINT, a);

	//cr->DrawLine(StringConverter::toString(m1));

	//delete cr;
}