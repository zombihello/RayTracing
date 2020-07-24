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
		Sphere( IMaterial* Material );
		Sphere( const Math::Vector3D& Center, float Radius, IMaterial* Material );

	private:
		float					radius;
		Math::Vector3D			center;
		
		IMaterial*				material;
	};

	//---------------------------------------------------------------------//
}

//---------------------------------------------------------------------//

#endif // !SPHERE_H
