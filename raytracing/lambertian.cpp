#include "lambertian.h"
#include "utils.h"

// ------------------------------------------------------------------------------------ //
// Scatter
// ------------------------------------------------------------------------------------ //
bool Lambertian::Scatter( const Math::Ray& Ray, const HitRecord& HitRecord, Math::Vector3D& Attenuation, Math::Ray& Scattered ) const
{
	Math::Vector3D			target = HitRecord.p + HitRecord.normal + RandomInUnitSphere();
	Scattered = Math::Ray( HitRecord.p, target - HitRecord.p );
	Attenuation = albedo;
	return true;
}

// ------------------------------------------------------------------------------------ //
// Constructor
// ------------------------------------------------------------------------------------ //
Lambertian::Lambertian( const Math::Vector3D& Albedo ) :
	albedo( Albedo )
{}
