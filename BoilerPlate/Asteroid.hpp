#pragma once
#ifndef _ASTEROID_H_
#define _ASTEROID_H_

// STL
#include <vector>

// Asteroids
#include "Vector2.hpp"
#include "Entity.hpp"

namespace Asteroids
{
	namespace  Entities
	{
		class Asteroid : public Entity
		{
		public:
			/* =============================================================
			* ENUMERATORS
			* ============================================================= */
			struct AsteroidSize
			{
				enum Size
				{
					BIG = 0,
					MEDIUM = 1,
					SMALL = 2,
				};
			};

			/* =============================================================
			* PUBLIC FUNCTIONS
			* ============================================================= */
			explicit Asteroid(AsteroidSize::Size size, Engine::Math::Vector2 position = Engine::Math::Vector2::Origin);
			void Update(double deltaTime) override;
			void Render() override;
			void ApplyRandomTranslation() const;

			/* =============================================================
			* GETTER FUNCTIONS
			* ============================================================= */
			AsteroidSize::Size GetSize() const { return m_size; };
		private:
			/* =============================================================
			* PRIVATE FUNCTIONS
			* ============================================================= */
			void Generate();
			void ApplyRandomImpulse() const;

			/* =============================================================
			* MEMBERS
			* ============================================================= */
			std::vector<Engine::Math::Vector2> m_points;
			AsteroidSize::Size m_size;
			int m_sizeFactor;
		};
	}
}

#endif // !_ASTEROID_H_