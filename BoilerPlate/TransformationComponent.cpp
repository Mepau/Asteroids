#include "TransformationComponent.hpp"
#include "Constants.hpp"

namespace Engine
{
	namespace Components
	{
		const std::string COMP_NAME = "TRANSFORMATION_COMPONENT";

		TransformationComponent::TransformationComponent()
			: Component(COMP_NAME)
		    , m_angleInDegrees(0)
			, m_angleInRadians(0)
		{}

		TransformationComponent::TransformationComponent(Math::Vector2 position, float angleInDegrees)
			: Component(COMP_NAME)
		{
			Teleport(position);
			RotateInDegrees(angleInDegrees);
		}

		TransformationComponent::~TransformationComponent()
		{}

		void TransformationComponent::Teleport(float x, float y)
		{
			m_position.x = x;
			m_position.y = y;
		}

		void TransformationComponent::Teleport(Math::Vector2 newPosition)
		{
			m_position = newPosition;
		}
		void TransformationComponent::RotateInDegrees(float angle)
		{
			m_angleInDegrees = angle;
			m_angleInRadians = (angle) * (Math::PI / 180);
		}
		void TransformationComponent::RotateInRadians(float angle)
		{
			m_angleInRadians = angle;
			m_angleInDegrees = angle * (180 / Math::PI);
		}

		void TransformationComponent::ResetOrientation()
		{
			m_angleInDegrees = 0;
			m_angleInRadians = 0;
		}
	}
}
