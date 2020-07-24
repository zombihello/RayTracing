#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "math/vector3d.h"
#include "math/ray.h"
#include "geometry/sphere.h"
#include "common/types.h"
#include "hitablelist.h"
#include "camera.h"

inline float		drand48()
{
	return ( float ) rand() / RAND_MAX;
}

Math::Vector3D		RandomInUnitSphere()
{
	Math::Vector3D		position;
	do
	{
		position = 2.f * Math::Vector3D( drand48(), drand48(), drand48() ) - Math::Vector3D( 1.f, 1.f, 1.f );
	}
	while ( position.GetSquaredLength() >= 1.f );
	return position;
}

Math::Vector3D		Color( const Math::Ray& Ray, IHitable* World )
{
	HitRecord		hitRecord;
	if ( World->IsHit( Ray, 0.001f, std::numeric_limits< float >::max(), hitRecord ) )
	{
		Math::Vector3D		target = hitRecord.p + hitRecord.normal + RandomInUnitSphere();
		return 0.5f * Color( Math::Ray( hitRecord.p, target - hitRecord.p ), World );
	}
	else
	{
		Math::Vector3D		normalizedDir = Math::Vector3D::Normalize( Ray.GetDirection() );
		float				t = 0.5f * ( normalizedDir.GetY() + 1.f );
		return ( 1.f - t ) * Math::Vector3D( 1.f, 1.f, 1.f ) + t * Math::Vector3D( 0.5f, 0.7f, 1.f );
	}
}

int main()
{
	std::ofstream		render( "output.ppm" );
	UInt32_t			width = 200;
	UInt32_t			height = 100;
	UInt32_t			countSamples = 100;
	
	render << "P3\n" << width << " " << height << "\n255\n";

	Geometry::Sphere		sphere1( Math::Vector3D( 0.f, 1.f, -1.f ), 0.5f );
	Geometry::Sphere		sphere2( Math::Vector3D( 0.f, -100.5f, -1.f ), 100.f );
	Camera					camera;
	HitableList				world;

	world.Append( &sphere1 );
	world.Append( &sphere2 );

	for ( int j = height - 1; j >= 0; --j )
		for ( int i = 0; i < width; ++i )
		{
			Math::Vector3D		color;

			for ( int sample = 0; sample < countSamples; ++sample )
			{
				
				float		u = ( i + drand48() ) / width;
				float		v = ( j + drand48() ) / height;

				Math::Ray			ray = camera.GetRay( u, v );
				Math::Vector3D		position = ray.PointAtParameter( 2.f );
				color += Color( ray, &world );
			}

			color /= ( float ) countSamples;
			color = Math::Vector3D( std::sqrt( color[ 0 ] ), std::sqrt( color[ 1 ] ), std::sqrt( color[ 2 ] ) );
			int ir = ( int ) 255.99f * color[ 0 ];
			int ig = ( int ) 255.99f * color[ 1 ];
			int ib = ( int ) 255.99f * color[ 2 ];
			render << ir << " " << ig << " " << ib << "\n";
		}

	return 0;
}