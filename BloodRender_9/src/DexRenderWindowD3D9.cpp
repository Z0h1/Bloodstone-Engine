#include "DexRenderWindowD3D9.h"
#include "DexStringConverter.h"
#include "DexHardwareBufferData.h"
#include "DexHardwareVertexBuffer.h"
#include "DexHardwareIndexBuffer.h"
#include "DexRenderComponent.h"
#include "DexRenderComponentD3D9.h"
#include "DexLightComponent.h"
#include "DexCameraComponent.h"
#include "DexCore.h"

namespace Dex
{
	RenderWindowD3D9::RenderWindowD3D9(ofstream* logger, UINT adapter, D3DDEVTYPE type, IDirect3D9* d3d9)
		: IRenderWindow("", logger)
	{
		m_nAdapter = adapter;
		m_DeviceType = type;
		m_pD3D9 = d3d9;

		ZeroMemory(&m_d3d_pp, sizeof(D3DPRESENT_PARAMETERS));
		m_pDevice9 = 0;
		m_LightCount = 0;
	}

	RenderWindowD3D9::~RenderWindowD3D9(void)
	{
		D_RELEASE(m_pDevice9);
	}

	bool RenderWindowD3D9::Create(const _lParametor& config, HWND h)
	{
		_lParametor::const_iterator it;

		it = config.find("window_name");
		if (it != config.end())
		{
			mObjectName = it->second;
		}

		it = config.find("window_handle");
		if (it != config.end())
		{
			m_d3d_pp.hDeviceWindow = h;
		}
		else
		{
			DrawLine("RenderWindowD3D9:Init \"window_handle\" не указан", MT_ERROR);
			return false;
		}

		m_d3d_pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		m_d3d_pp.EnableAutoDepthStencil = TRUE;
		m_d3d_pp.BackBufferFormat = D3DFMT_UNKNOWN;
		m_d3d_pp.BackBufferHeight = 0;
		m_d3d_pp.BackBufferWidth = 0;

		it = config.find("display_mode");
		if (it != config.end())
		{
			StringConverter::ParseDisplyaMode(it->second, m_nWidth, m_nHeight, m_nBit);
		}
		else
		{
			DrawLine("RenderWindowD3D9:Init \"display_mode\" не указано", MT_WARNING);

			m_nWidth = 800;
			m_nHeight = 600;
			m_nBit = 32;
		}

		if (m_nBit == 32)
		{
			m_d3d_pp.BackBufferFormat = D3DFMT_X8R8G8B8;

			if (FAILED(m_pD3D9->CheckDeviceFormat(m_nAdapter, m_DeviceType,
				D3DFMT_X8R8G8B8, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D24S8)))
			{
				if (FAILED(m_pD3D9->CheckDeviceFormat(m_nAdapter, m_DeviceType,
					D3DFMT_X8R8G8B8, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D32)))
				{
					m_d3d_pp.AutoDepthStencilFormat = D3DFMT_D16;
				}
				else
				{
					m_d3d_pp.AutoDepthStencilFormat = D3DFMT_D32;
				}
			}
			else
			{
				if (SUCCEEDED(m_pD3D9->CheckDepthStencilMatch(m_nAdapter, m_DeviceType,
					D3DFMT_X8R8G8B8, D3DFMT_X8R8G8B8, D3DFMT_D24S8)))
				{
					m_d3d_pp.AutoDepthStencilFormat = D3DFMT_D24S8;
				}
				else
				{
					m_d3d_pp.AutoDepthStencilFormat = D3DFMT_D24X8;
				}
			}
		}
		else if (m_nBit == 16)
		{
			m_d3d_pp.BackBufferFormat = D3DFMT_R5G6B5;
			m_d3d_pp.AutoDepthStencilFormat = D3DFMT_D16;
		}

		m_d3d_pp.BackBufferHeight = m_nHeight;
		m_d3d_pp.BackBufferWidth = m_nWidth;

		it = config.find("full_screan_mode");
		if (it != config.end())
		{
			if (it->second == "on")
			{
				m_FullScrean = true;
				m_d3d_pp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
			}
			else if (it->second == "off")
			{
				m_FullScrean = false;
			}
			else
			{
				DrawLine("RenderWindowD3D9:Init \"full_screan_mode\" значение не опознано \"on\" или \"off\"", MT_WARNING);
				m_FullScrean = false;
			}
		}

		m_VSync = false;

		m_d3d_pp.Windowed = !m_FullScrean;
		m_d3d_pp.BackBufferCount = m_VSync ? 2 : 1;
		HRESULT result;

		result = m_pD3D9->CreateDevice(m_nAdapter, m_DeviceType, m_d3d_pp.hDeviceWindow,
			D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_d3d_pp, &m_pDevice9);

		it = config.find("vertex_processing");
		if (it != config.end())
		{
			D_RELEASE(m_pDevice9);

			if (it->second == "Software")
			{
				result = m_pD3D9->CreateDevice(m_nAdapter, m_DeviceType, m_d3d_pp.hDeviceWindow,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_d3d_pp, &m_pDevice9);
			}
			else if (it->second == "Mixed")
			{
				result = m_pD3D9->CreateDevice(m_nAdapter, m_DeviceType, m_d3d_pp.hDeviceWindow,
					D3DCREATE_MIXED_VERTEXPROCESSING, &m_d3d_pp, &m_pDevice9);
			}
		}

		if (FAILED(result))
		{
			/*String error = DXGetErrorDescription(result);
			DrawLine("RenderWindowD3D9:CreateDevice Ошибка - " + error);*/

			return false;
		}

		m_pDevice9->SetRenderState(D3DRS_ZENABLE, TRUE);

		D3DXMatrixPerspectiveFovLH(&m_ProjectionMatrix, D3DX_PI / 4, (FLOAT)m_nWidth / m_nHeight, 1.0f, 10000.0f);
		m_pDevice9->SetTransform(D3DTS_PROJECTION, &m_ProjectionMatrix);

		return true;
	}

