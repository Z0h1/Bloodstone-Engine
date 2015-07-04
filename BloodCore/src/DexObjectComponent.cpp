#include "DexObjectComponent.h"
#include "DexSceneObject.h"

namespace Dex
{
	ObjectComponent::ObjectComponent( const string& cName, SceneObject* pParent, const ObjectComponentType& type )
		: ObjectLocation( pParent )
	{
		m_cName = cName;
		m_eType = type;
		m_pParentObject = pParent;
	}

	ObjectComponent::~ObjectComponent( void )
	{
	}

	const ObjectComponentType& ObjectComponent::GetType( void ) const
	{
		return m_eType;
	}

	const string& ObjectComponent::GetName( void ) const
	{
		return m_cName;
	}

	SceneObject* ObjectComponent::GetPatentObject( void )
	{
		return m_pParentObject; 
	}
}