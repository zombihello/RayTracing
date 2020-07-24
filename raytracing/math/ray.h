#ifndef RAY_H
#define RAY_H

#include "math/vector3d.h"

//---------------------------------------------------------------------//

namespace Math
{
	//---------------------------------------------------------------------//

	class Ray
	{
	public:
		Ray()															{}
		Ray( const Vector3D& Origin, const Vector3D& Direction ) :
			origin( Origin ),
			direction( Direction )
		{}

		static inline float				HitSphere( const Vector3D& Center, float Radius, const Ray& Ray )
		{
			Vector3D			direction = Ray.GetOrigin() - Center;
			float				a = Vector3D::Dot( Ray.GetDirection(), Ray.GetDirection() );
			float				b = 2.f * Vector3D::Dot( direction, Ray.GetDirection() );
			float				c = Vector3D::Dot( direction, direction ) - Radius * Radius;
			float				discriminant = b * b - 4 * a * c;
			
			if ( discriminant < 0.f )
				return -1.f;
			else
				return	( -b - std::sqrt( discriminant ) ) / ( 2.f * a );
		}
		inline Vector3D					PointAtParameter( float Value ) const
		{
			return origin + Value * direction;
		}

		inline const Vector3D&			GetOrigin() const
		{
			return origin;
		}
		inline const Vector3D&			GetDirection() const
		{
			return direction;
		}

	private:
		Vector3D			origin;
		Vector3D			direction;
	};

	//---------------------------------------------------------------------//
}

//---------------------------------------------------------------------//

#endif // !RAY_H
