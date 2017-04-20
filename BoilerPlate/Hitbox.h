#pragma once
#ifndef _HITBOX_H_
#define _HITBOX_H_

#include "Component.hpp"
#include "Vector2.hpp"

namespace Engine
{
	namespace Components
	{

		class Hitbox : public Core::Component
		{

		public:
			Hitbox();
			~Hitbox();
			Hitbox(float radius);
			Hitbox(Math::Vector2 minValues, Math::Vector2 maxValues);
			//void Update(double deltaTime) override;
			void setMinvalues(Math::Vector2 newValues) { m_xMin = newValues.x; m_yMin = newValues.y;};
			void setMaxvalues(Math::Vector2 newValues){ m_xMax = newValues.x; m_yMax = newValues.y; };
			float getRadius() { return m_radius; }
			void setCenter(Math::Vector2 o_center) {};

		protected:

			bool isHit(Hitbox p_hitBox);

		private:
			float m_radius;
			float m_xMin = 0, m_xMax = 0;
			float m_yMin = 0, m_yMax = 0;


		};
	}

}
#endif // !_HITBOX_H_