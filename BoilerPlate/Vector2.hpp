#pragma once

#ifndef _VECTOR2_H_
#define _VECTOR2_H_

namespace Engine
{
	namespace Math
	{
		class Vector2
		{
		public:
			/* =============================================================
			* STATIC
			* ============================================================= */
			static Vector2 Origin;

			/* =============================================================
			* CTOR
			* ============================================================= */
			Vector2( );
			Vector2( float uniform );
			Vector2( float x, float y );

			/* =============================================================
			* PUBLIC FUNCTIONS
			* ============================================================= */
			float Length() const;
			float SquaredLength() const;
			float Vector2::Normalize();

			/* =============================================================
			* OPERATORS
			* ============================================================= */
			Vector2& operator=( const Vector2& rhs );
			Vector2& operator+=( const Vector2& rhs );
			Vector2& operator-=( const Vector2& rhs );
			Vector2& operator*=( const Vector2& rhs );
			Vector2& operator/=( const Vector2& rhs );
			Vector2 operator+( const Vector2& rhs ) const;
			Vector2 operator-( const Vector2& rhs ) const;
			Vector2 operator-( ) const;
			Vector2 operator*( const Vector2& rhs ) const;
			Vector2 operator/( const Vector2& rhs ) const;
			bool operator==(const Vector2& rhs) const;
			bool operator!=(const Vector2& rhs) const;
			friend Vector2 operator*(float scaleUnit, const Vector2& rhs);
			friend Vector2 operator*(const Vector2& lhs, float scaleUnit);

			/* =============================================================
			* MEMBERS
			* ============================================================= */
			float x;
			float y;
			float length;
		};
	}
}

#endif // !_VECTOR2_H_
