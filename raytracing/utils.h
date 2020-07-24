#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>

//---------------------------------------------------------------------//

namespace Math
{
	class Vector3D;
}

//---------------------------------------------------------------------//

inline float		drand48()
{
	return ( float ) rand() / RAND_MAX;
}

//---------------------------------------------------------------------//

Math::Vector3D		RandomInUnitSphere();
Math::Vector3D		Reflect( const Math::Vector3D& Vector, const Math::Vector3D& Normal );
bool				Refract( const Math::Vector3D& Vector, const Math::Vector3D& Normal, float NiOvertNt, Math::Vector3D& Refracted );
float				Schlick( float Cosine, float RefIdx );

//---------------------------------------------------------------------//

#endif // !UTILS_H
