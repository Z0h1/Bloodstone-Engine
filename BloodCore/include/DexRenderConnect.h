//#pragma once
//
//#include "DexPreCompletion.h"
//#include "DexCommon.h"
//
//namespace Dex
//{
//	typedef struct _sFocusRenderConnect
//	{
//		CameraComponent*		m_pFocusCameraComponent;
//		Scene*					m_pFocusScene;
//
//	} g_sFocusRenderConnect;
//
//	class D_EXPORT IRenderConnect
//	{
//	public:
//		virtual void CalculateMatrix( RenderComponent* pRenderComponent ) = 0;
//		virtual void SetMatrixIdentity( void ) = 0;
//		virtual void SetViewMatrix( CameraComponent* pCamera ) = 0;
//		virtual void SetWorldMatrix( const Point3& position, const Point3& rotation, const Point3& scale ) = 0;
//
//		virtual bool IsLostControl( void ) = 0;
//		virtual bool PreRender( void ) = 0;
//		virtual void RenderObject( RenderComponent* pRenderComponent ) = 0;
//		virtual void SetLight( LightComponent* pLightComponent ) = 0;
//		virtual void PostRender( void ) = 0;
//		virtual void Clear( void ) = 0;
//		virtual void Present( void ) = 0;
//
//		virtual void BindBufferData( RenderComponent* pRenderComponent, HardwareBufferData* pBufferData ) = 0;
//		virtual void RemoveBind( RenderComponent* pRenderComponent ) = 0;
//
//		void SetFocus( CameraComponent* pCamera );
//
//		g_sFocusRenderConnect* GetFocus( void );
//
//		void AddFocus( CameraComponent* pCamera );
//		void RemoveFocus( CameraComponent* pCamera );
//
//	private:
//		g_sFocusRenderConnect* CreateFocus( CameraComponent* pCamera );
//
//	private:
//		g_sFocusRenderConnect*			m_sActiveFocus;
//
//		IndexedArray< g_sFocusRenderConnect* >	m_lFocus;
//	};
//}