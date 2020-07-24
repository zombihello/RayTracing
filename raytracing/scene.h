#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "imaterial.h"
#include "hitablelist.h"

//---------------------------------------------------------------------//

class Scene
{
public:
	Scene();
	~Scene();

	void							Initialize();
	void							Clear();

	inline const HitableList&		GetWorld() const
	{
		return world;
	}

private:
	void							AddMaterial( IMaterial* Material );
	void							AddSphere( const Math::Vector3D& Center, float Radius, IMaterial* Material );

	HitableList						world;
	std::vector< IHitable* >		hitables;
	std::vector< IMaterial* >		materials;
};

//---------------------------------------------------------------------//

#endif // !SCENE_H
