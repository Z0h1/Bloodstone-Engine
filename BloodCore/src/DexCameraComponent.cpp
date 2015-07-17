#include "DexCameraComponent.h"

namespace Dex
{
	CameraComponent::CameraComponent(const string& cName, SceneObject* pParent,
		const _point& nRange)
		: CoreComponent(cName, pParent, OCT_CAMERA)
	{
		m_nRange = nRange;
		m_bIsCalculateViewMatrix = false;

		m_nLookAt = _4point(0.0f, 0.0f, 1.0f);
		m_nRight = _4point(1.0f, 0.0f, 0.0f);
		m_nUp = _4point(0.0f, 1.0f, 0.0f);

		m_matrixView = _4matrix::zero();

		CalculateMatrixView();
	}

	CameraComponent::~CameraComponent(void)
	{
	}

	void CameraComponent::CalculateMatrixView()
	{
		if (m_bIsCalculateViewMatrix) {
			return;
		}

		//m_matrixView = MatrixTranspose(MatrixLookAtRH(m_nRight, m_nLookAt, m_nUp));

		m_bIsCalculateViewMatrix = true;
	}

	_4matrix& CameraComponent::GetMatrixView(void)
	{
		CalculateMatrixView();

		return m_matrixView;
	}

	void CameraComponent::RotateRL(const _point& nAngle)
	{
		m_nRotateRight =+ nAngle;

		m_bIsCalculateViewMatrix = true;
	}

	void CameraComponent::RotateDU(const _point& nAngle)
	{
		m_nRotateUp =+ nAngle;

		m_bIsCalculateViewMatrix = true;
	}

	void CameraComponent::ResetRotate(void)
	{
		m_nRotateUp = 0;
		m_nRotateRight = 0;
		m_nRotateLookAt = 0;
	}
}