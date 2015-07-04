#include "DexScene.h"
#include "DexSceneObject.h"

namespace Dex
{
	Scene::Scene( const string& cName )
	{
		m_cName = cName;
	}

	Scene::~Scene( void )
	{
	}

	int Scene::GetNewId( void )
	{
		return m_lSceneObject.Size();
	}

	SceneObject* Scene::CreateObject( const string& cName )
	{
		SceneObject* pObject = 0;

		pObject = new SceneObject( cName, this );

		m_lSceneObject.Add( pObject );

		return pObject;
	}
	SceneObject* Scene::GetObject( int nIndex )
	{
		return m_lSceneObject[nIndex];
	}

	const g_lSceneObject& Scene::GetListSceneObject( void )
	{
		return m_lSceneObject;
	}

	const string& Scene::GetName( void )
	{
		return m_cName;
	}

	void Scene::AddRenderConnect( IRenderConnect* pConnect )
	{
		m_lRenderConnect.Add( pConnect );
	}
	void Scene::RemoveRenderConnect( IRenderConnect* pConnect )
	{
		m_lRenderConnect.Remove( pConnect );
	}
	const g_lRenderConnect& Scene::GetListRenderConnect( void )
	{
		return m_lRenderConnect;
	}
}