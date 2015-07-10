#include "DexRenderComponent.h"
#include "DexHardwareBufferData.h"
#include "DexScene.h"
#include "DexSceneObject.h"

namespace Dex
{
	RenderComponent::RenderComponent(const string& cName, SceneObject* pParent, const PrimitiveType& eType)
		: CoreComponent(cName, pParent, OCT_RENDER), MeshSerializer(cName, pParent->GetOutFileStream()) // TODO tharde
	{
		m_pBufferData = new HardwareBufferData();

		m_ePrimitiveType = eType;
		m_bActive = true;
	}

	RenderComponent::~RenderComponent(void)
	{
		delete m_pBufferData;
	}

	void RenderComponent::Load(const string& cResource)
	{
		SetResource(cResource);

		ImportMesh();

		Scene* pScene = m_pObject->GetScene();

		_lRenderConnect lRenderConnect;
		pScene->GetRenderConnects(lRenderConnect);
		for (auto n : lRenderConnect)
		{
			n->BindBufferData(this, m_pBufferData);
		}
	}

	const PrimitiveType RenderComponent::GetPrimitiveType(void)
	{
		return m_ePrimitiveType;
	}

	HardwareBufferData* RenderComponent::GetBufferData(void)
	{
		return m_pBufferData;
	}

	bool RenderComponent::IsActive(void)
	{
		return m_bActive;
	}

	void RenderComponent::SetActive(bool bActive)
	{
		m_bActive = bActive;
	}
}