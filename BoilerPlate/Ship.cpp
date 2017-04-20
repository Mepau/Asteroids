#include "Ship.hpp"
#include <SDL2\SDL_opengl.h>

//
#include <cmath>
#include "MathUtilities.hpp"
#include "Constants.hpp"

namespace Asteroids
{
	namespace Entities
	{
		const float ANGLE_OFFSET = 90.0f;
		const float THRUST = 3.0f;
		const float MAX_SPEED = 350.0f;
		const float BULLET_SPEED = 250.f;
		const float ROTATION_SPEED = 5.0f;
		const int RESTART_BLINK_FRAME_TIME = 30;
		const int RESPAWN_TIME = 120;
		const float max_ship_wide = 86;
		const float max_ship_height = 40;
		const float half_length = 568;
		const float half_height = 320;

		Ship::Ship(const std::vector<points_set> points)
			: m_ships(points)
			, m_currentIndex(0)
			, m_nRespawnTime(0)
			, m_pulse(false)
			, m_currentPulseCount(0)
			, m_totalPulseCount(30)
			, m_currentColor(Engine::Math::Vector3(1.0f))
		{
			m_radius = 15.0f;

			// Transforms
			//
			m_transforms = new Engine::Components::TransformationComponent();

			// Attaching transformation component
			//
			AttachComponent(m_transforms);

			// Physics
			//
			m_physics = new Engine::Components::RigidBodyComponent(
				Engine::Math::Vector2(0.0f),
				m_transforms->GetPosition(),
				1.0f,
				0.999f
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

		Ship::~Ship()
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


		void Ship::MoveUp() const
		{
			m_physics->ApplyForce(
				Engine::Math::Vector2(THRUST),
				m_transforms->GetAngleIRadians() + Engine::Math::DegreesToRadians(ANGLE_OFFSET)
			);
		}

		void Ship::MoveRight() const
		{
			m_transforms->RotateInDegrees(m_transforms->GetAngleInDegrees() - ROTATION_SPEED);
		}

		void Ship::MoveLeft() const
		{
			m_transforms->RotateInDegrees(m_transforms->GetAngleInDegrees() + ROTATION_SPEED);
		}

		void Ship::ChangeShip()
		{
			m_currentIndex++;
			if (m_currentIndex > (m_ships.size() - 1))
			{
				m_currentIndex = 0;
			}

			CalculateMass();
		}

		void Ship::Update(double deltaTime)
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

			Entity::Update(deltaTime);
		}

		void Ship::Render()
		{


			for (float count = 1; count <= lives; count++)
			{
				Entity::RenderLives(GL_LINE_LOOP,
					m_ships[m_currentIndex],
					Engine::Math::Vector3(1.0f),
					half_length - (max_ship_wide * count),
					half_height - (max_ship_height));
			}

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

			//Quick fix for enemy model filtering to player's ship model

			if (m_currentIndex == 0) m_currentIndex++;


			// Draw ship
			Entity::Render(GL_LINE_LOOP, m_ships[m_currentIndex], m_currentColor);
		}

		void Ship::Respawn()
		{
			SetCollision(false);
			m_pulse = true;
			m_currentColor = Engine::Math::Vector3(1.0f, 0.0f, 0.0f);
			m_transforms->Teleport(0.0f, 0.0f);
			m_transforms->ResetOrientation();
			m_physics->SetVelocity(Engine::Math::Vector2(0.f, 0.f));
			m_state = EntityState::RESPAWNING;
		}

		Bullet * Ship::Shoot() const
		{
			float shootingAngle = m_transforms->GetAngleInDegrees() + ANGLE_OFFSET;
			float speed = m_currentSpeed + BULLET_SPEED;

			return new Bullet(
				m_transforms->GetPosition(),
				Engine::Math::Vector2(speed),
				shootingAngle
			);
		}

		void Ship::CalculateMass()
		{
			// TODO: RR: Set the mass, proportional to the ship size (asumming points defines size)
			//
			m_physics->SetMass(m_ships[m_currentIndex].size() / 10.0f);
		}
	}
}
