#pragma once

#include "DexPreCompletionD3D9.h"
#include "DexCommon.h"
#include "DexCoreObject.h"

namespace Dex
{
	class D_EXPORT_D3D9 RenderAdapterD3D9 : public CoreObject
	{
	public:
		RenderAdapterD3D9(ofstream* logger, UINT id, IDirect3D9* d3d9 );

		const _lString& GetDisplayMode( void );

	private:
		UINT					m_nId;

		_lString				m_lDisplayMode;

		// DirectX Setting
		IDirect3D9*				m_pD3D9;
		D3DADAPTER_IDENTIFIER9	m_AdapterIdentifier;
	};
}