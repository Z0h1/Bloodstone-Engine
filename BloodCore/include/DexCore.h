#pragma once

#include "DEXPreCompletion.h"

class DEX_EXPORT DEXCore
{
public:
	DEXCore();

	DEX_PVOID NewMemory(DEX_UINT size_one_block);
	DEX_PVOID NewMemory(DEX_UINT size_one_block, DEX_UINT count_block);

	DEX_PCollection NewCollection(DEX_UINT size_one_block);
	DEX_PCollection NewCollection(DEX_UINT size_one_block, DEX_UINT count_block);

	// Debug
	void FreeAllMemory();
	void PrintMemory(bool show = false);

	DEX_PClass InitSystem();

private:
	DEX_PMemory			pMemoryOverwatch;
	DEX_BOOL			bMemoryDebug;
	DEX_UINT			nMemoryCountBlock;
	DEX_UINT			nMemoryBlockStep;
	DEX_UINT			nMemoryMaxCountBlock;
};
