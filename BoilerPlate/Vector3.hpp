#pragma once

namespace Engine
{
	namespace Math
	{
		class Vector3
		{
		public:
			/* =============================================================
			* CTOR
			* ============================================================= */
			explicit Vector3();
			explicit Vector3(float uniform);
			explicit Vector3(float x, float y, float z);
			Vector3(const Vector3& other);

			/* =============================================================
			* PUBLIC FUNCTIONS
			* ============================================================= */
			float Normalize();
			float Length();
			float LengthSquared() const;
			void Scale(float scaleUnit);
			float SetLength(float newLength);

			/* =============================================================
			* MEMBERS
			* ============================================================= */
			float x;
			float y;
			float z;
			float length;
		};
	}
}