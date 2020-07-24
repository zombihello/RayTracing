#include <cmath>

#include "utils.h"
#include "camera.h"

// ------------------------------------------------------------------------------------ //
// Constructor
// ------------------------------------------------------------------------------------ //
Camera::Camera( const Math::Vector3D& LookFrom, const Math::Vector3D& LookAt, const Math::Vector3D& Up, float FOV, float Aspect, float Aperture, float FocusDist ) :
	origin( LookFrom ),
	lensRadius( Aperture / 2.f )
{
	float					theta = FOV * MATH_PI / 180.f;
	float					halfHeight = std::tan( theta / 2.f );
	float					halfWidth = Aspect * halfHeight;

	w = Math::Vector3D::Normalize( LookFrom - LookAt );
	u = Math::Vector3D::Normalize( Math::Vector3D::Cross( Up, w ) );
	v = Math::Vector3D::Cross( w, u );
	
	lowerLeftCorner = origin - halfWidth * FocusDist * u - halfHeight * FocusDist * v - FocusDist * w;
	horizontal = 2.f * halfWidth * FocusDist * u;
	vertical = 2.f * halfHeight * FocusDist * v;
}
