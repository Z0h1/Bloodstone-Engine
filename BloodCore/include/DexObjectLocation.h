#pragma once

#include "DexPreCompletion.h"
#include "DexCommon.h"

namespace Dex
{
	class D_EXPORT ObjectLocation
	{
	public:
		ObjectLocation( void );
		ObjectLocation( ObjectLocation* pParent );
		virtual ~ObjectLocation( void );

		// Position
		void Move( const Point3& position );
		void MoveX( const Point& move );
		void MoveY( const Point& move );
		void MoveZ( const Point& move );
		void MoveTo( const Point3& position );
		Point3& GetPosition( void );
		Point3 GetFullPosition( void );

		// Rotation
		void Rotation( const Point3& rotation );
		void RotationX( const Point& angle );
		void RotationY( const Point& angle );
		void RotationZ( const Point& angle );
		void RotationTo( const Point3& rotation );
		Point3& GetRotation( void );
		Point3 GetFullRotation( void );

		// Scale
		void Scale( const Point3& scale );
		void ScaleX( const Point& size );
		void ScaleY( const Point& size );
		void ScaleZ( const Point& size );
		void ScaleTo( const Point3& scale );
		Point3& GetScale( void );
		Point3 GetFullScale( void );

		bool IsCalculateMatrix( void );

	private:
		void CalculatePosition( const Point3& position );
		void CalculateRotation( const Point3& rotation );
		void CalculateScale( const Point3& scale );

	protected:
		Point3				m_Position;
		Point3				m_Rotation;
		Point3				m_Scale;
		bool				m_bIsCalculateMatrix;

	private:
		ObjectLocation*		m_pParent;
	};
}