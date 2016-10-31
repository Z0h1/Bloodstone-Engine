#pragma once

#include <cstdlib>



class DEXContainerBox
{
public:
	DEXContainerBox()
	{
	}

	void Add(void* pData)
	{
		BOX pNewBox;
		pNewBox.pData = pData;	

		if (0)
		{
			//pNewBox.pNextBox = pFirstBox;
		}
		else
		{
			//pNewBox.pNextBox = pFirstBox;
			//pFirstBox = 0;
		}
	}

private:
	struct BOX
	{
		void*	pData;
		//BOX	pNextBox;
	};

	BOX	pBox;
	BOX	pFirstBox;
};