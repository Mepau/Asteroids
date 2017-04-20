#include "Hitbox.h"

#include "Math.h"

namespace Engine
{
	namespace Components
	{

		const std::string COMP_NAME = "HITBOX_COMPONENT";

		Hitbox::Hitbox()
			: Component(COMP_NAME)
		{}

		Hitbox::~Hitbox()
		{
		}

		Hitbox::Hitbox(float radius)
			: Component(COMP_NAME)
		{

			//Planteamiento de vertices de un cuadrado inscrito dado el radio

			float side, halfSide;
			m_radius = radius;

			side = sqrt(2 * radius);
			halfSide = side / 2;

			m_xMin = fabs(m_xMin- halfSide);
			m_yMin = fabs(m_yMin - halfSide);
			m_yMax = m_yMin - halfSide;
			m_yMax = m_yMax - halfSide;

		}

		// Constructor dado los valores exactos de los vertices
		Hitbox::Hitbox(Math::Vector2 minValues, Math::Vector2 maxValues)
			: Component(COMP_NAME)
		{
			m_xMin = minValues.x;
			m_xMax = maxValues.y;
			m_yMin = minValues.y;
			m_yMax = maxValues.y;
			
		}

		void Update(double deltaTime)
		{}

		bool Hitbox::isHit(Hitbox p_Hitbox)
		{
			bool isHitting = false;

			if ((p_Hitbox.m_xMin  >= m_xMin) && (p_Hitbox.m_xMax <= m_xMax))
			{
				if ((p_Hitbox.m_yMin >= m_yMin) && (p_Hitbox.m_yMax <= m_yMax))
				{
					isHitting = true;

					// Uncomment for 3d collision 
					//if ((p_Hitbox.m_zMin >= m_zMin) && (p_Hitbox.m_zMax <= m_zMax))
					//	isHitting = true;
				}
			}

			return isHitting;
		}

	}
}