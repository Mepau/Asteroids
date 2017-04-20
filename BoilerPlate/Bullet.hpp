#pragma once

#ifndef _BULLET_H_
#define _BULLET_H_

#include "Entity.hpp"

namespace  Asteroids
{
	namespace Entities
	{
		class Bullet : public Entity
		{
		public:
			/* =============================================================
			* CTOR
			* ============================================================= */
			Bullet(Engine::Math::Vector2 position, Engine::Math::Vector2 velocity, float angle, unsigned int maxFrameLifeTime = 120);

			/* =============================================================
			* PUBLIC FUNCTIONS
			* ============================================================= */
			void Update(double deltaTime) override;
			void Render() override;
		private:
			/* =============================================================
			* MEMBERS
			* ============================================================= */
			unsigned int m_frameLifeTime;
			unsigned int m_maxFrameLifeTime;
		};
	}
}

#endif // !_BULLET_H_