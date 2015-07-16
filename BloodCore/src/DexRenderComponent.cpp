#include "DexRenderComponent.h"
#include "DexHardwareBufferData.h"
#include "DexScene.h"
#include "DexSceneObject.h"
#include "DexFile.h"

namespace Dex
{
	RenderComponent::RenderComponent(const string& cName, SceneObject* pParent)
		: CoreComponent(cName, pParent, OCT_RENDER)
	{
		m_ePrimitiveType = PrimitiveType::PT_NULL;
		m_bActive = true;
		m_bGeometryLoaded = false;
		m_pGeometryFile = nullptr;
	}

	RenderComponent::~RenderComponent(void)
	{
	}

	void RenderComponent::LoadGeometryFromFile(CoreFile* mesh)
	{
		m_pGeometryFile = dynamic_cast<File*>(mesh);

		if (!m_pGeometryFile) {
			DrawLine("LoadGeometry: Неверный формат файла " + mesh->GetName(), MT_ERROR);
			return;
		}

		LoadGeometry();
	}

	void RenderComponent::LoadGeometry()
	{
		m_bGeometryLoaded = false;

		if (!m_pGeometryFile->Open(OPEN_MODE_READ | OPEN_MODE_BINARY)) {
			DrawLine("LoadGeometry: Не возможно открыть файл " + m_pGeometryFile->GetName(), MT_ERROR);
			return;
		}

		int nVersion = 0;
		m_pGeometryFile->ReadInt(&nVersion);

		if (nVersion != GEOMETRY_VERSION_SERIALIZER)
		{
			DrawLine("LoadGeometry: Версии не совпадают!", MT_ERROR);
			m_pGeometryFile->Close();
			return;
		}

		GeometryStruct gs;

		bool bUseIndex;
		m_pGeometryFile->ReadBool(&bUseIndex);
		if (bUseIndex)
		{
			IndexType eIndexType = IndexType::IT_16;
			_intun nIndexCount = 0;

			m_pGeometryFile->ReadInt(&eIndexType);
			m_pGeometryFile->ReadUInt(&nIndexCount);

			_intun offset = sizeof(unsigned long);
			if (eIndexType == IT_16)
			{
				offset = sizeof(unsigned short);
			}

			void* indexBufferPtr = malloc(nIndexCount * offset);
			m_pGeometryFile->ReadPtr(indexBufferPtr, nIndexCount * offset);
			LoadIndexBuffer(indexBufferPtr, offset, nIndexCount);
		}

		// VS
		_intun byte_count = 0;
		m_pGeometryFile->ReadUInt(&byte_count);

		vector<unsigned char> shader_data(byte_count);
		m_pGeometryFile->ReadPtr(shader_data.data(), byte_count);

		LoadVertexShader(shader_data.data(), byte_count);

		_intun offset = 0;
		_vertexLayouts vertexLayous;

		m_pGeometryFile->ReadHeader(&gs);
		while (gs != GEOMETRY_VERTEX_ELEMENT_END)
		{
			VertexLayout eVertexLayout;

			m_pGeometryFile->ReadInt(&eVertexLayout);
			vertexLayous.push_back(eVertexLayout);

			switch (eVertexLayout)
			{
			case Dex::VL_POSITION:
				VL_OFFSET_POSITION(offset);
				break;
			case Dex::VL_NORMAL:
				VL_OFFSET_NORMAL(offset);
				break;
			case Dex::VL_TEXTURE:
				VL_OFFSET_TEXTURE(offset);
				break;
			}

			m_pGeometryFile->ReadHeader(&gs);
		}

		LoadVertexLayout(vertexLayous, shader_data.data(), byte_count);

		_intun nVertexCount = 0;
		m_pGeometryFile->ReadUInt(&nVertexCount);
		void* vertexBuffer = malloc(nVertexCount * offset);
		m_pGeometryFile->ReadPtr(vertexBuffer, nVertexCount * offset);
		LoadVertexBuffer(vertexBuffer, offset, nVertexCount);

		// PS
		byte_count = 0;
		m_pGeometryFile->ReadUInt(&byte_count);

		shader_data.clear();
		shader_data.resize(byte_count);

		m_pGeometryFile->ReadPtr(shader_data.data(), byte_count);

		LoadPixelShader(shader_data.data(), byte_count);

		m_pGeometryFile->Close();
		m_bGeometryLoaded = true;
		m_bActive = true;
	}
}