	bool RenderWindowD3D9::IsLostControl(void)
	{
		HRESULT result = m_pDevice9->TestCooperativeLevel();

		if (result == D3DERR_DEVICELOST)
		{
			return true;
		}
		else if (result == D3DERR_DEVICENOTRESET)
		{
			// deinitresurse
			m_pDevice9->Reset(&m_d3d_pp);
			// initresurse

			return false;
		}

		return false;
	}

	void RenderWindowD3D9::CalculateMatrix(RenderComponent* pRenderComponent)
	{
		m_lBufferBind[pRenderComponent]->first->CalculateMatrix(pRenderComponent->GetFullPosition(),
			pRenderComponent->GetFullRotation(), pRenderComponent->GetFullScale());
	}

	void RenderWindowD3D9::SetMatrixIdentity(void)
	{
		D3DXMatrixIdentity(&m_WorldMatrix);
		D3DXMatrixIdentity(&m_ViewMatrix);
		m_LightCount = 0;
	}

	void RenderWindowD3D9::SetViewMatrix(CameraComponent* pCamera)
	{
		D3DXMATRIX nMatrixD3D9;
		D3DXMATRIX nEndMatrixD3D9;

		// Get
		D3DXMATRIX nMatrixRotateRightD3D9;
		Point3 nRight = pCamera->GetRight();
		D3DXVECTOR3 nVectorRight(nRight.x, nRight.y, nRight.z);
		D3DXMatrixRotationAxis(&nMatrixRotateRightD3D9, &nVectorRight, pCamera->GetRotateRight());

		D3DXMATRIX nMatrixRotateLookAtD3D9;
		Point3 nLookAt = pCamera->GetLookAt();
		D3DXVECTOR3 nVectorLookAt(nLookAt.x, nLookAt.y, nLookAt.z);
		D3DXMatrixRotationAxis(&nMatrixRotateLookAtD3D9, &nVectorLookAt, pCamera->GetRotateLookAt());

		D3DXMATRIX nMatrixRotateUpD3D9;
		Point3 nUp = pCamera->GetUp();
		D3DXVECTOR3 nVectorUp(nUp.x, nUp.y, nUp.z);
		D3DXMatrixRotationAxis(&nMatrixRotateUpD3D9, &nVectorUp, pCamera->GetRotateUp());

		Point3 nPosition = pCamera->GetFullPosition();
		D3DXVECTOR3 nVectorPosition(nPosition.x, nPosition.y, nPosition.z);

		// Multiply
		D3DXMatrixMultiply(&nMatrixD3D9, &nMatrixRotateUpD3D9, &nMatrixRotateRightD3D9);
		D3DXMatrixMultiply(&nMatrixD3D9, &nMatrixRotateLookAtD3D9, &nMatrixD3D9);

		D3DXVec3TransformCoord(&nVectorRight, &nVectorRight, &nMatrixD3D9);
		D3DXVec3TransformCoord(&nVectorUp, &nVectorUp, &nMatrixD3D9);
		D3DXVec3Cross(&nVectorLookAt, &nVectorRight, &nVectorUp);

		if (fabs(D3DXVec3Dot(&nVectorUp, &nVectorRight)) > 0.01)
		{
			D3DXVec3Cross(&nVectorUp, &nVectorLookAt, &nVectorRight);
		}

		D3DXVec3Normalize(&nVectorRight, &nVectorRight);
		D3DXVec3Normalize(&nVectorUp, &nVectorUp);
		D3DXVec3Normalize(&nVectorLookAt, &nVectorLookAt);

		float nView41, nView42, nView43;

		nView41 = -D3DXVec3Dot(&nVectorRight, &nVectorPosition);
		nView42 = -D3DXVec3Dot(&nVectorUp, &nVectorPosition);
		nView43 = -D3DXVec3Dot(&nVectorLookAt, &nVectorPosition);

		nEndMatrixD3D9 = D3DXMATRIX(
			nVectorRight.x, nVectorUp.x, nVectorLookAt.x, 0.0f,
			nVectorRight.y, nVectorUp.y, nVectorLookAt.y, 0.0f,
			nVectorRight.z, nVectorUp.z, nVectorLookAt.z, 0.0f,
			nView41, nView42, nView43, 1.0f);

		m_pDevice9->SetTransform(D3DTS_VIEW, &nEndMatrixD3D9);

		pCamera->ResetRotate();
	}

