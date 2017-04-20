#include "Entity.hpp"

//
#include <SDL2/SDL_opengl.h>

//
#include "Scene.hpp"
#include "RigidBodyComponent.hpp"
#include "TransformationComponent.hpp"
#include "Hitbox.h"

namespace Asteroids
{
	namespace Entities
	{
		inline float wrap(float axis, float min, float max)
		{
			if (axis < min)
			{
				return max - (min - axis);
			}

			if (axis > max)
			{
				return min + (axis - max);
			}

			return axis;
		}

		Entity::Entity()
			: m_transforms(nullptr)
			, m_physics(nullptr)
			, m_radius(0)
			, m_canCollide(false)
			, m_sceneHalfWidth(0)
			, m_sceneHalfHeight(0)
			, m_state(EntityState::NORMAL)
		{}

		void Entity::Update(double deltaTime)
		{
			if (!GetParent()) return;

			Scene* scene = dynamic_cast<Scene*>(GetParent());
			if (!scene) return;

			m_sceneHalfWidth = (scene->GetWidth() / 2.0f);
			m_sceneHalfHeight = (scene->GetHeight() / 2.0f);

			if (!m_physics || !m_transforms) return;

			// Time stepping the position
			//
			Engine::Math::Vector2 newPos(
				m_transforms->GetPosition().x + (m_physics->GetVelocity().x * static_cast<float>(deltaTime)),
				m_transforms->GetPosition().y + (m_physics->GetVelocity().y * static_cast<float>(deltaTime))
			);

			// Getting axis limits
			//
			float worldMinX = -m_sceneHalfWidth;
			float worldMaxX = m_sceneHalfWidth;

			float worldMinY = -m_sceneHalfHeight;
			float worldMaxY = m_sceneHalfHeight;

			// Wrap!
			float x = wrap(newPos.x, worldMinX, worldMaxX);
			float y = wrap(newPos.y, worldMinY, worldMaxY);

			// Set the new position
			m_transforms->Teleport(x, y);

			// Base update
			//
			GameObject::Update(deltaTime);
		}

		void Entity::Render(unsigned int mode, std::vector<Engine::Math::Vector2> points, Engine::Math::Vector3 color)
		{
			Engine::Components::TransformationComponent* transforms = GetComponent<Engine::Components::TransformationComponent>();
			if (!transforms) return;

			// Reset transformation matrix to identity
			//
			glLoadIdentity();

			// Translate
			//
			glTranslatef(transforms->GetPosition().x, transforms->GetPosition().y, 0.0f);

			// Rotate
			//
			glRotatef(transforms->GetAngleInDegrees(), 0.0f, 0.0f, 1.0f);

			// Change color
			//
			glColor3f(color.x, color.y, color.z);

			// Draw
			//


			glBegin(mode);
			for (auto point : points)
			{
				glVertex2f(point.x, point.y);
			}
			glEnd();

			GameObject::Render();
		}

		void Entity::RenderLives(unsigned int mode, std::vector<Engine::Math::Vector2> points, Engine::Math::Vector3 color, float xPos, float yPos)
		{
			// Reset transformation matrix to identity
			//
			glLoadIdentity();

			// Translate
			//
			glTranslatef(xPos, yPos, 0.0f);

			// Rotate
			//
			glRotatef(0.0f, 0.0f, 0.0f, 1.0f);

			// Change color
			//
			glColor3f(color.x, color.y, color.z);

			// Draw
			//
			glBegin(mode);
			for (auto point : points)
			{
				glVertex2f(point.x, point.y);
			}
			glEnd();

			GameObject::Render();

		}

		bool Entity::IntersectsWith(Entity * rhs)
		{
			// TODO: RR: Move this check out to the rigid body component
			//
			Engine::Components::TransformationComponent* t_rhs =
				rhs->GetComponent<Engine::Components::TransformationComponent>();

			if (!rhs) return false;
			if (!t_rhs) return false;


			//Circles based intersects
			float x = m_transforms->GetPosition().x - t_rhs->GetPosition().x;
			float y = m_transforms->GetPosition().y - t_rhs->GetPosition().y;

			float radii = m_radius + rhs->m_radius;
			float distSquared = x * x + y * y;

			bool intersects = radii * radii >= distSquared;

			//Update entity state

			if (intersects) m_state = EntityState::COLLIDED;




		}
	}
}
