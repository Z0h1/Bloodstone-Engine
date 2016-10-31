#pragma once

#include "DexPreCompletion.h"
#include "DexCoreObject.h"
#include "DexMath.h"

namespace DEX
{
	typedef vector<CoreComponent*> _lCoreComponent;

	class D_EXPORT SceneObject : public CoreObject
	{
	public:
		SceneObject(const string& c_name, Scene* scene, _32un id, ofstream* logger, SceneObject* parent = nullptr);
		virtual ~SceneObject(void);

		_32un GetId(void);
		Scene* GetScene(void);

		void AddComponent(CoreComponent* pComponent);
		void RemoveComponent(CoreComponent* pComponent);

		void GetObjectComponents(_lCoreComponent& ocs);

		// Position
		void Move(const _3point& position);
		void MoveX(const _point& move);
		void MoveY(const _point& move);
		void MoveZ(const _point& move);
		void MoveTo(const _3point& position);
		_3point& GetPosition(void);
		_3point GetFullPosition(void);

		// Rotation
		void Rotation(const _3point& rotation);
		void RotationX(const _point& angle);
		void RotationY(const _point& angle);
		void RotationZ(const _point& angle);
		void RotationTo(const _3point& rotation);
		_3point& GetRotation(void);
		_3point GetFullRotation(void);

		// Scale
		void Scale(const _3point& scale);
		void ScaleX(const _point& size);
		void ScaleY(const _point& size);
		void ScaleZ(const _point& size);
		void ScaleTo(const _3point& scale);
		_3point& GetScale(void);
		_3point GetFullScale(void);

		bool IsCalculateMatrix(void);

	protected:
		_32un				m_nId;
		Scene*				m_pScene;
		SceneObject*		m_pParent;

		_3point				m_Position;
		_3point				m_Rotation;
		_3point				m_Scale;
		bool				m_bIsCalculateMatrix;

		_lCoreComponent	m_lObjectComponent;

		void CalculatePosition(const _3point& position);
		void CalculateRotation(const _3point& rotation);
		void CalculateScale(const _3point& scale);
	};
}