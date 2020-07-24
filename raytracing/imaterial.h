#ifndef IMATERIAL_H
#define IMATERIAL_H

#include "math/ray.h"
#include "ihitable.h"

//---------------------------------------------------------------------//

class IMaterial
{
public:
	virtual ~IMaterial() {}
	virtual bool			Scatter( const Math::Ray& Ray, const HitRecord& HitRecord, Math::Vector3D& Attenuation, Math::Ray& Scattered ) const = 0;
};

//---------------------------------------------------------------------//

#endif // !IMATERIAL_H
