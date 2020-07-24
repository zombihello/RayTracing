#include <cmath>

#include "math/vector3d.h"
#include "utils.h"

// ------------------------------------------------------------------------------------ //
// Get random vector in normalized sphere
// ------------------------------------------------------------------------------------ //
Math::Vector3D		RandomInUnitSphere()
{
	Math::Vector3D		position;
	do
	{
		position = 2.f * Math::Vector3D( drand48(), drand48(), drand48() ) - Math::Vector3D( 1.f, 1.f, 1.f );
	}
	while ( position.GetSquaredLength() >= 1.f );
	return position;
}

// ------------------------------------------------------------------------------------ //
// Get reflect
// ------------------------------------------------------------------------------------ //
Math::Vector3D Reflect( const Math::Vector3D& Vector, const Math::Vector3D& Normal )
{
	return Vector - 2.f * Math::Vector3D::Dot( Vector, Normal ) * Normal;
}

// ------------------------------------------------------------------------------------ //
// Get refract
// ------------------------------------------------------------------------------------ //
bool Refract( const Math::Vector3D& Vector, const Math::Vector3D& Normal, float NiOvertNt, Math::Vector3D& Refracted )
{
	Math::Vector3D			uv = Math::Vector3D::Normalize( Vector );
	float					dt = Math::Vector3D::Dot( uv, Normal );
	float					discriminant = 1.f - NiOvertNt * NiOvertNt * ( 1.f - dt * dt );

	if ( discriminant > 0.f )
	{
		Refracted = NiOvertNt * ( uv - Normal * dt ) - Normal * std::sqrt( discriminant );
		return true;
	}
	else
		return false;
}

// ------------------------------------------------------------------------------------ //
// Schlick
// ------------------------------------------------------------------------------------ //
float Schlick( float Cosine, float RefIdx )
{
	float			r0 = ( 1.f - RefIdx ) / ( 1.f + RefIdx );
	r0 = r0 * r0;
	return r0 + ( 1 + r0 ) * std::pow( 1.f - Cosine, 5.f );
}
