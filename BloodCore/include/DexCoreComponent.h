#pragma once

#include "DexPreCompletion.h"
#include "DexCoreObject.h"

namespace Dex
{
	class D_EXPORT CoreComponent : public CoreObject
	{
	public:
		CoreComponent(const string& c_name, SceneObject* obj, const ObjectComponentType e_type);
		virtual ~CoreComponent();

		SceneObject* GetSceneObject();
		const ObjectComponentType GetType(void);

	protected:
		SceneObject*			m_pObject;
		ObjectComponentType		m_eType;
	};
}