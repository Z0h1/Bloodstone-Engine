#pragma once

#include "DexCoreComponent.h"
#include "DexRenderComponent.h"

namespace Dex
{
	#define GEOMETRY_VERSION_SERIALIZER 3

	enum GeometryStruct
	{
		// int ( version visual object )
		// bool ( bUseIndex )
		// if ( bUseIndex )
		// {
		//		int ( enum IndexType )
		//		_intun ( Index count )
		//		Ptr ( buffer )
		// }
		// _intun count byte vs shader
		// Shader byte code
		// _intun count byte ps shader
		// Shader byte code
		GEOMETRY_VERTEX_BEGIN,
		// _intun ( Vertex count )
		GEOMETRY_VERTEX_ELEMENT_BEGIN,
		// int ( enum VertexSemantics )
		GEOMETRY_VERTEX_ELEMENT_END,
		// Ptr ( buffer )
		GEOMETRY_VERTEX_END
	};

	typedef vector<VertexLayout>		_vertexLayouts;

	class D_EXPORT RenderComponent : public CoreComponent
	{
	public:
		RenderComponent(const string& cName, SceneObject* pParent);
		virtual ~RenderComponent(void);

		void LoadGeometryFromFile(CoreFile* mesh);
		void LoadGeometry();

		PrimitiveType	GetPrimitiveType()		const { return m_ePrimitiveType; };
		File*			GetGeometryFile()		const { return m_pGeometryFile; };
		bool			IsActive()				const { return m_bActive; };
		bool			IsGeometryLoaded()		const { return m_bGeometryLoaded; };
		void			SetActive(bool bActive)					{ m_bActive = bActive; };
		void			SetPrimitiveType(PrimitiveType type)	{ m_ePrimitiveType = type; };

		virtual void LoadVertexShader(void* shader_code_ptr, _intun count_byte) = 0;
		virtual void LoadVertexLayout(_vertexLayouts& vertexLayouts, void* shader_code_ptr, _intun count_byte) = 0;
		virtual void LoadVertexBuffer(void* buffer, _intun offset, _intun size) = 0;
		virtual void LoadPixelShader(void* shader_code_ptr, _intun count_byte) = 0;
		virtual void LoadIndexBuffer(void* buffer, _intun offset, _intun size) = 0;

	protected:
		bool				m_bActive;
		bool				m_bGeometryLoaded;
		PrimitiveType		m_ePrimitiveType;
		File*				m_pGeometryFile;
	};
}