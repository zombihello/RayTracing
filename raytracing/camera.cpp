#include <cmath>

#include "camera.h"

// ------------------------------------------------------------------------------------ //
// Constructor
// ------------------------------------------------------------------------------------ //
Camera::Camera( const Math::Vector3D& LookFrom, const Math::Vector3D& LookAt, const Math::Vector3D& Up, float FOV, float Aspect ) :
	origin( LookFrom )
{
	Math::Vector3D			u;
	Math::Vector3D			v;
	Math::Vector3D			w;

	float					theta = FOV * MATH_PI / 180.f;
	float					halfHeight = std::tan( theta / 2.f );
	float					halfWidth = Aspect * halfHeight;

	w = Math::Vector3D::Normalize( LookFrom - LookAt );
	u = Math::Vector3D::Normalize( Math::Vector3D::Cross( Up, w ) );
	v = Math::Vector3D::Cross( w, u );
	
	//lowerLeftCorner = Math::Vector3D( -halfWidth, -halfHeight, -1.f );
	lowerLeftCorner = origin - halfWidth * u - halfHeight * v - w;
	horizontal = 2.f * halfWidth * u;
	vertical = 2.f * halfHeight * v;
}
