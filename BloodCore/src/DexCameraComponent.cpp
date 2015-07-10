#include "DexCameraComponent.h"

namespace Dex
{
	CameraComponent::CameraComponent( const string& cName, SceneObject* pParent,
		const Point& nRange )
		: CoreComponent( cName, pParent, OCT_CAMERA )
	{
		m_nRange = nRange;

		m_nLookAt = Point3( 0.0f, 0.0f, 1.0f );
		m_nRight = Point3( 1.0f, 0.0f, 0.0f );
		m_nUp = Point3( 0.0f, 1.0f, 0.0f );

		m_bIsCalculateViewMatrix = true;
	}

	CameraComponent::~CameraComponent( void )
	{
	}

	Point3 CameraComponent::GetRight( void )
	{
		return m_nRight;
	}

	Point CameraComponent::GetRotateRight( void )
	{
		return m_nRotateRight;
	}

	Point3 CameraComponent::GetLookAt( void )
	{
		return m_nLookAt;
	}

	Point CameraComponent::GetRotateLookAt( void )
	{
		return m_nRotateLookAt;
	}

	Point3 CameraComponent::GetUp( void )
	{
		return m_nUp;
	}

	Point CameraComponent::GetRotateUp( void )
	{
		return m_nRotateUp;
	}

	void CameraComponent::RotateRL( const Point& nAngle )
	{
		m_nRotateRight =+ nAngle;

		m_bIsCalculateViewMatrix = true;
	}

	void CameraComponent::RotateDU( const Point& nAngle )
	{
		m_nRotateUp =+ nAngle;

		m_bIsCalculateViewMatrix = true;
	}

	void CameraComponent::ResetRotate( void )
	{
		m_nRotateUp = m_nRotateRight = m_nRotateLookAt = 0;
	}
}