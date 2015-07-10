#include "DexCoreComponent.h"
#include "DexSceneObject.h"
#include "DexCoreObject.h"

namespace Dex
{
	CoreComponent::CoreComponent(const string& c_name, SceneObject* obj, const ObjectComponentType e_type)
		: CoreObject(c_name, obj->GetOutFileStream(), WorkPriority::WP_COMPONENT)
	{
		m_pObject = obj;
		m_eType = e_type;
	}

	CoreComponent::~CoreComponent()
	{

	}

	SceneObject* CoreComponent::GetSceneObject()
	{
		return m_pObject;
	}

	const ObjectComponentType CoreComponent::GetType(void)
	{
		return m_eType;
	}
}