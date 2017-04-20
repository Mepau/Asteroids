#include "Vector2.hpp"
#include <cmath>

namespace Engine
{
	namespace Math
	{
		Vector2 Vector2::Origin = Vector2();

		Vector2::Vector2()
			: x( 0.0f )
			, y( 0.0f )
			, length( 0.0f )
		{}

		Vector2::Vector2(float uniform)
			: x(uniform)
			, y(uniform)
			, length( 0 )
		{
			// Calculate length for the given point
			//
			Length();
		}

		Vector2::Vector2(float x, float y)
			: x( x )
			, y( y )
			, length( 0 )
		{
			// Calculate length for the given point
			//
			Length();
		}

		float Vector2::Length() const
		{
			return std::sqrt(x * x + y * y);
		}

		float Vector2::SquaredLength() const
		{
			return x * x + y * y;
		}

		float Vector2::Normalize()
		{
			// Calculating the length
			Length();

			float inverseScale = 1.0f / length;
			x *= inverseScale;
			y *= inverseScale;

			return length;
		}

		// operators
		//
		Vector2& Vector2::operator=(const Vector2& rhs)
		{
			// Prevent self assignment. Two objects
			// are equal if their memory address are equal.
			if (this == &rhs)
			{
				return *this;
			}

			x = rhs.x;
			y = rhs.y;

			return *this;
		}

		Vector2& Vector2::operator+=(const Vector2& rhs)
		{
			x = x + rhs.x;
			y = y + rhs.y;

			return *this;
		}

		Vector2& Vector2::operator-=(const Vector2& rhs)
		{
			x = x - rhs.x;
			y = y - rhs.y;

			return *this;
		}

		Vector2& Vector2::operator*=(const Vector2& rhs)
		{
			x = x * rhs.x;
			y = y * rhs.y;

			return *this;
		}

		Vector2& Vector2::operator/=(const Vector2& rhs)
		{
			x = x / rhs.x;
			y = y / rhs.y;

			return *this;
		}

		Vector2 Vector2::operator+(const Vector2& rhs) const
		{
			Vector2 sum;

			sum.x = x + rhs.x;
			sum.y = y + rhs.y;

			return sum;
		}

		Vector2 Vector2::operator-(const Vector2& rhs) const
		{
			Vector2 sub;
			sub.x = x - rhs.x;
			sub.y = y - rhs.y;

			return sub;
		}

		Vector2 Vector2::operator-() const
		{
			return Vector2(-x, -y);
		}

		Vector2 Vector2::operator*(const Vector2& rhs) const
		{
			Vector2 scaled;

			scaled.y = y * rhs.y;
			scaled.x = x * rhs.x;

			return scaled;
		}

		Vector2 Vector2::operator/(const Vector2& rhs) const
		{
			Vector2 inverseScaled;

			inverseScaled.x = x / rhs.x;
			inverseScaled.y = y / rhs.y;

			return inverseScaled;
		}

		bool Vector2::operator==(const Vector2& rhs) const
		{
			return
				x == rhs.x &&
				y == rhs.y;
		}

		bool Vector2::operator!=(const Vector2& rhs) const
		{
			return
				x != rhs.x ||
				y != rhs.y;
		}

		// friend functions
		Vector2 operator*(float scaleUnit, const Vector2& rhs)
		{
			Vector2 scaled;
			scaled.x = scaleUnit * rhs.x;
			scaled.y = scaleUnit * rhs.y;

			return scaled;
		}

		Vector2 operator*(const Vector2& lhs, float scaleUnit)
		{
			Vector2 scaled;
			scaled.x = scaleUnit * lhs.x;
			scaled.y = scaleUnit * lhs.y;

			return scaled;
		}
	}
}