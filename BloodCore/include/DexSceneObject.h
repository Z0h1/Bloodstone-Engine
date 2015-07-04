#pragma once

#include <DexPreCompletion.h>
#include <DexCommon.h>
#include <DexObjectLocation.h>

namespace Dex
{
	typedef IndexedArray< ObjectComponent* > g_lObjectComponent;

	class D_EXPORT SceneObject : public ObjectLocation
	{
	public:
		SceneObject( const String& name, Scene* pParent );
		~SceneObject( void );

		// Name and Id
		int GetId( void );
		const String& GetName( void );
		Scene* GetScene( void );

		void AddComponent( ObjectComponent* pComponent );
		void RemoveComponent( ObjectComponent* pComponent );

		const g_lObjectComponent& GetListObjectComponent( void );

	protected:
		int					m_nId;
		String				m_Name;
		Scene*				m_pScene;

		g_lObjectComponent	m_lObjectComponent;
	};
}