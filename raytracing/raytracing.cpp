#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "math/vector3d.h"
#include "math/ray.h"
#include "geometry/sphere.h"
#include "common/types.h"
#include "utils.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include "hitablelist.h"
#include "camera.h"

Math::Vector3D		Color( const Math::Ray& Ray, IHitable* World, int Depth )
{
	HitRecord		hitRecord;
	if ( World->IsHit( Ray, 0.001f, std::numeric_limits< float >::max(), hitRecord ) )
	{
		Math::Ray			scattered;
		Math::Vector3D		attenuation;
		if ( Depth < 50 && hitRecord.material->Scatter( Ray, hitRecord, attenuation, scattered ) )
			return attenuation * Color( scattered, World, Depth + 1 );
		else
			return Math::Vector3D( 0.f, 0.f, 0.f );
	}
	else
	{
		Math::Vector3D		normalizedDir = Math::Vector3D::Normalize( Ray.GetDirection() );
		float				t = 0.5f * ( normalizedDir.GetY() + 1.f );
		return ( 1.f - t ) * Math::Vector3D( 1.f, 1.f, 1.f ) + t * Math::Vector3D( 0.5f, 0.7f, 1.f );
	}
}
#include <cmath>
int main()
{
	std::ofstream		render( "output.ppm" );
	UInt32_t			width = 200;
	UInt32_t			height = 100;
	UInt32_t			countSamples = 100;
	
	render << "P3\n" << width << " " << height << "\n255\n";

	Lambertian				lambertian1( Math::Vector3D( 0.f, 0.f, 1.f ) );
	Lambertian				lambertian2( Math::Vector3D( 0.8f, 0.8f, 0.f ) );
	Metal					metal1( Math::Vector3D( 0.8f, 0.6f, 0.2f ), 0.3f );
	Dielectric				dielectric( 1.5f );

	Geometry::Sphere		sphere1( Math::Vector3D( 0.f, 0.f, -1.f ), 0.5f, &lambertian1 );
	Geometry::Sphere		sphere2( Math::Vector3D( 0.f, -100.5f, -1.f ), 100.f, &lambertian2 );
	Geometry::Sphere		sphere3( Math::Vector3D( 1.f, 0.f, -1.f ), 0.5f, &metal1 );
	Geometry::Sphere		sphere4( Math::Vector3D( -1.f, 0.f, -1.f ), 0.5f, &dielectric );
	Geometry::Sphere		sphere5( Math::Vector3D( -1.f, 0.f, -1.f ), -0.45f, &dielectric );
	Camera					camera( Math::Vector3D( -2.f, 2.f, 1.f ), Math::Vector3D( 0.f, 0.f, -1.f ), Math::Vector3D( 0.f, 1.f, 0.f ), 90.f, ( float ) width / height );
	HitableList				world;

	world.Append( &sphere1 );
	world.Append( &sphere2 );
	world.Append( &sphere3 );
	world.Append( &sphere4 );
	world.Append( &sphere5 );

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
				color += Color( ray, &world, 0 );
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