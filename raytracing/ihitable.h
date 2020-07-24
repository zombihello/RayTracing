#ifndef IHITABLE_H
#define IHITABLE_H

#include "math/vector3d.h"
#include "math/ray.h"

//---------------------------------------------------------------------//

struct HitRecord
{
	float					t;
	Math::Vector3D			p;
	Math::Vector3D			normal;
};

//---------------------------------------------------------------------//

class IHitable
{
public:
	virtual ~IHitable() {}
	virtual bool			IsHit( const Math::Ray& Ray, float TMin, float TMax, HitRecord& HitRecord ) const = 0;
};

//---------------------------------------------------------------------//

#endif // !IHITABLE_H
