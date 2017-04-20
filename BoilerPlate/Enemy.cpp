#include "Enemy.h"
#include <SDL2\SDL_opengl.h>

//
#include <cmath>
#include <math.h>
#include "MathUtilities.hpp"
#include "Constants.hpp"
#include <time.h>


namespace Asteroids
{
	namespace Entities
	{
		const float ANGLE_OFFSET = 90.0f;
		const float THRUST = 3.0f;
		const float MAX_SPEED = 200.0f;
		const float BULLET_SPEED = 250.f;
		const float ROTATION_SPEED = 5.0f;
		const int RESTART_BLINK_FRAME_TIME = 30;
		const int RESPAWN_TIME = 120;
		const float neg_half_width = -1136 / 2;

		Enemy::Enemy(const std::vector<points_set> points)
			: m_ships(points)
			, m_currentIndex(0)
			, m_nRespawnTime(0)
			, m_pulse(false)
			, m_currentPulseCount(0)
			, m_totalPulseCount(30)
			, m_currentColor(Engine::Math::Vector3(1.0f))
		{
			m_radius = 5.0f;

			srand(time(NULL));

			// Creating random position.
			float random_yPos =(rand() % 320) * pow(-1, rand());

			Engine::Math::Vector2 newpos(neg_half_width, random_yPos);
			// Transforms
			//
			m_transforms = new Engine::Components::TransformationComponent(newpos, 0.0f);

			// Attaching transformation component
			//
			AttachComponent(m_transforms);

			// Physics
			//
			m_physics = new Engine::Components::RigidBodyComponent(
				Engine::Math::Vector2(0.0f),
				m_transforms->GetPosition(),
				1.0f,
				1.0f
			);

			// Attaching physics component
			//
			AttachComponent(m_physics);

			// Trigger mass calculation
			//
			CalculateMass();

			//Attaching Hitbox Component

			m_hitbox = new Engine::Components::Hitbox(m_radius);

			AttachComponent(m_hitbox);
		}

		Enemy::~Enemy()
		{
			// Clear points allocation per model
			//
			for (auto model : m_ships)
			{
				model.clear();
			}

			// Clear ships collection
			//
			m_ships.clear();
		}


		void Enemy::Move() const
		{
			m_physics->ApplyDiagForce(
				Engine::Math::Vector2(THRUST),
				m_transforms->GetAngleIRadians() + Engine::Math::DegreesToRadians(ANGLE_OFFSET)
			);
		}

		void Enemy::Update(double deltaTime)
		{
			// Clamp speed
			//
			m_currentSpeed = fabs(m_physics->GetSpeed());
			if (m_currentSpeed > MAX_SPEED)
			{
				m_physics->SetVelocity(
					Engine::Math::Vector2(
					(m_physics->GetVelocity().x / m_currentSpeed) * MAX_SPEED,
						(m_physics->GetVelocity().y / m_currentSpeed) * MAX_SPEED
					)
				);

				m_currentSpeed = MAX_SPEED;
			}

			Move();

			Entity::Update(deltaTime);
		}

		void Enemy::Render()
		{
			if (!m_canCollide)
			{
				if (m_nRespawnTime >= RESPAWN_TIME)
				{
					SetCollision(true);
					m_state = EntityState::NORMAL;
					m_nRespawnTime = 0;
					m_pulse = false;
					m_currentColor = Engine::Math::Vector3(1.0f);
				}

				m_nRespawnTime++;

				if (m_pulse)
				{
					// Pulsing, skip draw frames for a small amount of time
					if (m_totalPulseCount > m_currentPulseCount)
					{
						m_currentPulseCount++;
						return;
					}

					// Pulsing, reset pulse after a small amount of time
					// this will allow for blinking to be spaced and smooth
					if (m_nUpdates % RESTART_BLINK_FRAME_TIME == 0)
					{
						m_currentPulseCount = 0;
					}
				}
			}

			// Draw ship
			Entity::Render(GL_LINE_LOOP, m_ships[m_currentIndex], m_currentColor);


		}

		void Enemy::Respawn()
		{
			SetCollision(false);
			m_pulse = true;
			m_currentColor = Engine::Math::Vector3(1.0f, 0.0f, 0.0f);
			m_transforms->Teleport(0.0f, 0.0f);
			m_transforms->ResetOrientation();
			m_physics->SetVelocity(Engine::Math::Vector2(0.f, 0.f));
			m_state = EntityState::RESPAWNING;
		}

		Bullet * Enemy::Shoot(Engine::Math::Vector2 playerPosition) const
		{

			float shootingAngle = (float)(atan2f(playerPosition.y - m_transforms->GetPosition().y,
				playerPosition.x - m_transforms->GetPosition().x) * 180) / Engine::Math::PI;

			if (shootingAngle < 0) shootingAngle += 360;

			float speed = m_currentSpeed + BULLET_SPEED;

			return new Bullet(
				m_transforms->GetPosition(),
				Engine::Math::Vector2(speed),
				shootingAngle
			);
		}

		void Enemy::CalculateMass()
		{
			// TODO: RR: Set the mass, proportional to the ship size (asumming points defines size)
			//
			m_physics->SetMass(m_ships[m_currentIndex].size() / 10.0f);
		}

	}
}
