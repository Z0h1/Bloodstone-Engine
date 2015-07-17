#pragma once

#include "DexPreCompletion.h"
#include "DexMath.h"

namespace Dex
{
	// constant buffer

	struct ConstantBuffer_ModelViewProjection
	{
		_4matrix model;
		_4matrix view;
		_4matrix projection;
	};

	// vertex layout

	struct Vertex_PositionColor
	{
		_3point pos;
		_3point color;
	};

	struct Vertex_PositionTextureNormal
	{
		_3point pos;
		_2point tex;
		_3point nrm;
	};
}