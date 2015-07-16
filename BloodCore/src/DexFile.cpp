#include "DexFile.h"
#include "DexIndexBuffer.h"
#include "DexVertexBuffer.h"

namespace Dex
{
	File::File(ofstream* logger, Folder* pParent, const string& cPath, const string& cName)
		: CoreFile(logger, pParent, FileFormat::FF_DEXG, cPath, cName), Serializer(cPath)
	{	
	}
}