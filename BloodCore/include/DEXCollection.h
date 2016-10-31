#pragma once

#include "DEXPreCompletion.h"
#include "DEXClass.h"

template<typename T>
class DEX_EXPORT DEXCollection : public DEXClass
{
public:
	DEXCollection(DEX_PCore core)
	{
		pInformation = nullptr;
	}

	DEXCollection(DEX_PCore core, DEX_UINT count_block)
	{

	}

	void PushBack(DEX_PVOID information)
	{

	}

	void PushBack(T *information)
	{

	}

private:
	DEX_PVOID		pInformation;
	DEX_UINT		nCountBlock;
	DEX_UINT		nSizeOneBlock;

	bool ResizeArray(DEX_UINT new_count)
	{

	}
};


