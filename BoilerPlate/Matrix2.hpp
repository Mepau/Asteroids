#pragma once

#ifndef _MATRIX2_H_
#define _MATRIX2_H_

namespace Engine
{
	namespace Math
	{
		class Vector2;

		struct Matrix2
		{
			/* =============================================================
			* MEMBERS
			* ============================================================= */
			union
			{
				struct
				{
					float m00, m01;
					float m10, m11;
				};

				float m[2][2];
				float v[4];
			};

			/* =============================================================
			* PUBLIC FUNCTIONS
			* ============================================================= */
			Matrix2();
			Matrix2(float radians);
			Matrix2(float a, float b, float c, float d);
			void Set(float radians);
			Matrix2 Abs() const;
			Vector2 AxisX() const;
			Vector2 AxisY() const;
			Matrix2 Transpose() const;

			/* =============================================================
			* OPERATOR OVERLOADS
			* ============================================================= */
			Vector2 operator*(const Vector2& rhs) const;
			Matrix2 operator*(const Matrix2& rhs) const;
		};
	}
}

#endif // !_MATRIX2_H_