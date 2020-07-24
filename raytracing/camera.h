#ifndef CAMERA_H
#define CAMERA_H

#include "math/ray.h"

#define MATH_PI			3.14159265359f

//---------------------------------------------------------------------//

class Camera
{
public:
	Camera( const Math::Vector3D& LookFrom, const Math::Vector3D& LookAt, const Math::Vector3D& Up, float FOV, float Aspect );

	inline Math::Ray		GetRay( float U, float V )
	{
		return Math::Ray( origin, lowerLeftCorner + U * horizontal + V * vertical - origin );
	}

private:
	Math::Vector3D			origin;
	Math::Vector3D			lowerLeftCorner;
	Math::Vector3D			horizontal;
	Math::Vector3D			vertical;
};

//---------------------------------------------------------------------//

#endif // !CAMERA_H

