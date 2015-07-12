#include "DexSceneObject.h"
#include "DexRenderComponent.h"
#include "DexCameraComponent.h"
#include "DexScene.h"
#include "DexMath.h"

namespace Dex
{
	SceneObject::SceneObject(const string& c_name, Scene* scene, UInt32 id, ofstream* logger, SceneObject* parent)
		: CoreObject(c_name, logger, WorkPriority::WP_STEP_2)
	{
		m_pScene = scene;
		m_pParent = parent;
		m_nId = id;

		m_Position = Point3(0.0f, 0.0f, 0.0f);
		m_Rotation = Point3(0.0f, 0.0f, 0.0f);
		m_Scale = Point3(1.0f, 1.0f, 1.0f);

		if (parent != nullptr) {
			m_Position = m_Position + parent->GetPosition();
		}

		m_bIsCalculateMatrix = true;
	}
	SceneObject::~SceneObject(void)
	{
	}

	UInt32 SceneObject::GetId(void)
	{
		return m_nId;
	}

	Scene* SceneObject::GetScene(void)
	{
		return m_pScene;
	}

	void SceneObject::AddComponent(CoreComponent* pComponent)
	{
		
		if (find(m_lObjectComponent.begin(), m_lObjectComponent.end(), pComponent) == m_lObjectComponent.end())
		{
			switch (pComponent->GetType())
			{
			case OCT_RENDER:
			{
				RenderComponent* pRenderComponent = (RenderComponent*)pComponent;

				_lRenderConnect lRenderConnect;
				m_pScene->GetRenderConnects(lRenderConnect);
				for (auto n : lRenderConnect)
				{
					//n->BindBufferData(pRenderComponent, pRenderComponent->GetBufferData());
				}
			}
			break;
			}

			m_lObjectComponent.push_back(pComponent);
		}
	}

	void SceneObject::RemoveComponent(CoreComponent* pComponent)
	{
		_lCoreComponent::iterator it = find(m_lObjectComponent.begin(), m_lObjectComponent.end(), pComponent);
		if (it != m_lObjectComponent.end())
		{
			switch (pComponent->GetType())
			{
			case OCT_RENDER:
			{
				RenderComponent* pRenderComponent = (RenderComponent*)pComponent;

				_lRenderConnect lRenderConnect;
				m_pScene->GetRenderConnects(lRenderConnect);
				for (auto n : lRenderConnect)
				{
					//n->RemoveBind(pRenderComponent);
				}
			}
			break;
			case OCT_CAMERA:
			{
				CameraComponent* pCameraComponent = (CameraComponent*)pComponent;

				_lRenderConnect lRenderConnect;
				m_pScene->GetRenderConnects(lRenderConnect);
				for (auto n : lRenderConnect)
				{
					//n->RemoveFocus(pCameraComponent);
				}
			}
			break;
			}

			m_lObjectComponent.erase(it);
		}
	}

	void SceneObject::GetObjectComponents(_lCoreComponent& ocs)
	{
		ocs = m_lObjectComponent;
	}

	void SceneObject::CalculatePosition(const Point3& position)
	{
		m_Position = position;

		m_bIsCalculateMatrix = false;
	}

	void SceneObject::CalculateRotation(const Point3& rotation)
	{
		m_Rotation = rotation;

		m_bIsCalculateMatrix = false;
	}

	void SceneObject::CalculateScale(const Point3& scale)
	{
		m_Scale = scale;

		m_bIsCalculateMatrix = false;
	}

	// Position
	void SceneObject::Move(const Point3& position)
	{
		CalculatePosition(m_Position + position);
	}
	void SceneObject::MoveX(const Point& move)
	{
		CalculatePosition(m_Position + Point3(move, 0.0f, 0.0f));
	}
	void SceneObject::MoveY(const Point& move)
	{
		CalculatePosition(m_Position + Point3(0.0f, move, 0.0f));
	}
	void SceneObject::MoveZ(const Point& move)
	{
		CalculatePosition(m_Position + Point3(0.0f, 0.0f, move));
	}
	void SceneObject::MoveTo(const Point3& position)
	{
		CalculatePosition(position);
	}
	Point3& SceneObject::GetPosition(void)
	{
		return m_Position;
	}
	Point3 SceneObject::GetFullPosition(void)
	{
		if (m_pParent)
		{
			return m_Position + m_pParent->GetFullPosition();
		}
		else
		{
			return m_Position;
		}
	}

	// Rotation
	void SceneObject::Rotation(const Point3& rotation)
	{
		CalculateRotation(m_Rotation + rotation);
	}
	void SceneObject::RotationX(const Point& angle)
	{
		CalculateRotation(m_Rotation + Point3(angle, 0.0f, 0.0f));
	}
	void SceneObject::RotationY(const Point& angle)
	{
		CalculateRotation(m_Rotation + Point3(0.0f, angle, 0.0f));
	}
	void SceneObject::RotationZ(const Point& angle)
	{
		CalculateRotation(m_Rotation + Point3(0.0f, 0.0f, angle));
	}
	void SceneObject::RotationTo(const Point3& rotation)
	{
		CalculateRotation(rotation);
	}
	Point3& SceneObject::GetRotation(void)
	{
		return m_Rotation;
	}
	Point3 SceneObject::GetFullRotation(void)
	{
		if (m_pParent)
		{
			return m_Rotation + m_pParent->GetFullRotation();
		}
		else
		{
			return m_Rotation;
		}
	}

	// Scale
	void SceneObject::Scale(const Point3& scale)
	{
		CalculateScale(m_Scale + scale);
	}
	void SceneObject::ScaleX(const Point& size)
	{
		CalculateScale(m_Scale + Point3(size, 0.0f, 0.0f));
	}
	void SceneObject::ScaleY(const Point& size)
	{
		CalculateScale(m_Scale + Point3(0.0f, size, 0.0f));
	}
	void SceneObject::ScaleZ(const Point& size)
	{
		CalculateScale(m_Scale + Point3(0.0f, 0.0f, size));
	}
	void SceneObject::ScaleTo(const Point3& scale)
	{
		CalculateScale(scale);
	}
	Point3& SceneObject::GetScale(void)
	{
		return m_Scale;
	}
	Point3 SceneObject::GetFullScale(void)
	{
		return m_Scale;
	}

	bool SceneObject::IsCalculateMatrix(void)
	{
		return m_bIsCalculateMatrix;
	}
}