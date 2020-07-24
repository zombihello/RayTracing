#include "hitablelist.h"

// ------------------------------------------------------------------------------------ //
// Is hit
// ------------------------------------------------------------------------------------ //
bool HitableList::IsHit( const Math::Ray& Ray, float TMin, float TMax, HitRecord& HitRecord ) const
{
	::HitRecord			hitRecord;
	bool				result = false;
	double				clossetSoFar = TMax;

	for ( UInt32_t index = 0, count = array.size(); index < count; ++index )
	{
		IHitable*		hitable = array[ index ];
		if ( hitable->IsHit( Ray, TMin, clossetSoFar, hitRecord ) )
		{
			result = true;
			clossetSoFar = hitRecord.t;
			HitRecord = hitRecord;
		}
	}

	return result;
}

// ------------------------------------------------------------------------------------ //
// Constructor
// ------------------------------------------------------------------------------------ //
HitableList::HitableList()
{}

// ------------------------------------------------------------------------------------ //
// Append hitable object
// ------------------------------------------------------------------------------------ //
void HitableList::Append( IHitable* Hitable )
{
	if ( !Hitable )	return;
	array.push_back( Hitable );
}

// ------------------------------------------------------------------------------------ //
// Remove hitable object
// ------------------------------------------------------------------------------------ //
void HitableList::Remove( UInt32_t Index )
{
	if ( Index >= array.size() ) return;
	array.erase( Index + array.begin() );
}
