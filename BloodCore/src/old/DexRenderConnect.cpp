//#include "DexRenderConnect.h"
//#include "DexScene.h"
//#include "DexSceneObject.h"
//#include "DexRenderComponent.h"
//#include "DexCameraComponent.h"
//
//namespace Dex
//{
//	void IRenderConnect::SetFocus(CameraComponent* pCamera)
//	{
//		AddFocus(pCamera);
//
//		m_sActiveFocus = CreateFocus(pCamera);
//	}
//
//	g_sFocusRenderConnect* IRenderConnect::GetFocus(void)
//	{
//		return m_sActiveFocus;
//	}
//
//	void IRenderConnect::AddFocus(CameraComponent* pCamera)
//	{
//		g_sFocusRenderConnect* sFocus = CreateFocus(pCamera);
//
//		if (!m_lFocus.Search(sFocus))
//		{
//			sFocus->m_pFocusScene->AddRenderConnect(this);
//
//			_lSceneObject lSceneObject;
//			sFocus->m_pFocusScene->GetSceneObjects(lSceneObject);
//			for (auto n : lSceneObject)
//			{
//				_lCoreComponent lObjectComponent;
//				n->GetObjectComponents(lObjectComponent);
//				for (auto i : lObjectComponent)
//				{
//					if (i->GetType() == OCT_RENDER)
//					{
//						RenderComponent* pRenderComponent = (RenderComponent*)i;
//
//						BindBufferData(pRenderComponent, pRenderComponent->GetBufferData());
//					}
//				}
//			}
//
//			m_lFocus.Add(sFocus);
//		}
//	}
//
//	void IRenderConnect::RemoveFocus(CameraComponent* pCamera)
//	{
//		g_sFocusRenderConnect* sFocus = CreateFocus(pCamera);
//
//		if (m_lFocus.Search(sFocus))
//		{
//			if (m_sActiveFocus == sFocus)
//			{
//				m_sActiveFocus = 0;
//			}
//
//			sFocus->m_pFocusScene->RemoveRenderConnect(this);
//
//			_lSceneObject lSceneObject;
//			sFocus->m_pFocusScene->GetSceneObjects(lSceneObject);
//			for (auto n : lSceneObject)
//			{
//				_lCoreComponent lObjectComponent;
//				n->GetObjectComponents(lObjectComponent);
//				for (auto i : lObjectComponent)
//				{
//					if (i->GetType() == OCT_RENDER)
//					{
//						RenderComponent* pRenderComponent = (RenderComponent*)i;
//
//						RemoveBind(pRenderComponent);
//					}
//				}
//			}
//
//			m_lFocus.Remove(sFocus);
//		}
//	}
//
//	g_sFocusRenderConnect* IRenderConnect::CreateFocus(CameraComponent* pCamera)
//	{
//		g_sFocusRenderConnect* sFocusRenderConnect = new g_sFocusRenderConnect();
//
//		sFocusRenderConnect->m_pFocusCameraComponent = pCamera;
//		sFocusRenderConnect->m_pFocusScene = pCamera->GetSceneObject()->GetScene();
//
//		return sFocusRenderConnect;
//	}
//}