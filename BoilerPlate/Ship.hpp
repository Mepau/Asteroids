#pragma once
#ifndef _SHIP_H_
#define _SHIP_H_

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
		class Ship : public Entity
		{
		public:
			/* =============================================================
			* CTOR
			* ============================================================= */
			explicit Ship(const std::vector<points_set> ships);
			~Ship();

			/* =============================================================
			* PUBLIC FUNCTIONS
			* ============================================================= */
			void MoveUp() const;
			void MoveRight() const;
			void MoveLeft() const;
			void ChangeShip();
			void Update(double deltaTime) override;
			void Render() override;
			void Respawn();
			void redLives() { lives--; }
			int getLives() { return lives; } 
			Bullet* Shoot() const;
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
			Engine::Math::Vector3 m_currentColor;
			int lives = 3;

		};
	}
}

#endif // !_SHIP_H_
