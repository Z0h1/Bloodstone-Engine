#pragma once

#include "DexCoreComponent.h"
#include "DexMeshSerializer.h"

namespace Dex
{
	class D_EXPORT RenderComponent : public CoreComponent
	{
	public:
		RenderComponent(const string& cName, SceneObject* pParent, const PrimitiveType& eType);
		virtual ~RenderComponent(void);

		void Load(const string& cResource);

		const PrimitiveType GetPrimitiveType(void);

		HardwareBufferData* GetBufferData(void);

		bool IsActive(void);
		void SetActive(bool bActive);

	private:
		bool						m_bActive;

		PrimitiveType				m_ePrimitiveType;
	};
}