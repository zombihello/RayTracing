#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "imaterial.h"

//---------------------------------------------------------------------//

class Dielectric : public IMaterial
{
public:
	// IMaterial
	virtual bool			Scatter( const Math::Ray& Ray, const HitRecord& HitRecord, Math::Vector3D& Attenuation, Math::Ray& Scattered ) const;

	// Dielectric
	Dielectric( float Ri );

private:
	float					refIdx;
};

//---------------------------------------------------------------------//

#endif // !DIELECTRIC_H

