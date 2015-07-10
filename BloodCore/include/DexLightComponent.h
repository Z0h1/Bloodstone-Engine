#pragma once

#include "DexCoreComponent.h"
#include "DexMath.h"

namespace Dex
{
	class D_EXPORT LightComponent : public CoreComponent
	{
	public:
		LightComponent(const string& cName, SceneObject* pParent, const Point4& nColor, const Point& nRange);
		~LightComponent(void);

		void SetColor(const Point4& nColor);

		const Point4& GetColor(void);
		const Point& GetRange(void);

	private:
		Point4				m_nColor;
		Point				m_nRange;
	};
}