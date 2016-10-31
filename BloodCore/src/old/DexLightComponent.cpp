#include "DexLightComponent.h"

namespace DEX
{
	LightComponent::LightComponent( const string& cName, SceneObject* pParent,
		const _4point& nColor, const _point& nRange )
		: CoreComponent( cName, pParent, OCT_LIGHT )
	{
		m_nColor = nColor;
		m_nRange = nRange;
	}

	LightComponent::~LightComponent( void )
	{
	}

	void LightComponent::SetColor( const _4point& nColor )
	{
		m_nColor = nColor;
	}

	const _4point& LightComponent::GetColor( void )
	{
		return m_nColor;
	}

	const _point& LightComponent::GetRange( void )
	{
		return m_nRange;
	}
}