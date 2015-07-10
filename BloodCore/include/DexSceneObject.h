#pragma once

#include "DexPreCompletion.h"
#include "DexCoreObject.h"
#include "DexMath.h"

namespace Dex
{
	typedef vector<CoreComponent*> _lCoreComponent;

	class D_EXPORT SceneObject : public CoreObject
	{
	public:
		SceneObject(const string& c_name, Scene* scene, UInt32 id, ofstream* logger, SceneObject* parent = nullptr);
		virtual ~SceneObject(void);

		UInt32 GetId(void);
		Scene* GetScene(void);

		void AddComponent(CoreComponent* pComponent);
		void RemoveComponent(CoreComponent* pComponent);

		void GetObjectComponents(_lCoreComponent& ocs);

		// Position
		void Move(const Point3& position);
		void MoveX(const Point& move);
		void MoveY(const Point& move);
		void MoveZ(const Point& move);
		void MoveTo(const Point3& position);
		Point3& GetPosition(void);
		Point3 GetFullPosition(void);

		// Rotation
		void Rotation(const Point3& rotation);
		void RotationX(const Point& angle);
		void RotationY(const Point& angle);
		void RotationZ(const Point& angle);
		void RotationTo(const Point3& rotation);
		Point3& GetRotation(void);
		Point3 GetFullRotation(void);

		// Scale
		void Scale(const Point3& scale);
		void ScaleX(const Point& size);
		void ScaleY(const Point& size);
		void ScaleZ(const Point& size);
		void ScaleTo(const Point3& scale);
		Point3& GetScale(void);
		Point3 GetFullScale(void);

		bool IsCalculateMatrix(void);

	protected:
		UInt32				m_nId;
		Scene*				m_pScene;
		SceneObject*		m_pParent;

		Point3				m_Position;
		Point3				m_Rotation;
		Point3				m_Scale;
		bool				m_bIsCalculateMatrix;

		_lCoreComponent	m_lObjectComponent;

		void CalculatePosition(const Point3& position);
		void CalculateRotation(const Point3& rotation);
		void CalculateScale(const Point3& scale);
	};
}