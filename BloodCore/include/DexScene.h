#pragma once

#include "DexPreCompletion.h"
#include "DexCommon.h"
#include "DexRenderConnect.h"

namespace Dex
{
	typedef IndexedArray< SceneObject* >	g_lSceneObject;
	typedef	IndexedArray< IRenderConnect* >	g_lRenderConnect;

	class D_EXPORT Scene
	{
	public:
		Scene( const string& cName );
		~Scene( void );

		int GetNewId( void );

		SceneObject* CreateObject( const string& name );
		SceneObject* GetObject( int nIndex );

		const g_lSceneObject& GetListSceneObject( void );
		const string& GetName( void );

		void AddRenderConnect( IRenderConnect* pConnect );
		void RemoveRenderConnect( IRenderConnect* pConnect );
		const g_lRenderConnect& GetListRenderConnect( void );

	private:
		g_lSceneObject		m_lSceneObject;
		g_lRenderConnect	m_lRenderConnect;

		string				m_cName;
	};
}