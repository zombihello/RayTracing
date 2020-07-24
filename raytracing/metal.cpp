#include "metal.h"
#include "utils.h"

// ------------------------------------------------------------------------------------ //
// Scatter
// ------------------------------------------------------------------------------------ //
bool Metal::Scatter( const Math::Ray& Ray, const HitRecord& HitRecord, Math::Vector3D& Attenuation, Math::Ray& Scattered ) const
{
	Math::Vector3D		reflected = Reflect( Math::Vector3D::Normalize( Ray.GetDirection() ), HitRecord.normal );
	Scattered = Math::Ray( HitRecord.p, reflected + fuzz * RandomInUnitSphere() );
	Attenuation = albedo;
	return Math::Vector3D::Dot( Scattered.GetDirection(), HitRecord.normal ) > 0.f;
}

// ------------------------------------------------------------------------------------ //
// Constructor
// ------------------------------------------------------------------------------------ //
Metal::Metal( const Math::Vector3D& Albedo, float Fuzz ) :
	albedo( Albedo )
{
	if ( Fuzz < 1.f )
		fuzz = Fuzz;
	else
		fuzz = 1.f;
}
