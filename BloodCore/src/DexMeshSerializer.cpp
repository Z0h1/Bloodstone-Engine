#include <DexMeshSerializer.h>
#include <DexHardwareBufferData.h>
#include <DexHardwareIndexBuffer.h>
#include <DexHardwareVertexBuffer.h>

namespace Dex
{
	MeshSerializer::MeshSerializer(const String& c_name, OFStream* logger, bool fw)
		: Serializer(c_name, logger, fw)
	{
	}

	MeshSerializer::~MeshSerializer()
	{
	}

	void MeshSerializer::ImportMesh( void )
	{ 
		ReadHeader( &m_sMeshStruct );

		int nVersion = 0;
		ReadInt( &nVersion );

		if ( nVersion != MESH_VERSION_SERIALIZER )
		{
			//DrawLine( "MeshSerializer: Версии не совпадают!", EZ_ERROR );
			return;
		}

		for ( ; ; )
		{
			ReadHeader( &m_sMeshStruct );

			if ( m_sMeshStruct == MESH_GEOMETRY )
			{
				ReadGeometry();
			}
			else if ( m_sMeshStruct == MESH_GEOMETRY_END )
			{
				break;
			}
			else
			{
				break;
			}
		}
	}

	void MeshSerializer::ReadGeometry( void )
	{
		bool bUseIndex;
		ReadBool( &bUseIndex );

		if ( bUseIndex )
		{
			ReadHeader( &m_sMeshStruct );

			IndexType eIndexType;
			unsigned int nIndexCount = 0;

			ReadInt( &eIndexType );
			ReadUInt( &nIndexCount );

			HardwareIndexBuffer* pIndexBuffer = m_pBufferData->CreateIndexBuffer( nIndexCount, eIndexType );

			ReadPtr( pIndexBuffer->GetBuffer(), pIndexBuffer->GetSizeIndex() );
		}

		for ( ; ; )
		{
			ReadHeader( &m_sMeshStruct );

			if ( m_sMeshStruct == MESH_GEOMETRY_VERTEX )
			{
				ReadVertex();
			}
			else if ( m_sMeshStruct == MESH_GEOMETRY_VERTEX_END )
			{
				break;
			}
			else
			{
				break;
			}
		}
	}

	void MeshSerializer::ReadVertex( void )
	{
		unsigned int nVertexCount = 0;

		ReadUInt( &nVertexCount );
		HardwareVertexBuffer* pVertexBuffer = m_pBufferData->CreateVertexBuffer( nVertexCount );

		for ( ; ; )
		{
			ReadHeader( &m_sMeshStruct );

			if ( m_sMeshStruct == MESH_GEOMETRY_VERTEX_ELEMENT )
			{
				VertexSemantics eVertexSemantics;

				ReadInt( &eVertexSemantics );
				pVertexBuffer->AddVertexSemantic( eVertexSemantics );
			}
			else if ( m_sMeshStruct == MESH_GEOMETRY_VERTEX_ELEMENT_END )
			{
				break;
			}
			else
			{
				break;
			}
		}

		ReadPtr( pVertexBuffer->GetBuffer(), pVertexBuffer->GetSizeBuffer() );		
	}
}