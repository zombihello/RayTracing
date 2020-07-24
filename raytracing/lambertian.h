#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "imaterial.h"

//---------------------------------------------------------------------//

class Lambertian : public IMaterial
{
public:
	// IMaterial
	virtual bool			Scatter( const Math::Ray& Ray, const HitRecord& HitRecord, Math::Vector3D& Attenuation, Math::Ray& Scattered ) const;

	// Lambertian
	Lambertian( const Math::Vector3D& Albedo );

private:
	Math::Vector3D			albedo;
};

//---------------------------------------------------------------------//

#endif // !LAMBERTIAN_H

