#include "DexRenderConnect.h"
#include "DexScene.h"
#include "DexSceneObject.h"
#include "DexRenderComponent.h"
#include "DexCameraComponent.h"

namespace Dex
{
	void IRenderConnect::SetFocus( CameraComponent* pCamera )
	{
		AddFocus( pCamera );

		m_sActiveFocus = CreateFocus( pCamera );
	}

	g_sFocusRenderConnect* IRenderConnect::GetFocus( void )
	{
		return m_sActiveFocus;
	}

	void IRenderConnect::AddFocus( CameraComponent* pCamera )
	{
		g_sFocusRenderConnect* sFocus = CreateFocus( pCamera );

		if ( !m_lFocus.Search( sFocus ) )
		{
			sFocus->m_pFocusScene->AddRenderConnect( this );

			const g_lSceneObject& lSceneObject = sFocus->m_pFocusScene->GetListSceneObject();
			for ( int i = 0; i < lSceneObject.Size(); ++i )
			{
				const g_lObjectComponent& lObjectComponent = lSceneObject[i]->GetListObjectComponent();

				for ( int n = 0; n < lObjectComponent.Size(); ++n )
				{
					if ( lObjectComponent[n]->GetType() == OCT_RENDER )
					{
						RenderComponent* pRenderComponent = static_cast< RenderComponent* >( lObjectComponent[n] );

						BindBufferData( pRenderComponent, pRenderComponent->GetBufferData() );
					}
				}
			}

			m_lFocus.Add( sFocus );
		}
	}

	void IRenderConnect::RemoveFocus( CameraComponent* pCamera )
	{
		g_sFocusRenderConnect* sFocus = CreateFocus( pCamera );

		if ( m_lFocus.Search( sFocus ) )
		{
			if ( m_sActiveFocus == sFocus )
			{
				m_sActiveFocus = 0;
			}

			sFocus->m_pFocusScene->RemoveRenderConnect( this );

			const g_lSceneObject& lSceneObject = sFocus->m_pFocusScene->GetListSceneObject();
			for ( int i = 0; i < lSceneObject.Size(); ++i )
			{
				const g_lObjectComponent& lObjectComponent = lSceneObject[i]->GetListObjectComponent();

				for ( int n = 0; n < lObjectComponent.Size(); ++n )
				{
					if ( lObjectComponent[n]->GetType() == OCT_RENDER )
					{
						RenderComponent* pRenderComponent = static_cast< RenderComponent* >( lObjectComponent[n] );

						RemoveBind( pRenderComponent );
					}
				}
			}

			m_lFocus.Remove( sFocus );
		}
	}

	g_sFocusRenderConnect* IRenderConnect::CreateFocus( CameraComponent* pCamera )
	{
		g_sFocusRenderConnect* sFocusRenderConnect = new g_sFocusRenderConnect();

		sFocusRenderConnect->m_pFocusCameraComponent = pCamera;
		sFocusRenderConnect->m_pFocusScene = pCamera->GetPatentObject()->GetScene();

		return sFocusRenderConnect;
	}
}