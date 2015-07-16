#pragma once

#include "DexPreCompletion.h"
#include "DexMath.h"

namespace Dex
{
	// constant buffer

	struct ConstantBuffer_ModelViewProjection
	{
		Matrix4 model;
		Matrix4 view;
		Matrix4 projection;
	};

	// vertex layout

	struct Vertex_PositionColor
	{
		Point3 pos;
		Point3 color;
	};

	struct Vertex_PositionTextureNormal
	{
		Point3 pos;
		Point2 tex;
		Point3 nrm;
	};
}