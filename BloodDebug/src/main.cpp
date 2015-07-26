#include "Dex.h"

using namespace Dex;

void main()
{
	//Core* cr = new Core();

	_4matrix m1(
		1.0f, 2.0f, 3.0f, 5.0f,
		4.0f, -9.0f, 12.0f, 4.0f,
		0.0f, 4.0f, -1.0f, 9.0f,
		11.0f, -5.0f, 3.0f, 7.0f
	);
	_4matrix m2(
		8.0f, 6.0f, 5.0f, 3.0f,
		9.0f, -9.0f, 17.0f, 2.0f,
		5.0f, 6.0f, -2.0f, 6.0f,
		41.0f, -1.0f, 2.0f, 4.0f
	);

	m1 = m1 * m2;

	//cr->DrawLine(StringConverter::toString(m1));

	//delete cr;
}