#pragma once

#include "DexCoreComponent.h"
#include "DexMath.h"

namespace Dex
{
	class D_EXPORT CameraComponent : public CoreComponent
	{
	public:
		CameraComponent(const string& cName, SceneObject* pParent,
			const Point& nRange);
		~CameraComponent(void);

		void RotateRL(const Point& nAngle);
		void RotateDU(const Point& nAngle);

		Point3 GetRight(void);
		Point GetRotateRight(void);

		Point3 GetLookAt(void);
		Point GetRotateLookAt(void);

		Point3 GetUp(void);
		Point GetRotateUp(void);

		void ResetRotate(void);

	private:
		Point				m_nRange;

		Point				m_nRotateUp;
		Point				m_nRotateRight;
		Point				m_nRotateLookAt;

		Point3				m_nLookAt;
		Point3				m_nRight;
		Point3				m_nUp;

		bool				m_bIsCalculateViewMatrix;
	};
}

