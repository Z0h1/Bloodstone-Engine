#pragma once

#include <DexPreCompletion.h>
#include <DexCommon.h>
#include <DexObjectLocation.h>

namespace Dex
{
	class D_EXPORT ObjectComponent : public ObjectLocation
	{
	public:
		ObjectComponent( const String& cName, SceneObject* pParent, const ObjectComponentType& type );
		virtual ~ObjectComponent();

		const ObjectComponentType& GetType( void ) const;
		const String& GetName( void ) const;
		SceneObject* GetPatentObject( void );

	protected:
		String					m_cName;
		ObjectComponentType		m_eType;
		SceneObject*			m_pParentObject;
	};
}