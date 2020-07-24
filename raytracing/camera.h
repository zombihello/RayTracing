#ifndef CAMERA_H
#define CAMERA_H

#include "math/ray.h"
#include "utils.h"

#define MATH_PI			3.14159265359f

//---------------------------------------------------------------------//

class Camera
{
public:
	Camera( const Math::Vector3D& LookFrom, const Math::Vector3D& LookAt, const Math::Vector3D& Up, float FOV, float Aspect, float Aperture, float FocusDist );

	inline Math::Ray		GetRay( float U, float V )
	{
		Math::Vector3D			rayDir = lensRadius * RandomInUnitDisk();
		Math::Vector3D			offset = u * rayDir.GetX() + v * rayDir.GetY();
		return Math::Ray( origin + offset, lowerLeftCorner + U * horizontal + V * vertical - origin - offset );
	}

private:
	float					lensRadius;

	Math::Vector3D			origin;
	Math::Vector3D			lowerLeftCorner;
	Math::Vector3D			horizontal;
	Math::Vector3D			vertical;
	Math::Vector3D			u;
	Math::Vector3D			v;
	Math::Vector3D			w;
};

//---------------------------------------------------------------------//

#endif // !CAMERA_H

