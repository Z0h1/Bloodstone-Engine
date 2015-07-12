#include "DexGeometryFile.h"

namespace Dex
{
	GeometryFile::GeometryFile(ofstream* logger, Folder* pParent, const string& cPath, const string& cName)
		: CoreFile(logger, pParent, FileFormat::FF_DEXG, cPath, cName),
		Serializer(cName, logger, cPath)
	{

	}
}