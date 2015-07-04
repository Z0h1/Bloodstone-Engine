#include <DexSceneObject.h>
#include <DexObjectComponent.h>
#include <DexRenderComponent.h>
#include <DexCameraComponent.h>
#include <DexScene.h>

namespace Dex
{
	SceneObject::SceneObject( const String& name, Scene* scene )
		: ObjectLocation()
	{
		m_Name = name;
		m_pScene = scene;

		m_nId = m_pScene->GetNewId();
	}
	SceneObject::~SceneObject( void )
	{
	}

	// Name and Id
	int SceneObject::GetId( void )
	{
		return m_nId;
	}
	const String& SceneObject::GetName( void )
	{
		return m_Name;
	}
	Scene* SceneObject::GetScene( void )
	{
		return m_pScene;
	}

	void SceneObject::AddComponent( ObjectComponent* pComponent )
	{
		if ( !m_lObjectComponent.Search( pComponent ) )
		{
			switch ( pComponent->GetType() )
			{
			case OCT_RENDER:
				{
					RenderComponent* pRenderComponent = static_cast< RenderComponent* >( pComponent );

					const g_lRenderConnect& lRenderConnect = m_pScene->GetListRenderConnect();
					for ( int i = 0; i < lRenderConnect.Size(); ++i )
					{
						lRenderConnect[i]->BindBufferData( pRenderComponent, pRenderComponent->GetBufferData() );
					}
				}
				break;
			}

			m_lObjectComponent.Add( pComponent );
		}
	}

	void SceneObject::RemoveComponent( ObjectComponent* pComponent )
	{
		if ( m_lObjectComponent.Search( pComponent ) )
		{
			switch ( pComponent->GetType() )
			{
			case OCT_RENDER:
				{
					RenderComponent* pRenderComponent = static_cast< RenderComponent* >( pComponent );

					const g_lRenderConnect& lRenderConnect = m_pScene->GetListRenderConnect();
					for ( int i = 0; i < lRenderConnect.Size(); ++i )
					{
						lRenderConnect[i]->RemoveBind( pRenderComponent );
					}
				}
				break;
			case OCT_CAMERA:
				{
					CameraComponent* pCameraComponent = static_cast< CameraComponent* >( pComponent );

					const g_lRenderConnect& lRenderConnect = m_pScene->GetListRenderConnect();
					for ( int i = 0; i < lRenderConnect.Size(); ++i )
					{
						lRenderConnect[i]->RemoveFocus( pCameraComponent );
					}
				}
				break;
			}

			m_lObjectComponent.Remove( pComponent );
		}
	}

	const g_lObjectComponent& SceneObject::GetListObjectComponent( void )
	{
		return m_lObjectComponent;
	}
}