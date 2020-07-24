#ifndef HITABLELIST_H
#define HITABLELIST_H

#include <vector>

#include "ihitable.h"

//---------------------------------------------------------------------//

class HitableList : public IHitable
{
public:
	// IHitable
	virtual bool			IsHit( const Math::Ray& Ray, float TMin, float TMax, HitRecord& HitRecord ) const;

	// HitableList
	HitableList();

	void					Append( IHitable* Hitable );
	void					Remove( UInt32_t Index );

private:
	std::vector< IHitable* >			array;
};

//---------------------------------------------------------------------//

#endif // !HITABLELIST_H