	void RenderWindowD3D9::SetWorldMatrix(const Point3& position, const Point3& rotation, const Point3& scale)
	{
		D3DXMATRIX buffer;

		// Rotation X
		D3DXMatrixIdentity(&buffer);
		D3DXMatrixRotationX(&buffer, D3DXToRadian(rotation.x));
		D3DXMatrixMultiply(&m_WorldMatrix, &buffer, &m_WorldMatrix);

		// Rotation Y
		D3DXMatrixIdentity(&buffer);
		D3DXMatrixRotationY(&buffer, D3DXToRadian(rotation.y));
		D3DXMatrixMultiply(&m_WorldMatrix, &buffer, &m_WorldMatrix);

		// Rotation Z
		D3DXMatrixIdentity(&buffer);
		D3DXMatrixRotationZ(&buffer, D3DXToRadian(rotation.z));
		D3DXMatrixMultiply(&m_WorldMatrix, &buffer, &m_WorldMatrix);

		// Scaling
		D3DXMatrixIdentity(&buffer);
		D3DXMatrixScaling(&buffer, scale.x, scale.y, scale.z);
		D3DXMatrixMultiply(&m_WorldMatrix, &buffer, &m_WorldMatrix);

		// Translation
		D3DXMatrixIdentity(&buffer);
		D3DXMatrixTranslation(&buffer, position.x, position.y, position.z);
		D3DXMatrixMultiply(&m_WorldMatrix, &buffer, &m_WorldMatrix);

		m_pDevice9->SetTransform(D3DTS_WORLD, &m_WorldMatrix);
	}

