#include "RigidBodyComponent.hpp"

namespace Engine
{
	namespace Components
	{
		const std::string COMP_NAME = "PHYSICS_COMPONENT";
		RigidBodyComponent::RigidBodyComponent()
			: Component(COMP_NAME)
			, m_gravity(0.0f, 0.0f)
			, m_position(0.0f, 0.f)
			, m_mass(1.0f)
			, m_drag(1.0f)
		{}

		RigidBodyComponent::RigidBodyComponent(Math::Vector2 gravity, Math::Vector2 position, float mass, float drag)
			: Component(COMP_NAME)
			, m_mass(mass)
			, m_drag(drag)
			, m_position(position)
			, m_gravity(gravity)
		{}

		RigidBodyComponent::~RigidBodyComponent()
		{}

		void RigidBodyComponent::ApplyDiagForce(const Math::Vector2 force, float angleInRadians)
		{
			if (m_mass > 0)
			{
				float x = (force.x / m_mass);
				float y = (force.y / m_mass) * (sinf(angleInRadians) / 2);

				m_velocity += Math::Vector2(x, y);
			}
		}
		void RigidBodyComponent::Update(double deltaTime)
		{
			// Apply acceleration
			//
			m_velocity += m_gravity;

			// Apply drag
			//
			m_velocity *= m_drag;

			// Base class function call
			//
			Component::Update(deltaTime);
		}

		void RigidBodyComponent::ApplyForce(const Math::Vector2 force, float angleInRadians)
		{
			if (m_mass > 0)
			{
				float x = (force.x / m_mass) * cosf(angleInRadians);
				float y = (force.y / m_mass) * sinf(angleInRadians);

				m_velocity += Math::Vector2(x, y);
			}
		}
	}
}