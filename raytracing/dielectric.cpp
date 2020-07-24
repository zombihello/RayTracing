#include "dielectric.h"
#include "utils.h"

// ------------------------------------------------------------------------------------ //
// Scatter
// ------------------------------------------------------------------------------------ //
bool Dielectric::Scatter( const Math::Ray& Ray, const HitRecord& HitRecord, Math::Vector3D& Attenuation, Math::Ray& Scattered ) const
{
	Math::Vector3D			outwardNormal;
	Math::Vector3D			reflected = Reflect( Ray.GetDirection(), HitRecord.normal );
	Math::Vector3D			refracted;
	float					niOverNt = 0.f;
	float					reflectProb = 0.f;
	float					cosine = 0.f;

	Attenuation = Math::Vector3D( 1.f, 1.f, 1.f );	
	if ( Math::Vector3D::Dot( Ray.GetDirection(), HitRecord.normal ) > 0.f )
	{
		outwardNormal = -HitRecord.normal;
		niOverNt = refIdx;
		cosine = refIdx * Math::Vector3D::Dot( Ray.GetDirection(), HitRecord.normal ) / Ray.GetDirection().GetLength();
	}
	else
	{
		outwardNormal = HitRecord.normal;
		niOverNt = 1.f / refIdx;
		cosine = -Math::Vector3D::Dot( Ray.GetDirection(), HitRecord.normal ) / Ray.GetDirection().GetLength();
	}

	if ( Refract( Ray.GetDirection(), outwardNormal, niOverNt, refracted ) )
		reflectProb = Schlick( cosine, refIdx );
	else
	{
		Scattered = Math::Ray( HitRecord.p, reflected );
		reflectProb = 1.f;
	}
		
	if ( drand48() < reflectProb )
		Scattered = Math::Ray( HitRecord.p, reflected );
	else
		Scattered = Math::Ray( HitRecord.p, refracted );

	return true;
}

// ------------------------------------------------------------------------------------ //
// Constructor
// ------------------------------------------------------------------------------------ //
Dielectric::Dielectric( float Ri ) :
	refIdx( Ri )
{}
