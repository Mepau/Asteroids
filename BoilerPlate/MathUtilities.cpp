#include "MathUtilities.hpp"
#include "Constants.hpp"

namespace Engine
{
	namespace Math
	{
		float DegreesToRadians(float angleInRadians)
		{
			return angleInRadians * (PI / 180);
			
		}
		float RadiansToDegrees(float angleInDegrees)
		{
			return angleInDegrees * (180 / PI);
		}
	}
}
