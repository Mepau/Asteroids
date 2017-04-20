#pragma once

#ifndef INPUT_SYSTEM_HPP
#define INPUT_SYSTEM_HPP

#include <memory>

namespace Engine
{
	namespace Systems
	{
		class InputSystem
		{
		public:
			/* =============================================================
			* STATIC FUNCTIONS
			* ============================================================= */
			static void Create();
			static void Destroy();
			static InputSystem& Instance();

			/* =============================================================
			* PUBLIC FUNCTIONS
			* ============================================================= */
			bool IsKeyDown(unsigned char key);
			bool IsKeyUp(unsigned char key);
			void KeyDown(unsigned char key);
			void KeyUp(unsigned char key);
			void ResetInput();
		private:
			/* =============================================================
			* CTOR
			* ============================================================= */
			InputSystem();
			InputSystem(InputSystem const&) {};

			/* =============================================================
			* OPERATORS
			* ============================================================= */
			InputSystem& operator= (InputSystem const&) {};

			/* =============================================================
			* MEMBERS
			* ============================================================= */
			bool m_isDown[256];
			bool m_isUp[256];
			static std::unique_ptr< InputSystem > s_instance;
		};
	}
}

extern void OnKeyboardDownEvent(unsigned char key);
extern void OnKeyboardUpEvent(unsigned char key);

#endif // !INPUT_SYSTEM_HPP