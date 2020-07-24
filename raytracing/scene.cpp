#include "common/types.h"
#include "geometry/sphere.h"

#include "utils.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include "scene.h"

// ------------------------------------------------------------------------------------ //
// Constructor
// ------------------------------------------------------------------------------------ //
Scene::Scene()
{}

// ------------------------------------------------------------------------------------ //
// Destructor
// ------------------------------------------------------------------------------------ //
Scene::~Scene()
{
	Clear();
}

// ------------------------------------------------------------------------------------ //
// Initialize
// ------------------------------------------------------------------------------------ //
void Scene::Initialize()
{
	IMaterial*			material = new Lambertian( Math::Vector3D( 0.5f, 0.5f, 0.5f ) );
	
	AddMaterial( material );
	AddSphere( Math::Vector3D( 0, -1000.f, 0.f ), 1000.f, material );

	for ( int a = -11; a < 11; ++a )
		for ( int b = -11; b < 11; ++b )
		{
			float			chooseMaterial = DRandom();
			Math::Vector3D	center( a + 0.9f * DRandom(), 0.2f, b + 0.9f * DRandom() );

			if ( ( center - Math::Vector3D( 4.f, 0.2f, 0.f ) ).GetLength() > 0.9f )
			{
				// Diffuse
				if ( chooseMaterial < 0.8f )
				{
					material = new Lambertian( Math::Vector3D( DRandom() * DRandom(), DRandom() * DRandom(), DRandom() * DRandom() ) );
					AddMaterial( material );
					AddSphere( center, 0.2f, material );
				}

				// Metal
				else if ( chooseMaterial < 0.95f )
				{
					material = new Metal( Math::Vector3D( 0.5f * ( 1.f + DRandom() ), 0.5f * ( 1.f + DRandom() ), 0.5f * ( 1.f + DRandom() ) ), 0.5f * DRandom() );
					AddMaterial( material );
					AddSphere( center, 0.2f, material );
				}

				// Glass
				else
				{
					material = new Dielectric( 1.5f );
					AddMaterial( material );
					AddSphere( center, 0.2f, material );
				}
			}
		}

	material = new Dielectric( 1.5f );
	AddMaterial( material );
	AddSphere( Math::Vector3D( 0.f, 1.f, 0.f ), 1.f, material );

	material = new Lambertian( Math::Vector3D( 0.4f, 0.2f, 0.1f ) );
	AddMaterial( material );
	AddSphere( Math::Vector3D( -4.f, 1.f, 0.f ), 1.f, material );

	material = new Metal( Math::Vector3D( 0.7f, 0.6f, 0.5f ), 0.f );
	AddMaterial( material );
	AddSphere( Math::Vector3D( 4.f, 1.f, 0.f ), 1.f, material );
}

// ------------------------------------------------------------------------------------ //
// Clear scene
// ------------------------------------------------------------------------------------ //
void Scene::Clear()
{
	for ( UInt32_t index = 0, count = hitables.size(); index < count; ++index )
		delete hitables[ index ];

	for ( UInt32_t index = 0, count = materials.size(); index < count; ++index )
		delete materials[ index ];

	hitables.clear();
	materials.clear();
}

// ------------------------------------------------------------------------------------ //
// Add material
// ------------------------------------------------------------------------------------ //
void Scene::AddMaterial( IMaterial* Material )
{
	if ( !Material ) return;
	materials.push_back( Material );
}

// ------------------------------------------------------------------------------------ //
// Add sphere
// ------------------------------------------------------------------------------------ //
void Scene::AddSphere( const Math::Vector3D& Center, float Radius, IMaterial* Material )
{
	if ( !Material ) return;

	hitables.push_back( new Geometry::Sphere( Center, Radius, Material ) );
	world.Append( hitables.back() );
}
