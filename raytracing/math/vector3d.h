#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <cmath>
#include <memory>
#include <iostream>

#include "common/types.h"

//---------------------------------------------------------------------//

namespace Math
{
	//---------------------------------------------------------------------//

	class Vector3D
	{
	public:

		//---------------------------------------------------------------------//

		friend std::istream&		operator>>( std::istream& Left, Vector3D& Right );
		friend std::ostream&		operator>>( std::ostream& Left, const Vector3D& Right );
		friend Vector3D				operator+( const Vector3D& Right, const Vector3D& Left );
		friend Vector3D				operator-( const Vector3D& Right, const Vector3D& Left );
		friend Vector3D				operator*( const Vector3D& Right, const Vector3D& Left );
		friend Vector3D				operator/( const Vector3D& Right, const Vector3D& Left );
		friend Vector3D				operator*( float Right, const Vector3D& Left );
		friend Vector3D				operator*( const Vector3D& Right, float Left );
		friend Vector3D				operator/( const Vector3D& Right, float Left );

		//---------------------------------------------------------------------//

		Vector3D()										
		{
			memset( value, 0, 3 * sizeof( float ) );
		}
		Vector3D( float X, float Y, float Z )
		{
			value[ 0 ] = X;
			value[ 1 ] = Y;
			value[ 2 ] = Z;
		}
		Vector3D( const Vector3D& Copy )
		{
			value[ 0 ] = Copy.value[ 0 ];
			value[ 1 ] = Copy.value[ 1 ];
			value[ 2 ] = Copy.value[ 2 ];
		}

		static inline float			Dot( const Vector3D& Left, const Vector3D& Right )
		{
			return Left.value[ 0 ] * Right.value[ 0 ] + Left.value[ 1 ] * Right.value[ 1 ] + Left.value[ 2 ] * Right.value[ 2 ];
		}
		static inline Vector3D		Cross( const Vector3D& Left, const Vector3D& Right )
		{
			return Vector3D( Left.value[ 1 ] * Right.value[ 2 ] - Left.value [ 2 ] * Right.value[ 1 ],
							 -( Left.value[ 0 ] * Right.value[ 2 ] - Left.value[ 2 ] * Right.value[ 0 ] ),
							 Left.value[ 0 ] * Right.value[ 1 ] - Left.value[ 1 ] * Right.value[ 0 ] );
		}
		static inline Vector3D		Normalize( const Vector3D& Vector )
		{
			return Vector / Vector.GetLength();
		}
		inline void					Normalize()
		{
			float		k = 1.f / GetLength();
			value[ 0 ] *= k;
			value[ 1 ] *= k;
			value[ 2 ] *= k;
		}

		inline void					Set( float X, float Y, float Z )
		{
			value[ 0 ] = X;
			value[ 1 ] = Y;
			value[ 2 ] = Z;
		}
		inline void					SetX( float X )									{ value[ 0 ] = X; }
		inline void					SetY( float Y )									{ value[ 1 ] = Y; }
		inline void					SetZ( float Z )									{ value[ 2 ] = Z; }

		inline float				GetX() const									{ return value[ 0 ]; }
		inline float				GetY() const									{ return value[ 1 ]; }
		inline float				GetZ() const									{ return value[ 2 ]; }
		inline float				GetLength() const
		{
			return std::sqrt( value[ 0 ] * value[ 0 ] + value[ 1 ] * value[ 1 ] + value[ 2 ] * value[ 2 ] );
		}
		inline float				GetSquaredLength() const
		{
			return value[ 0 ] * value[ 0 ] + value[ 1 ] * value[ 1 ] + value[ 2 ] * value[ 2 ];
		}

		inline const Vector3D&		operator+() const						{ return *this; }
		inline Vector3D				operator-() const						{ return Vector3D( -value[ 0 ], -value[ 1 ], -value[ 2 ] ); }
		inline float				operator[]( UInt32_t Index ) const		{ return value[ Index ]; }
		inline float&				operator[]( UInt32_t Index )			{ return value[ Index ]; }

