#include "DexSceneObject.h"
#include "DexRenderComponent.h"
#include "DexCameraComponent.h"
#include "DexScene.h"
#include "DexMath.h"

namespace DEX
{
	SceneObject::SceneObject(const string& c_name, Scene* scene, _32un id, ofstream* logger, SceneObject* parent)
		: CoreObject(c_name, logger, WorkPriority::WP_STEP_2)
	{
		m_pScene = scene;
		m_pParent = parent;
		m_nId = id;

		m_Position = _3point(0.0f, 0.0f, 0.0f);
		m_Rotation = _3point(0.0f, 0.0f, 0.0f);
		m_Scale = _3point(1.0f, 1.0f, 1.0f);

		if (parent != nullptr) {
			m_Position = m_Position + parent->GetPosition();
		}

		m_bIsCalculateMatrix = true;
	}
	SceneObject::~SceneObject(void)
	{
	}

	_32un SceneObject::GetId(void)
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

	void SceneObject::CalculatePosition(const _3point& position)
	{
		m_Position = position;

		m_bIsCalculateMatrix = false;
	}

	void SceneObject::CalculateRotation(const _3point& rotation)
	{
		m_Rotation = rotation;

		m_bIsCalculateMatrix = false;
	}

	void SceneObject::CalculateScale(const _3point& scale)
	{
		m_Scale = scale;

		m_bIsCalculateMatrix = false;
	}

	// Position
	void SceneObject::Move(const _3point& position)
	{
		CalculatePosition(m_Position + position);
	}
	void SceneObject::MoveX(const _point& move)
	{
		CalculatePosition(m_Position + _3point(move, 0.0f, 0.0f));
	}
	void SceneObject::MoveY(const _point& move)
	{
		CalculatePosition(m_Position + _3point(0.0f, move, 0.0f));
	}
	void SceneObject::MoveZ(const _point& move)
	{
		CalculatePosition(m_Position + _3point(0.0f, 0.0f, move));
	}
	void SceneObject::MoveTo(const _3point& position)
	{
		CalculatePosition(position);
	}
	_3point& SceneObject::GetPosition(void)
	{
		return m_Position;
	}
	_3point SceneObject::GetFullPosition(void)
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
	void SceneObject::Rotation(const _3point& rotation)
	{
		CalculateRotation(m_Rotation + rotation);
	}
	void SceneObject::RotationX(const _point& angle)
	{
		CalculateRotation(m_Rotation + _3point(angle, 0.0f, 0.0f));
	}
	void SceneObject::RotationY(const _point& angle)
	{
		CalculateRotation(m_Rotation + _3point(0.0f, angle, 0.0f));
	}
	void SceneObject::RotationZ(const _point& angle)
	{
		CalculateRotation(m_Rotation + _3point(0.0f, 0.0f, angle));
	}
	void SceneObject::RotationTo(const _3point& rotation)
	{
		CalculateRotation(rotation);
	}
	_3point& SceneObject::GetRotation(void)
	{
		return m_Rotation;
	}
	_3point SceneObject::GetFullRotation(void)
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
	void SceneObject::Scale(const _3point& scale)
	{
		CalculateScale(m_Scale + scale);
	}
	void SceneObject::ScaleX(const _point& size)
	{
		CalculateScale(m_Scale + _3point(size, 0.0f, 0.0f));
	}
	void SceneObject::ScaleY(const _point& size)
	{
		CalculateScale(m_Scale + _3point(0.0f, size, 0.0f));
	}
	void SceneObject::ScaleZ(const _point& size)
	{
		CalculateScale(m_Scale + _3point(0.0f, 0.0f, size));
	}
	void SceneObject::ScaleTo(const _3point& scale)
	{
		CalculateScale(scale);
	}
	_3point& SceneObject::GetScale(void)
	{
		return m_Scale;
	}
	_3point SceneObject::GetFullScale(void)
	{
		return m_Scale;
	}

	bool SceneObject::IsCalculateMatrix(void)
	{
		return m_bIsCalculateMatrix;
	}
}