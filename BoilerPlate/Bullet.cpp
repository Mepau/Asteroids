#include "Bullet.hpp"

//
#include <SDL2/SDL_opengl.h>
#include "MathUtilities.hpp"

namespace  Asteroids
{
	namespace Entities
	{
		Bullet::Bullet(Engine::Math::Vector2 position, Engine::Math::Vector2 velocity, float angle, unsigned int maxFrameLifeTime)
			: m_frameLifeTime(0)
			, m_maxFrameLifeTime(maxFrameLifeTime)
		{
			m_radius = 1.0f;

			// Transforms
			//
			m_transforms = new Engine::Components::TransformationComponent();

			// Apply initial transforms
			//
			m_transforms->Teleport(position);

			// Attaching transformation component
			//
			AttachComponent(m_transforms);

			// Physics
			//
			m_physics = new Engine::Components::RigidBodyComponent(
				Engine::Math::Vector2(0.0f),
				m_transforms->GetPosition()
			);

			// Attaching physics component
			//
			AttachComponent(m_physics);

			// Apply initial velocity
			//
			m_physics->ApplyForce(
				velocity, 
				Engine::Math::DegreesToRadians(angle)
			);
		}

		void Bullet::Update(double deltaTime)
		{
			if(m_frameLifeTime > m_maxFrameLifeTime)
			{
				m_state = EntityState::DELETED;
				return;
			}

			// Update frame lifetime
			//
			m_frameLifeTime++;

			// Call update on base class
			//
			Entity::Update(deltaTime);
		}

		void Bullet::Render()
		{
			// TODO: RR: Move this out to a renderer
			//
			glLoadIdentity();

			glPointSize(2.0f);

			glEnable(GL_POINT_SMOOTH);

			glBegin(GL_POINTS);

			glVertex2f(m_transforms->GetPosition().x, m_transforms->GetPosition().y);

			glEnd();
		}
	}
}
