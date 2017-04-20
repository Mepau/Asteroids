#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_

//
#include <vector>

//
#include "Vector2.hpp"
#include "Entity.hpp"
#include "Bullet.hpp"

typedef std::vector<Engine::Math::Vector2> points_set;

namespace Asteroids
{
	namespace Entities
	{
		class Enemy : public Entity
		{
		public:
			/* =============================================================
			* CTOR
			* ============================================================= */
			explicit Enemy(const std::vector<points_set> ships);
			~Enemy();

			/* =============================================================
			* PUBLIC FUNCTIONS
			* ============================================================= */
			void Move() const;
			void Update(double deltaTime) override;
			void Render() override;
			void Respawn();
			bool isDestroyed() { return destroyed; }
			void Respawned() { destroyed = false; }
			void Destroyed() { destroyed = true; }
			Bullet* Shoot(Engine::Math::Vector2 playerPosition) const;
		private:
			void CalculateMass();
			/* =============================================================
			* MEMBERS
			* ============================================================= */
			std::vector<points_set> m_ships;
			float m_currentSpeed;
			unsigned int m_currentIndex;
			int m_nRespawnTime;
			bool m_pulse = false;
			int  m_currentPulseCount;
			int  m_totalPulseCount;
			bool destroyed = false;
			Engine::Math::Vector3 m_currentColor;

		};
	}
}

#endif // !_ENEMY_H_