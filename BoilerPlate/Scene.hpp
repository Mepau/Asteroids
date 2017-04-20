#pragma once

#ifndef _SCENE_H_
#define _SCENE_H_

#include "Vector3.hpp"
#include "GameObject.hpp"

namespace Asteroids
{
	namespace Entities
	{
		class Scene : public Engine::Core::GameObject
		{
		public:
			/* =============================================================
			* CTOR
			* ============================================================= */
			Scene(Engine::Math::Vector3 background, int width, int height);

			/* =============================================================
			* PUBLIC FUNCTIONS
			* ============================================================= */
			void Render() override;

			/* =============================================================
			* GETTER FUNCTIONS
			* ============================================================= */
			int GetWidth() const { return m_width; }
			int GetHeight() const { return m_height; }
		private:
			/* =============================================================
			* MEMBERS
			* ============================================================= */
			Engine::Math::Vector3 m_background;
			int m_width;
			int m_height;
		};
	}
}

#endif // !_SCENE_H_