#pragma once

#include "DexCoreComponent.h"
#include "DexMath.h"

namespace Dex
{
	class D_EXPORT CameraComponent : public CoreComponent
	{
	public:
		CameraComponent(const string& cName, SceneObject* pParent, const _point& nRange);
		~CameraComponent(void);

		void RotateRL(const _point& nAngle);
		void RotateDU(const _point& nAngle);

		_4point GetRight(void) const { return m_nRight; }
		_point GetRotateRight(void) const { return m_nRotateRight; }

		_4point GetLookAt(void) const { return m_nLookAt; }
		_point GetRotateLookAt(void) const { return m_nRotateLookAt; }

		_4point GetUp(void) const { return m_nUp; }
		_point GetRotateUp(void) const { return m_nRotateUp; }

		_3DMatrix& GetMatrixView(void);

		void ResetRotate(void);

	private:
		void CalculateMatrixView();

		_point				m_nRange;

		_point				m_nRotateUp;
		_point				m_nRotateRight;
		_point				m_nRotateLookAt;

		_4point				m_nLookAt;
		_4point				m_nRight;
		_4point				m_nUp;

		_3DMatrix			m_matrixView;
		bool				m_bIsCalculateViewMatrix;
	};
}

