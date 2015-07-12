#pragma once

#include "DexCoreComponent.h"

namespace Dex
{
	class D_EXPORT RenderComponent : public CoreComponent
	{
	public:
		RenderComponent(const string& cName, SceneObject* pParent);
		virtual ~RenderComponent(void);

		void LoadGeometry(CoreFile* mesh);

		PrimitiveType GetPrimitiveType() const { return m_ePrimitiveType; };
		GeometryFile* GetGeometry() const { return m_pGeometry; };

		bool IsActive() const { return m_bActive; };
		void SetActive(bool bActive) { m_bActive = bActive; };
		void SetPrimitiveType(PrimitiveType type) { m_ePrimitiveType = type; };

	private:
		bool				m_bActive;
		PrimitiveType		m_ePrimitiveType;
		GeometryFile*		m_pGeometry;
	};
}