		inline Vector3D&			operator+=( const Vector3D& Right )
		{
			value[ 0 ] += Right.value[ 0 ];
			value[ 1 ] += Right.value[ 1 ];
			value[ 2 ] += Right.value[ 2 ];
			return *this;
		}
		inline Vector3D&			operator-=( const Vector3D& Right )
		{
			value[ 0 ] -= Right.value[ 0 ];
			value[ 1 ] -= Right.value[ 1 ];
			value[ 2 ] -= Right.value[ 2 ];
			return *this;
		}
		inline Vector3D&			operator*=( const Vector3D& Right )
		{
			value[ 0 ] *= Right.value[ 0 ];
			value[ 1 ] *= Right.value[ 1 ];
			value[ 2 ] *= Right.value[ 2 ];
			return *this;
		}
		inline Vector3D&			operator/=( const Vector3D& Right )
		{
			value[ 0 ] /= Right.value[ 0 ];
			value[ 1 ] /= Right.value[ 1 ];
			value[ 2 ] /= Right.value[ 2 ];
			return *this;
		}
		inline Vector3D&			operator*=( float Right )
		{
			value[ 0 ] *= Right;
			value[ 1 ] *= Right;
			value[ 2 ] *= Right;
			return *this;
		}
		inline Vector3D&			operator/=( float Right )
		{
			value[ 0 ] /= Right;
			value[ 1 ] /= Right;
			value[ 2 ] /= Right;
			return *this;
		}

	private:
		float			value[ 3 ];
	};

	//---------------------------------------------------------------------//

	inline std::istream&		operator>>( std::istream& Left, Vector3D& Right )
	{
		Left >> Right.value[ 0 ] >> Right.value[ 1 ] >> Right.value[ 2 ];
		return Left;
	}
	inline std::ostream&		operator>>( std::ostream& Left, const Vector3D& Right )
	{
		Left << Right.value[ 0 ] << " " << Right.value[ 1 ] << " " << Right.value[ 2 ];
		return Left;
	}
	inline Vector3D				operator+( const Vector3D& Right, const Vector3D& Left )
	{
		return Vector3D( Right.value[ 0 ] + Left.value[ 0 ], Right.value[ 1 ] + Left.value[ 1 ], Right.value[ 2 ] + Left.value[ 2 ] );
	}
	inline Vector3D				operator-( const Vector3D& Right, const Vector3D& Left )
	{
		return Vector3D( Right.value[ 0 ] - Left.value[ 0 ], Right.value[ 1 ] - Left.value[ 1 ], Right.value[ 2 ] - Left.value[ 2 ] );
	}
	inline Vector3D				operator*( const Vector3D& Right, const Vector3D& Left )
	{
		return Vector3D( Right.value[ 0 ] * Left.value[ 0 ], Right.value[ 1 ] * Left.value[ 1 ], Right.value[ 2 ] * Left.value[ 2 ] );
	}
	inline Vector3D				operator/( const Vector3D& Right, const Vector3D& Left )
	{
		return Vector3D( Right.value[ 0 ] / Left.value[ 0 ], Right.value[ 1 ] / Left.value[ 1 ], Right.value[ 2 ] / Left.value[ 2 ] );
	}
	inline Vector3D				operator*( float Right, const Vector3D& Left )
	{
		return Vector3D( Right * Left.value[ 0 ], Right * Left.value[ 1 ], Right * Left.value[ 2 ] );
	}
	inline Vector3D				operator*( const Vector3D& Right, float Left )
	{
		return Vector3D( Left * Right.value[ 0 ], Left * Right.value[ 1 ], Left * Right.value[ 2 ] );
	}
	inline Vector3D				operator/( const Vector3D& Right, float Left )
	{
		return Vector3D( Right.value[ 0 ] / Left, Right.value[ 1 ] / Left, Right.value[ 2 ] / Left );
	}

	//---------------------------------------------------------------------//
}

//---------------------------------------------------------------------//

#endif // !VECTOR3D_H

