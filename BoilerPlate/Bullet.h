#pragma once
#ifndef _ASTEROIDS_H_
#define _ASTEROIDS_H_

#include "Entity.hpp"
#include "Time.h"

namespace Asteroids
{
	namespace Entities
	{

		class Bullet : public Entity
		{
			public:

			Bullet();
			~Bullet();
			void Update(float deltaTime)override;
			void Render() override;
			void ApplyImpulse(Engine::Math::Vector2 pos, float angle);
			

			private:	

				std::vector<Engine::Math::Vector2> m_puntos;
				float m_velocidad;
				void Generate();
				clock_t creationTime;
				

		};

	}
}

#endif 
