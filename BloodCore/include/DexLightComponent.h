#pragma once

#include "DexCoreComponent.h"
#include "DexMath.h"

namespace Dex
{
	class D_EXPORT LightComponent : public CoreComponent
	{
	public:
		LightComponent(const string& cName, SceneObject* pParent, const _4point& nColor, const _point& nRange);
		~LightComponent(void);

		void SetColor(const _4point& nColor);

		const _4point& GetColor(void);
		const _point& GetRange(void);

	private:
		_4point				m_nColor;
		_point				m_nRange;
	};
}