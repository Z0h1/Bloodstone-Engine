#include "DEXCore.h"
#include "DEXClass.h"
#include "DEXCollection.h"

DEXCore::DEXCore()
{
	bMemoryDebug = true;
}

DEX_PVOID DEXCore::NewMemory(DEX_UINT size_one_block)
{
	return NewMemory(size_one_block, 1);
}

DEX_PVOID DEXCore::NewMemory(DEX_UINT size_one_block, DEX_UINT count_block)
{
	DEX_PVOID m = malloc(count_block * size_one_block);

	if (!m)
	{
		//error
		return nullptr;
	}

	if (bMemoryDebug)
	{
		if (!pMemoryOverwatch)
		{
			nMemoryMaxCountBlock = nMemoryBlockStep;
			pMemoryOverwatch = new DEXMemory[nMemoryMaxCountBlock];
			nMemoryCountBlock = 0;
		}

		if ((nMemoryCountBlock + 1) > nMemoryMaxCountBlock)
		{
			nMemoryMaxCountBlock += nMemoryBlockStep;
			pMemoryOverwatch = static_cast<DEX_PMemory>(
				realloc(pMemoryOverwatch, nMemoryCountBlock * sizeof(DEXMemory))
			);
		}

		DEXMemory info_m;
		info_m.nCountBlock = count_block;
		info_m.nSizeOneBlock = size_one_block;
		info_m.pFirstAddres = m;

		pMemoryOverwatch[nMemoryCountBlock] = info_m;
		nMemoryCountBlock++;
	}

	return m;
}

DEX_PCollection DEXCore::NewCollection(DEX_UINT size_one_block)
{
	DEX_PCollection collection = static_cast<DEX_PCollection>(
		NewMemory(sizeof(DEXCollection))
	);

	return collection;
}

DEX_PCollection DEXCore::NewCollection(DEX_UINT size_one_block, DEX_UINT count_block)
{

}

// Debug
void DEXCore::FreeAllMemory()
{
	if (!pMemoryOverwatch)
	{
		return;
	}

	for (int a = 0; a < nMemoryCountBlock; a++)
	{
		DEXMemory m = pMemoryOverwatch[a];

		free(m.pFirstAddres);
	}

	free(pMemoryOverwatch);

	pMemoryOverwatch = nullptr;
	nMemoryCountBlock = 0;
}

void DEXCore::PrintMemory(bool show)
{
	//if (!pMemory)
	//{
	//	//std::cout << "error memory" << std::endl;
	//	return;
	//}

	//float AllMemorySize = 0;

	//for (int a = 0; a < nMemoryCount; a++)
	//{
	//	DEXMemory m = pMemory[a];

	//	if (show)
	//	{
	//		//std::cout << m.pFirstAddres << " = " << m.nCountBlock << " * " << m.nSizeOneBlock << std::endl;
	//	}

	//	AllMemorySize += m.nCountBlock * m.nSizeOneBlock;
	//}

	////std::cout << "Memory = " << (AllMemorySize / 1024) / 1024 << " mb, Count block = " << nMemoryCount << std::endl;
}

DEX_PClass DEXCore::InitSystem()
{
	return nullptr;
}
