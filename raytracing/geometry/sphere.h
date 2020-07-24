#ifndef SPHERE_H
#define SPHERE_H

#include "ihitable.h"

//---------------------------------------------------------------------//

namespace Geometry
{
	//---------------------------------------------------------------------//

	class Sphere : public IHitable
	{
	public:
		// IHitable
		virtual bool			IsHit( const Math::Ray& Ray, float TMin, float TMax, HitRecord& HitRecord ) const;

		// Sphere
		Sphere();
		Sphere( const Math::Vector3D& Center, float Radius );

	private:
		Math::Vector3D			center;
		float					radius;
	};

	//---------------------------------------------------------------------//
}

//---------------------------------------------------------------------//

#endif // !SPHERE_H
