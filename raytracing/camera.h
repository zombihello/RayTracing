#ifndef CAMERA_H
#define CAMERA_H

#include "math/ray.h"

//---------------------------------------------------------------------//

class Camera
{
public:
	Camera();

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

