#include "DexRenderComponent.h"
#include "DexHardwareBufferData.h"
#include "DexScene.h"
#include "DexSceneObject.h"
#include "DexGeometryFile.h"

namespace Dex
{
	RenderComponent::RenderComponent(const string& cName, SceneObject* pParent)
		: CoreComponent(cName, pParent, OCT_RENDER)
	{
		m_ePrimitiveType = PrimitiveType::PT_NULL;
		m_bActive = false;
		m_pGeometry = nullptr;
	}

	RenderComponent::~RenderComponent(void)
	{
	}

	void RenderComponent::LoadGeometry(CoreFile* mesh)
	{
		if (mesh->GetFormat() == FileFormat::FF_DEXG) {
			m_pGeometry = (GeometryFile*)mesh;

			m_pGeometry->ImportMesh();
		}

		//Scene* pScene = m_pObject->GetScene();

		//_lRenderConnect lRenderConnect;
		//pScene->GetRenderConnects(lRenderConnect);
		//for (auto n : lRenderConnect)
		//{
		//	//n->BindBufferData(this, m_pBufferData);
		//}
	}
}