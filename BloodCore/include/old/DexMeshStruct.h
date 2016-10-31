#pragma once

#include "DexPreCompletion.h"
#include "DexCommon.h"

namespace DEX
{
	enum MeshStruct
	{
		MESH_VERSION,
		// int ( version mesh )
		MESH_GEOMETRY,
			// bool ( bUseIndex )
			MESH_GEOMETRY_INDEX,
			// int ( enum IndexType )
			// unsigned int ( Index count )
			// Ptr
			MESH_GEOMETRY_VERTEX,
				// unsigned int ( Vertex count )
				MESH_GEOMETRY_VERTEX_ELEMENT,
				// int ( enum VertexSemantics )
				MESH_GEOMETRY_VERTEX_ELEMENT_END,
				// Ptr
			MESH_GEOMETRY_VERTEX_END,
		MESH_GEOMETRY_END
	};
}