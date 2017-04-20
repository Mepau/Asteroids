#include "InputManager.hpp"

//
#include <algorithm>

namespace Engine
{
	namespace Input
	{
		InputManager* InputManager::s_instance = nullptr;

		InputManager::InputManager()
			: m_isKeyPressed(false)
		{
			// Initialize internal structures
			//
			std::generate(m_currentKeys, m_currentKeys + 256, []() { return false; });
			std::generate(m_previousKeys, m_previousKeys + 256, []() { return false; });
		}

		void InputManager::Update()
		{
			// Copy current keys to previous keys.
			//
			std::copy(m_currentKeys, m_currentKeys + KEYCOUNT, m_previousKeys);
		}

		void InputManager::Create()
		{
			if (!s_instance)
			{
				s_instance = new InputManager;
			}
		}

		void InputManager::Destroy()
		{
			if (s_instance)
			{
				// Delete the instance
				//
				delete s_instance;
				s_instance = nullptr;
			}
		}

		InputManager& InputManager::Instance()
		{
			if (!s_instance)
			{
				Create();
			}

			return *s_instance;
		}

		bool InputManager::IsKeyDown(unsigned char key)
		{
			return m_currentKeys[key];
		}

		bool InputManager::IsKeyReleased(unsigned char key) const
		{
			return (m_currentKeys[key] == false && m_previousKeys[key] == true);
		}

		void InputManager::KeyDown(unsigned char key)
		{
			m_currentKeys[key] = true;
		}

		bool InputManager::IsKeyPressed(unsigned char key)
		{
			return m_currentKeys[key];
		}

		void InputManager::KeyUp(unsigned char key)
		{
			m_previousKeys[key] = true;
			m_currentKeys[key] = false;
		}

		void InputManager::ResetInput()
		{
			std::generate(m_previousKeys, m_previousKeys + 256, []() { return false; });
		}
	}
}

void OnKeyboardDownEvent(unsigned char key)
{
	Engine::Input::InputManager::Instance().SetKeyPressed(true);
	Engine::Input::InputManager::Instance().KeyDown(key);
}

void OnKeyboardReleasedEvent(unsigned char key)
{
	Engine::Input::InputManager::Instance().SetKeyPressed(false);
	Engine::Input::InputManager::Instance().KeyUp(key);
}

void KeyboardPollEvent()
{
	Engine::Input::InputManager::Instance().Update();
}