	bool RenderWindowD3D9::PreRender(void)
	{
		if (SUCCEEDED(m_pDevice9->BeginScene()))
		{
			return true;
		}

		return false;
	}

	void RenderWindowD3D9::RenderObject(RenderComponent* pRenderComponent)
	{
		if (!pRenderComponent->IsActive())
		{
			return;
		}

		_lBufferBind::iterator it_BufferBind = m_lBufferBind.find(pRenderComponent);
		RenderComponentD3D9* pRenderComponentD3D9 = it_BufferBind->second->first;

		const g_lVertexBufferD3D9& lVertexBufferD3D9 = pRenderComponentD3D9->GetListVertexBufferD3D9();

		if (pRenderComponentD3D9 && !lVertexBufferD3D9.Size())
		{
			return;
		}

		unsigned int nVertexCount = 0;

		D3DMATERIAL9 mtrl;
		ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));
		mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
		mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
		mtrl.Diffuse.b = mtrl.Ambient.b = 0.0f;
		mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
		m_pDevice9->SetMaterial(&mtrl);

		m_pDevice9->SetRenderState(D3DRS_LIGHTING, TRUE);

		if (pRenderComponent->IsCalculateMatrix())
		{
			CalculateMatrix(pRenderComponent);
		}

		m_pDevice9->SetTransform(D3DTS_WORLD, &pRenderComponentD3D9->GetMatrixD3D9());

		m_pDevice9->SetVertexDeclaration(pRenderComponentD3D9->GetDeclarationD3D9());

		for (int n = 0; n < lVertexBufferD3D9.Size(); ++n)
		{
			g_sVertexBufferD3D9* sVertexBufferD3D9 = lVertexBufferD3D9[n];

			m_pDevice9->SetStreamSource(n, sVertexBufferD3D9->m_pVertexBufferD3D9, 0,
				sVertexBufferD3D9->m_nOffset);

			if (nVertexCount < sVertexBufferD3D9->m_nVertexCount)
			{
				nVertexCount = sVertexBufferD3D9->m_nVertexCount;
			}
		}

		UINT nPrimitiveCount = nVertexCount;
		D3DPRIMITIVETYPE ePrimitiveType = D3DPT_POINTLIST;

		if (pRenderComponent->GetPrimitiveType() == PT_LINE)
		{
			ePrimitiveType = D3DPT_LINESTRIP;
		}
		else if (pRenderComponent->GetPrimitiveType() == PT_POLYGON)
		{
			ePrimitiveType = D3DPT_TRIANGLELIST;
		}

		if (pRenderComponentD3D9->GetUseIndex())
		{
			g_sIndexBufferD3D9* sIndexBufferD3D9 = pRenderComponentD3D9->GetIndexBufferD3D9();

			m_pDevice9->SetIndices(sIndexBufferD3D9->m_pIndexBufferD3D9);

			nPrimitiveCount = sIndexBufferD3D9->m_nIndexCount;

			if (pRenderComponent->GetPrimitiveType() == PT_LINE)
			{
				nPrimitiveCount = sIndexBufferD3D9->m_nIndexCount - 1;
			}
			else if (pRenderComponent->GetPrimitiveType() == PT_POLYGON)
			{
				nPrimitiveCount = sIndexBufferD3D9->m_nIndexCount / 3;
			}

			HRESULT hr = m_pDevice9->DrawIndexedPrimitive(ePrimitiveType, 0, 0,
				nVertexCount, 0, nPrimitiveCount);
		}
		else
		{
			/*
			HRESULT hr = m_pDevice9->DrawPrimitive( PrimitiveType, 0, 0,
				nVertexCount, 1, sIndexBufferD3D9.m_nIndexCount );
			*/
		}
	}

	void RenderWindowD3D9::SetLight(LightComponent* pLightComponent)
	{
		D3DLIGHT9 light;
		ZeroMemory(&light, sizeof(D3DLIGHT9));

		light.Type = D3DLIGHT_DIRECTIONAL;

		Point3 nPosition = pLightComponent->GetFullPosition();
		light.Position.x = nPosition.x;
		light.Position.z = nPosition.z;
		light.Position.y = nPosition.y;

		const Point4& nColor = pLightComponent->GetColor();
		light.Diffuse.r = nColor.x;
		light.Diffuse.g = nColor.y;
		light.Diffuse.b = nColor.z;
		light.Diffuse.a = nColor.w;

		light.Direction = D3DXVECTOR3(0.0f, 0.0f, 1.0f);


		light.Range = pLightComponent->GetRange();

		m_pDevice9->SetLight(m_LightCount, &light);
		m_pDevice9->LightEnable(m_LightCount, TRUE);

		m_LightCount++;
	}

	void RenderWindowD3D9::PostRender(void)
	{
		m_pDevice9->EndScene();
	}

	void RenderWindowD3D9::Clear(void)
	{
		m_pDevice9->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 28, 128), 1.0f, 0);
	}

	void RenderWindowD3D9::Present(void)
	{
		m_pDevice9->Present(0, 0, 0, 0);
	}

	void RenderWindowD3D9::BindBufferData(RenderComponent* pRenderComponent, HardwareBufferData* pBufferData)
	{
		_lBufferBind::iterator it = m_lBufferBind.find(pRenderComponent);

		if (it != m_lBufferBind.end())
		{
			if (pBufferData && m_lBufferBind[pRenderComponent]->second != pBufferData)
			{
				RemoveBind(pRenderComponent);
			}
			else
			{
				return;
			}
		}

		// BIND
		RenderComponentD3D9* pRenderComponentD3D9 = new RenderComponentD3D9();

		// Vertex Buffer List and Declaration
		IDirect3DVertexDeclaration9* pDeclarationD3D9 = 0;
		IndexedArray< D3DVERTEXELEMENT9 > lVertexSemanticD3D9;

		const g_lVertexBuffer& lVertexBuffer = pBufferData->GetListVertexBuffer();
		for (int i = 0; i < lVertexBuffer.Size(); ++i)
		{
			// Vertex Buffer
			g_sVertexBufferD3D9* sVertexBufferD3D9 = new g_sVertexBufferD3D9();

			IDirect3DVertexBuffer9* pVertexBufferD3D9 = 0;
			m_pDevice9->CreateVertexBuffer(lVertexBuffer[i]->GetSizeBuffer(),
				0, 0, D3DPOOL_DEFAULT, &pVertexBufferD3D9, 0);

			void* pBuffer = 0;

			pVertexBufferD3D9->Lock(0, lVertexBuffer[i]->GetSizeBuffer(), &pBuffer, 0);
			memcpy(pBuffer, lVertexBuffer[i]->GetBuffer(), lVertexBuffer[i]->GetSizeBuffer());
			pVertexBufferD3D9->Unlock();

			sVertexBufferD3D9->m_pVertexBufferD3D9 = pVertexBufferD3D9;
			sVertexBufferD3D9->m_nOffset = lVertexBuffer[i]->GetOffsetBuffer();
			sVertexBufferD3D9->m_nVertexCount = lVertexBuffer[i]->GetVertexCount();

			pRenderComponentD3D9->AddVertexBufferD3D9(sVertexBufferD3D9);

			// Declaration
			const g_lVertexSemantic& lSemantic = lVertexBuffer[i]->GetListVertexSemantic();
			for (int n = 0, nOffset = 0; n < lSemantic.Size(); ++n)
			{
				D3DVERTEXELEMENT9 sVertexElement;
				sVertexElement.Stream = i;
				sVertexElement.Offset = nOffset;

				if (lSemantic[n] == VS_POSITION)
				{
					sVertexElement.Type = D3DDECLTYPE_FLOAT3;
					sVertexElement.Method = D3DDECLMETHOD_DEFAULT;
					sVertexElement.Usage = D3DDECLUSAGE_POSITION;
					sVertexElement.UsageIndex = 0;

					nOffset += 12;
				}
				else if (lSemantic[n] == VS_NORMAL)
				{
					sVertexElement.Type = D3DDECLTYPE_FLOAT3;
					sVertexElement.Method = D3DDECLMETHOD_DEFAULT;
					sVertexElement.Usage = D3DDECLUSAGE_NORMAL;
					sVertexElement.UsageIndex = 0;

					nOffset += 12;
				}
				else if (lSemantic[n] == VS_TEX)
				{
					sVertexElement.Type = D3DDECLTYPE_FLOAT2;
					sVertexElement.Method = D3DDECLMETHOD_DEFAULT;
					sVertexElement.Usage = D3DDECLUSAGE_TEXCOORD;
					sVertexElement.UsageIndex = 1;

					nOffset += 8;
				}

				lVertexSemanticD3D9.Add(sVertexElement);
			}
		}

		// Null
		D3DVERTEXELEMENT9 sVertexElementNull;
		sVertexElementNull.Stream = 0xff;
		sVertexElementNull.Offset = 0;
		sVertexElementNull.Type = D3DDECLTYPE_UNUSED;
		sVertexElementNull.Method = 0;
		sVertexElementNull.Usage = 0;
		sVertexElementNull.UsageIndex = 0;

		lVertexSemanticD3D9.Add(sVertexElementNull);
		m_pDevice9->CreateVertexDeclaration(lVertexSemanticD3D9.GetData(), &pDeclarationD3D9);
		pRenderComponentD3D9->SetDeclarationD3D9(pDeclarationD3D9);

		// IndexBuffer
		HardwareIndexBuffer* pIndexBuffer = pBufferData->GetIndexBuffer();
		g_sIndexBufferD3D9* sIndexBufferD3D9 = new g_sIndexBufferD3D9();

		if (pIndexBuffer)
		{
			IDirect3DIndexBuffer9* pIndexBufferD3D9 = 0;

			D3DFORMAT eFormatD3D9 = D3DFMT_INDEX32;
			sIndexBufferD3D9->m_nOffset = sizeof(unsigned long);
			if (pIndexBuffer->GetIndexType() == IT_16)
			{
				eFormatD3D9 = D3DFMT_INDEX16;
				sIndexBufferD3D9->m_nOffset = sizeof(unsigned short);
			}

			sIndexBufferD3D9->m_nIndexCount = pIndexBuffer->GetIndexCount();

			m_pDevice9->CreateIndexBuffer(pIndexBuffer->GetSizeIndex(), 0, eFormatD3D9, D3DPOOL_DEFAULT, &pIndexBufferD3D9, 0);

			void* pBuffer = 0;
			pIndexBufferD3D9->Lock(0, pIndexBuffer->GetSizeIndex(), &pBuffer, 0);
			memcpy(pBuffer, pIndexBuffer->GetBuffer(), pIndexBuffer->GetSizeIndex());
			pIndexBufferD3D9->Unlock();

			sIndexBufferD3D9->m_pIndexBufferD3D9 = pIndexBufferD3D9;

			pRenderComponentD3D9->SetIndexBufferD3D9(sIndexBufferD3D9);
		}


		_sBufferBindPair* sBufferBindPair = new _sBufferBindPair(pRenderComponentD3D9, pBufferData);

		m_lBufferBind.insert(_lBufferBind::value_type(pRenderComponent, sBufferBindPair));
	}

	void RenderWindowD3D9::RemoveBind(RenderComponent* pRenderComponent)
	{
		_lBufferBind::iterator it_BufferBind = m_lBufferBind.find(pRenderComponent);

		if (it_BufferBind != m_lBufferBind.end())
		{
			delete it_BufferBind->second->first;

			m_lBufferBind.erase(it_BufferBind);
		}
	}
}
