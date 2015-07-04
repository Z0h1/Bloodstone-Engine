#pragma once

#include "DexPreCompletionD3D9.h"
#include "DexCommon.h"

namespace Dex
{
	typedef struct _sVertexBufferD3D9
	{
		IDirect3DVertexBuffer9*  m_pVertexBufferD3D9;
		unsigned int m_nVertexCount;
		int m_nOffset;

	} g_sVertexBufferD3D9;

	typedef struct _sIndexBufferD3D9
	{
		IDirect3DIndexBuffer9*  m_pIndexBufferD3D9;
		unsigned int m_nIndexCount;
		int m_nOffset;

	} g_sIndexBufferD3D9;

	typedef IndexedArray< g_sVertexBufferD3D9* >	g_lVertexBufferD3D9;

	class D_EXPORT_D3D9 RenderComponentD3D9
	{
	public:
		RenderComponentD3D9( void );
		~RenderComponentD3D9( void );

		void SetIndexBufferD3D9( g_sIndexBufferD3D9* sIndexBufferD3D9 );
		void SetDeclarationD3D9( IDirect3DVertexDeclaration9* pDeclarationD3D9 );
		void AddVertexBufferD3D9( g_sVertexBufferD3D9* sVertexBufferD3D9 );
		void RemoveVertexBufferD3D9( g_sVertexBufferD3D9* sVertexBufferD3D9 );

		const g_lVertexBufferD3D9& GetListVertexBufferD3D9( void );
		g_sIndexBufferD3D9* GetIndexBufferD3D9( void );
		IDirect3DVertexDeclaration9* GetDeclarationD3D9( void );
		bool GetUseIndex( void );

		void CalculateMatrix( const Point3& position, const Point3& rotation, const Point3& scale );

		const D3DXMATRIX& GetMatrixD3D9( void );

	private:
		IDirect3DVertexDeclaration9*		m_pDeclarationD3D9;
		g_lVertexBufferD3D9					m_lVertexBufferD3D9;
		g_sIndexBufferD3D9*					m_sIndexBufferD3D9;

		D3DXMATRIX							m_WorldMatrixD3D9;

		bool								m_bUseIndex;
	};
}