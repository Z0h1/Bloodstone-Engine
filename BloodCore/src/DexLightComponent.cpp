#include <DexLightComponent.h>

namespace Dex
{
	LightComponent::LightComponent( const String& cName, SceneObject* pParent,
		const Point4& nColor, const Point& nRange )
		: ObjectComponent( cName, pParent, OCT_LIGHT )
	{
		m_nColor = nColor;
		m_nRange = nRange;
	}

	LightComponent::~LightComponent( void )
	{
	}

	void LightComponent::SetColor( const Point4& nColor )
	{
		m_nColor = nColor;
	}

	const Point4& LightComponent::GetColor( void )
	{
		return m_nColor;
	}

	const Point& LightComponent::GetRange( void )
	{
		return m_nRange;
	}
}