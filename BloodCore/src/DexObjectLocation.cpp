#include "DexObjectLocation.h"

namespace Dex
{
	ObjectLocation::ObjectLocation( void )
	{
		m_pParent = 0;

		m_Position = Point3( 0.0f, 0.0f, 0.0f );
		m_Rotation = Point3( 0.0f, 0.0f, 0.0f );
		m_Scale = Point3( 1.0f, 1.0f, 1.0f );

		m_bIsCalculateMatrix = true;
	}

	ObjectLocation::ObjectLocation( ObjectLocation* pParent )
	{
		m_pParent = pParent;

		m_Position = Point3( 0.0f, 0.0f, 0.0f );
		m_Rotation = Point3( 0.0f, 0.0f, 0.0f );
		m_Scale = Point3( 1.0f, 1.0f, 1.0f );

		m_Position = m_Position + pParent->GetPosition();
	}

	ObjectLocation::~ObjectLocation( void )
	{
	}

	void ObjectLocation::CalculatePosition( const Point3& position )
	{
		m_Position = position;

		m_bIsCalculateMatrix = false;
	}

	void ObjectLocation::CalculateRotation( const Point3& rotation )
	{
		m_Rotation = rotation;

		m_bIsCalculateMatrix = false;
	}

	void ObjectLocation::CalculateScale( const Point3& scale )
	{
		m_Scale = scale;

		m_bIsCalculateMatrix = false;
	}

	// Position
	void ObjectLocation::Move( const Point3& position )
	{
		CalculatePosition( m_Position + position );
	}
	void ObjectLocation::MoveX( const Point& move )
	{
		CalculatePosition( m_Position + Point3( move, 0.0f, 0.0f ) );
	}
	void ObjectLocation::MoveY( const Point& move )
	{
		CalculatePosition( m_Position + Point3( 0.0f, move, 0.0f ) );
	}
	void ObjectLocation::MoveZ( const Point& move )
	{
		CalculatePosition( m_Position + Point3( 0.0f, 0.0f, move ) );
	}
	void ObjectLocation::MoveTo( const Point3& position )
	{
		CalculatePosition( position );
	}
	Point3& ObjectLocation::GetPosition( void )
	{
		return m_Position;
	}
	Point3 ObjectLocation::GetFullPosition( void )
	{
		if ( m_pParent )
		{
			return m_Position + m_pParent->GetFullPosition();
		}
		else
		{
			return m_Position;
		}
	}

	// Rotation
	void ObjectLocation::Rotation( const Point3& rotation )
	{
		CalculateRotation( m_Rotation + rotation );
	}
	void ObjectLocation::RotationX( const Point& angle )
	{
		CalculateRotation( m_Rotation + Point3( angle, 0.0f, 0.0f ) );
	}
	void ObjectLocation::RotationY( const Point& angle )
	{
		CalculateRotation( m_Rotation + Point3( 0.0f, angle, 0.0f ) );
	}
	void ObjectLocation::RotationZ( const Point& angle )
	{
		CalculateRotation( m_Rotation + Point3( 0.0f, 0.0f, angle ) );
	}
	void ObjectLocation::RotationTo( const Point3& rotation )
	{
		CalculateRotation( rotation );
	}
	Point3& ObjectLocation::GetRotation( void )
	{
		return m_Rotation;
	}
	Point3 ObjectLocation::GetFullRotation( void )
	{
		if ( m_pParent )
		{
			return m_Rotation + m_pParent->GetFullRotation();
		}
		else
		{
			return m_Rotation;
		}
	}

	// Scale
	void ObjectLocation::Scale( const Point3& scale )
	{
		CalculateScale( m_Scale + scale );
	}
	void ObjectLocation::ScaleX( const Point& size )
	{
		CalculateScale( m_Scale + Point3( size, 0.0f, 0.0f ) );
	}
	void ObjectLocation::ScaleY( const Point& size )
	{
		CalculateScale( m_Scale + Point3( 0.0f, size, 0.0f ) );
	}
	void ObjectLocation::ScaleZ( const Point& size )
	{
		CalculateScale( m_Scale + Point3( 0.0f, 0.0f, size ) );
	}
	void ObjectLocation::ScaleTo( const Point3& scale )
	{
		CalculateScale( scale );
	}
	Point3& ObjectLocation::GetScale( void )
	{
		return m_Scale;
	}
	Point3 ObjectLocation::GetFullScale( void )
	{
		return m_Scale;
	}

	bool ObjectLocation::IsCalculateMatrix( void )
	{
		return m_bIsCalculateMatrix;
	}
}