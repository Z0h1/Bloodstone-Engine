#include "DexGeometryFile.h"
#include "DexIndexBuffer.h"
#include "DexVertexBuffer.h"

namespace Dex
{
	GeometryFile::GeometryFile(ofstream* logger, Folder* pParent, const string& cPath, const string& cName)
		: CoreFile(logger, pParent, FileFormat::FF_DEXG, cPath, cName), Serializer(cPath)
	{	
	}

	void GeometryFile::ImportMesh()
	{
		if (Open(OPEN_MODE_READ | OPEN_MODE_BINARY)) {
			DrawLine("ImportMesh: Не возможно открыть файл " + m_cPath, MT_ERROR);
		}

		GeometryStruct gs;

		int nVersion = 0;
		ReadInt(&nVersion);

		if (nVersion != GEOMETRY_VERSION_SERIALIZER)
		{
			DrawLine("ImportMesh: Версии не совпадают!", MT_ERROR);
			Close();
			return;
		}

		bool bUseIndex;
		ReadBool(&bUseIndex);
		if (bUseIndex)
		{
			IndexType eIndexType;
			UInt32 nIndexCount = 0;

			ReadInt(&eIndexType);
			ReadUInt(&nIndexCount);

			m_pIndexBuffer = new IndexBuffer(nIndexCount, eIndexType);

			ReadPtr(m_pIndexBuffer->GetBuffer(), m_pIndexBuffer->GetSizeIndex());
		}

		ReadHeader(&gs);
		while (gs != GEOMETRY_VERTEX_END)
		{
			UInt32 nVertexCount = 0;

			ReadUInt(&nVertexCount);

			VertexBuffer* pVertexBuffer = new VertexBuffer(nVertexCount);
			m_lVertexBuffer.push_back(pVertexBuffer);

			ReadHeader(&gs);
			while (gs != GEOMETRY_VERTEX_ELEMENT_END)
			{
				VertexLayout eVertexLayout;

				ReadInt(&eVertexLayout);
				pVertexBuffer->AddVertexSemantic(eVertexLayout);

				ReadHeader(&gs);
			}

			ReadPtr(pVertexBuffer->GetBuffer(), pVertexBuffer->GetSizeBuffer());

			ReadHeader(&gs);
		}

		Close();
	}

	void GeometryFile::ReadGeometry(void)
	{
		/*bool bUseIndex;
		ReadBool(&bUseIndex);

		if (bUseIndex)
		{
			ReadHeader(&gs);

			IndexType eIndexType;
			unsigned int nIndexCount = 0;

			ReadInt(&eIndexType);
			ReadUInt(&nIndexCount);

			HardwareIndexBuffer* pIndexBuffer = m_pBufferData->CreateIndexBuffer(nIndexCount, eIndexType);

			ReadPtr(pIndexBuffer->GetBuffer(), pIndexBuffer->GetSizeIndex());
		}

		for (;; )
		{
			ReadHeader(&gs);

			if (gs == MESH_GEOMETRY_VERTEX)
			{
				ReadVertex();
			}
			else if (gs == MESH_GEOMETRY_VERTEX_END)
			{
				break;
			}
			else
			{
				break;
			}
		}*/
	}

	void GeometryFile::ReadVertex(void)
	{
		/*unsigned int nVertexCount = 0;

		ReadUInt(&nVertexCount);
		HardwareVertexBuffer* pVertexBuffer = m_pBufferData->CreateVertexBuffer(nVertexCount);

		for (;; )
		{
			ReadHeader(&gs);

			if (gs == MESH_GEOMETRY_VERTEX_ELEMENT)
			{
				VertexSemantics eVertexSemantics;

				ReadInt(&eVertexSemantics);
				pVertexBuffer->AddVertexSemantic(eVertexSemantics);
			}
			else if (gs == MESH_GEOMETRY_VERTEX_ELEMENT_END)
			{
				break;
			}
			else
			{
				break;
			}
		}

		ReadPtr(pVertexBuffer->GetBuffer(), pVertexBuffer->GetSizeBuffer());*/
	}
}