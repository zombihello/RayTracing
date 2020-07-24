#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

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
#include "scene.h"

// ------------------------------------------------------------------------------------ //
// Get color final pixel
// ------------------------------------------------------------------------------------ //
Math::Vector3D		GetPixel( const Math::Ray& Ray, const IHitable* World, int Depth )
{
	HitRecord		hitRecord;
	if ( World->IsHit( Ray, 0.001f, std::numeric_limits< float >::max(), hitRecord ) )
	{
		Math::Ray			scattered;
		Math::Vector3D		attenuation;
		if ( Depth < 50 && hitRecord.material->Scatter( Ray, hitRecord, attenuation, scattered ) )
			return attenuation * GetPixel( scattered, World, Depth + 1 );
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

// ------------------------------------------------------------------------------------ //
// Save config
// ------------------------------------------------------------------------------------ //
void				SaveConfig( const std::string& Path, UInt32_t Width, UInt32_t Height, UInt32_t CountSamples )
{
	std::ofstream		outputFile( Path );
	outputFile << "{\n"
		<< "\t\"Width\": " << Width << ",\n"
		<< "\t\"Height\": " << Height << ",\n"
		<< "\t\"CountSamples\": " << CountSamples << "\n"
		<< "}";
}

// ------------------------------------------------------------------------------------ //
// Load config
// ------------------------------------------------------------------------------------ //
void				LoadConfig( const std::string& Path, UInt32_t& Width, UInt32_t& Height, UInt32_t& CountSamples )
{
	std::ifstream		file( Path );
	Width = 200;
	Height = 100;
	CountSamples = 10;

	if ( !file.is_open() )
	{
		SaveConfig( Path, Width, Height, CountSamples );
		return;
	}

	std::string					stringBuffer;
	UInt32_t					stringLength = 0;
	std::getline( file, stringBuffer, '\0' );

	rapidjson::Document			document;
	document.Parse( stringBuffer.c_str() );
	if ( document.HasParseError() )
	{
		SaveConfig( Path, Width, Height, CountSamples );
		return;
	}

	for ( auto it = document.MemberBegin(), itEnd = document.MemberEnd(); it != itEnd; ++it )
	{
		// Width
		if ( !strcmp( it->name.GetString(), "Width" ) && it->value.IsInt() )
			Width = it->value.GetInt();

		// Height
		else if ( !strcmp( it->name.GetString(), "Height" ) && it->value.IsInt() )
			Height = it->value.GetInt();

		// CountSamples
		else if ( !strcmp( it->name.GetString(), "CountSamples" ) && it->value.IsInt() )
			CountSamples = it->value.GetInt();
	}
}

// ------------------------------------------------------------------------------------ //
// Main function
// ------------------------------------------------------------------------------------ //
int main()
{
	std::ofstream			render( "output.ppm" );
	UInt32_t				width = 200;
	UInt32_t				height = 100;
	UInt32_t				countSamples = 10;
	
	LoadConfig( "config.json", width, height, countSamples );
	render << "P3\n" << width << " " << height << "\n255\n";

	Math::Vector3D			lookFrom( 3.f, 3.f, 2.f );
	Math::Vector3D			lookAt( 0.f, 0.f, -1.f );
	float					distToFocus = ( lookFrom - lookAt ).GetLength();
	float					aperture = 0.1f;
	
	Camera					camera( lookFrom, lookAt, Math::Vector3D( 0.f, 1.f, 0.f ), 75.f, ( float ) width / height, aperture, distToFocus );
	Scene					scene;

	scene.Initialize();
	const HitableList*		world = &scene.GetWorld();

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
				color += GetPixel( ray, world, 0 );
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