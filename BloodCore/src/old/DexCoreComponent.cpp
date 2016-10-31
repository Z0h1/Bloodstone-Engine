#include "DexCoreComponent.h"
#include "DexSceneObject.h"
#include "DexCoreObject.h"

namespace DEX
{
	CoreComponent::CoreComponent(const string& c_name, SceneObject* obj, const ObjectComponentType e_type)
		: CoreObject(c_name, obj->GetOutFileStream(), WorkPriority::WP_COMPONENT)
	{
		m_pObject = obj;
		m_eType = e_type;

		if (m_pObject) {
			m_pObject->AddComponent(this);
		}
	}

	CoreComponent::~CoreComponent()
	{
		if (m_pObject) {
			m_pObject->RemoveComponent(this);
		}
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