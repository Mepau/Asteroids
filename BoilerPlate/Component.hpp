#pragma once

#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <string>

//
#include "IUpdate.hpp"

namespace Engine
{
	namespace Core
	{
		class GameObject;
		class Component : IUpdate
		{
		public:
			/* =============================================================
			* PUBLIC FUNCTIONS
			* ============================================================= */
			explicit Component(const std::string& name);
			~Component();
			void Update(double deltaTime) override;

			/* =============================================================
			* GETTER FUNCTIONS
			* ============================================================= */
			void SetOwner(GameObject* owner) { m_owner = owner; }
			GameObject* GetOwner() const { return m_owner; }
			std::string GetName() const { return m_name; }
		protected:
			/* =============================================================
			* MEMBERS
			* ============================================================= */
			GameObject*	m_owner;
			std::string	m_name;
		};
	}	
}


#endif // !COMPONENT_HPP
