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
		// If ray hit in object = calculate pixel color depending on the material
		Math::Ray			scattered;
		Math::Vector3D		attenuation;
		if ( Depth < 50 && hitRecord.material->Scatter( Ray, hitRecord, attenuation, scattered ) )
			return attenuation * GetPixel( scattered, World, Depth + 1 );
		else
			return Math::Vector3D( 0.f, 0.f, 0.f );
	}
	else
	{
		// If ray not hit in object - render background
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
	Width = 200;
	Height = 100;
	CountSamples = 10;
	
	// Open file for read
	std::ifstream		file( Path );
	if ( !file.is_open() )
	{
		SaveConfig( Path, Width, Height, CountSamples );
		return;
	}

	// Getting all content int string buffer
	std::string					stringBuffer;
	UInt32_t					stringLength = 0;
	std::getline( file, stringBuffer, '\0' );

	// Prase json document
	rapidjson::Document			document;
	document.Parse( stringBuffer.c_str() );
	if ( document.HasParseError() )
	{
		SaveConfig( Path, Width, Height, CountSamples );
		return;
	}

	// Getting all elements in json file
	for ( auto it = document.MemberBegin(), itEnd = document.MemberEnd(); it != itEnd; ++it )
	{
		// Getting Width
		if ( !strcmp( it->name.GetString(), "Width" ) && it->value.IsInt() )
			Width = it->value.GetInt();

		// Getting Height
		else if ( !strcmp( it->name.GetString(), "Height" ) && it->value.IsInt() )
			Height = it->value.GetInt();

		// Getting count samples
		else if ( !strcmp( it->name.GetString(), "CountSamples" ) && it->value.IsInt() )
			CountSamples = it->value.GetInt();
	}
}

// ------------------------------------------------------------------------------------ //
// Main function
// ------------------------------------------------------------------------------------ //
int main()
{
	// Output file to render picture (format PPM)
	std::ofstream			render( "output.ppm" );
	UInt32_t				width = 200;
	UInt32_t				height = 100;				// } Default render settings 
	UInt32_t				countSamples = 10;
	
	// Loading config and print header picture
	LoadConfig( "config.json", width, height, countSamples );
	render << "P3\n" << width << " " << height << "\n255\n";

	// Initialize camera
	Math::Vector3D			lookFrom( 13.f, 2.f, 3.f );
	Math::Vector3D			lookAt( 0.f, 0.f, 0.f );
	float					distToFocus = 10.f;
	Camera					camera( lookFrom, lookAt, Math::Vector3D( 0.f, 1.f, 0.f ), 20.f, ( float ) width / height, 0.1f, distToFocus );
	
	// Create and initialize scene
	Scene					scene;
	scene.Initialize();	
	const HitableList*		world = &scene.GetWorld();

	// Render scene to picture
	for ( int j = height - 1; j >= 0; --j )
		for ( int i = 0; i < width; ++i )
		{
			Math::Vector3D		color;

			// Antializing
			for ( int sample = 0; sample < countSamples; ++sample )
			{			
				float		u = ( i + drand48() ) / width;
				float		v = ( j + drand48() ) / height;

				Math::Ray			ray = camera.GetRay( u, v );
				color += GetPixel( ray, world, 0 );
			}

			// We average the value and write to the file
			color /= ( float ) countSamples;
			color = Math::Vector3D( std::sqrt( color[ 0 ] ), std::sqrt( color[ 1 ] ), std::sqrt( color[ 2 ] ) );		
			int ir = ( int ) 255.99f * color[ 0 ];
			int ig = ( int ) 255.99f * color[ 1 ];
			int ib = ( int ) 255.99f * color[ 2 ];
			render << ir << " " << ig << " " << ib << "\n";
		}

	return 0;
}