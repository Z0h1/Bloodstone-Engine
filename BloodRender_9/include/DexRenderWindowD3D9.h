#pragma once

#include "DexPreCompletionD3D9.h"
#include "DexRenderWindow.h"
#include "DexRenderConnect.h"

namespace Dex
{
	class D_EXPORT_D3D9 RenderWindowD3D9 : public IRenderWindow, public IRenderConnect
	{
	public:
		RenderWindowD3D9(ofstream* logger, UINT adapter, D3DDEVTYPE type, IDirect3D9* d3d9);
		~RenderWindowD3D9(void);

		bool Create(const _lParametor & config, HWND h);

	public:
		// connect
		void CalculateMatrix(RenderComponent* pRenderComponent);
		void SetMatrixIdentity(void);
		void SetViewMatrix(CameraComponent* pCamera);
		void SetWorldMatrix(const Point3& position, const Point3& rotation, const Point3& scale);

		bool IsLostControl(void);
		bool PreRender(void);
		void RenderObject(RenderComponent* pRenderComponent);
		void SetLight(LightComponent* pLightComponent);
		void PostRender(void);
		void Clear(void);
		void Present(void);

		void BindBufferData(RenderComponent* pRenderComponent, HardwareBufferData* pBufferData);
		void RemoveBind(RenderComponent* pRenderComponent);

	private:
		typedef pair< RenderComponentD3D9*, HardwareBufferData* > _sBufferBindPair;
		typedef map< RenderComponent*, _sBufferBindPair* >	_lBufferBind;
		_lBufferBind				m_lBufferBind;

		int							m_LightCount;

		// DirectX Setting
		D3DXMATRIX					m_WorldMatrix;
		D3DXMATRIX					m_ViewMatrix;
		D3DXMATRIX					m_ProjectionMatrix;

		IDirect3D9*					m_pD3D9;
		IDirect3DDevice9*			m_pDevice9;

		UINT						m_nAdapter;
		D3DDEVTYPE					m_DeviceType;

		D3DPRESENT_PARAMETERS		m_d3d_pp;
	};
}