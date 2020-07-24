#ifndef METAL_H
#define METAL_H

#include "imaterial.h"

//---------------------------------------------------------------------//

class Metal : public IMaterial
{
public:
	// IMaterial
	virtual bool			Scatter( const Math::Ray& Ray, const HitRecord& HitRecord, Math::Vector3D& Attenuation, Math::Ray& Scattered ) const;

	// Metal
	Metal( const Math::Vector3D& Albedo, float Fuzz );

private:
	float					fuzz;
	Math::Vector3D			albedo;
};

//---------------------------------------------------------------------//

#endif // !METAL_H

