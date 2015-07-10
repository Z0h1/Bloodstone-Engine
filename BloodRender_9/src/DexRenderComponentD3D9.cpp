#include "DexRenderComponentD3D9.h"

namespace Dex
{
	RenderComponentD3D9::RenderComponentD3D9(void)
	{
		m_pDeclarationD3D9 = 0;
		m_bUseIndex = false;
		D3DXMatrixIdentity(&m_WorldMatrixD3D9);
	}

	RenderComponentD3D9::~RenderComponentD3D9(void)
	{
		D_RELEASE(m_sIndexBufferD3D9->m_pIndexBufferD3D9);
		for (int i = 0; i < m_lVertexBufferD3D9.Size(); ++i)
		{
			D_RELEASE(m_lVertexBufferD3D9[i]->m_pVertexBufferD3D9);
		}
		m_lVertexBufferD3D9.Clear();
		D_RELEASE(m_pDeclarationD3D9);
	}

	void RenderComponentD3D9::SetIndexBufferD3D9(g_sIndexBufferD3D9* sIndexBufferD3D9)
	{
		m_sIndexBufferD3D9 = sIndexBufferD3D9;
		m_bUseIndex = true;
	}

	void RenderComponentD3D9::SetDeclarationD3D9(IDirect3DVertexDeclaration9* pDeclarationD3D9)
	{
		m_pDeclarationD3D9 = pDeclarationD3D9;
	}

	void RenderComponentD3D9::AddVertexBufferD3D9(g_sVertexBufferD3D9* sVertexBufferD3D9)
	{
		m_lVertexBufferD3D9.Add(sVertexBufferD3D9);
	}

	void RenderComponentD3D9::RemoveVertexBufferD3D9(g_sVertexBufferD3D9* sVertexBufferD3D9)
	{
		m_lVertexBufferD3D9.Remove(sVertexBufferD3D9);
	}

	const g_lVertexBufferD3D9& RenderComponentD3D9::GetListVertexBufferD3D9(void)
	{
		return m_lVertexBufferD3D9;
	}

	g_sIndexBufferD3D9* RenderComponentD3D9::GetIndexBufferD3D9(void)
	{
		return m_sIndexBufferD3D9;
	}

	IDirect3DVertexDeclaration9* RenderComponentD3D9::GetDeclarationD3D9(void)
	{
		return m_pDeclarationD3D9;
	}

	bool RenderComponentD3D9::GetUseIndex(void)
	{
		return m_bUseIndex;
	}

	void RenderComponentD3D9::CalculateMatrix(const Point3& position, const Point3& rotation, const Point3& scale)
	{
		D3DXMATRIX buffer;
		D3DXMatrixIdentity(&m_WorldMatrixD3D9);

		// Rotation X
		D3DXMatrixIdentity(&buffer);
		D3DXMatrixRotationX(&buffer, D3DXToRadian(rotation.x));
		D3DXMatrixMultiply(&m_WorldMatrixD3D9, &buffer, &m_WorldMatrixD3D9);

		// Rotation Y
		D3DXMatrixIdentity(&buffer);
		D3DXMatrixRotationY(&buffer, D3DXToRadian(rotation.y));
		D3DXMatrixMultiply(&m_WorldMatrixD3D9, &buffer, &m_WorldMatrixD3D9);

		// Rotation Z
		D3DXMatrixIdentity(&buffer);
		D3DXMatrixRotationZ(&buffer, D3DXToRadian(rotation.z));
		D3DXMatrixMultiply(&m_WorldMatrixD3D9, &buffer, &m_WorldMatrixD3D9);

		// Scaling
		D3DXMatrixIdentity(&buffer);
		D3DXMatrixScaling(&buffer, scale.x, scale.y, scale.z);
		D3DXMatrixMultiply(&m_WorldMatrixD3D9, &buffer, &m_WorldMatrixD3D9);

		// Translation
		D3DXMatrixIdentity(&buffer);
		D3DXMatrixTranslation(&buffer, position.x, position.y, position.z);
		D3DXMatrixMultiply(&m_WorldMatrixD3D9, &buffer, &m_WorldMatrixD3D9);
	}

	const D3DXMATRIX& RenderComponentD3D9::GetMatrixD3D9(void)
	{
		return m_WorldMatrixD3D9;
	}
}