#include "sphere.h"

// ------------------------------------------------------------------------------------ //
// Is hit
// ------------------------------------------------------------------------------------ //
bool Geometry::Sphere::IsHit( const Math::Ray& Ray, float TMin, float TMax, HitRecord& HitRecord ) const
{
	Math::Vector3D		direction = Ray.GetOrigin() - center;
	float				a = Math::Vector3D::Dot( Ray.GetDirection(), Ray.GetDirection() );
	float				b = Math::Vector3D::Dot( direction, Ray.GetDirection() );
	float				c = Math::Vector3D::Dot( direction, direction ) - radius * radius;
	float				discriminant = b * b - a * c;

	if ( discriminant > 0 )
	{
		float			temp = ( -b - std::sqrt( b * b - a * c ) ) / a;
		if ( temp < TMax && temp > TMin )
		{
			HitRecord.t = temp;
			HitRecord.p = Ray.PointAtParameter( HitRecord.t );
			HitRecord.normal = ( HitRecord.p - center ) / radius;
			HitRecord.material = material;
			return true;
		}

		temp = ( -b + std::sqrt( b * b - a * c ) ) / a;
		if ( temp < TMax && temp > TMin )
		{
			HitRecord.t = temp;
			HitRecord.p = Ray.PointAtParameter( HitRecord.t );
			HitRecord.normal = ( HitRecord.p - center ) / radius;
			HitRecord.material = material;
			return true;
		}
	}

	return false;
}

// ------------------------------------------------------------------------------------ //
// Constructor
// ------------------------------------------------------------------------------------ //
Geometry::Sphere::Sphere( IMaterial* Material ) :
	center( 0.f, 0.f, 0.f ),
	radius( 0.f ),
	material( Material )
{}

// ------------------------------------------------------------------------------------ //
// Constructor
// ------------------------------------------------------------------------------------ //
Geometry::Sphere::Sphere( const Math::Vector3D& Center, float Radius, IMaterial* Material ) :
	center( Center ),
	radius( Radius ),
	material( Material )
{}
