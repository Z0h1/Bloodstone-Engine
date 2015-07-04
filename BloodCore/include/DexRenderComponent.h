#pragma once

#include <DexObjectComponent.h>
#include <DexMeshSerializer.h>

namespace Dex
{
	class D_EXPORT RenderComponent : public ObjectComponent, public MeshSerializer
	{
	public:
		RenderComponent( const String& cName, SceneObject* pParent, const PrimitiveType& eType );
		~RenderComponent( void );

		void Load( const String& cResource );

		const PrimitiveType& GetPrimitiveType( void );

		HardwareBufferData* GetBufferData( void );

		bool IsActive( void );
		void SetActive( bool bActive );

	private:
		bool						m_bActive;

		PrimitiveType				m_ePrimitiveType;
	};
}