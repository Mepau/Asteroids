#include "Scene.hpp"

#include <SDL2/SDL_opengl.h>

namespace Asteroids
{
	namespace Entities
	{
		Scene::Scene(Engine::Math::Vector3 background, int width, int height)
			: m_background(background)
			, m_width(width)
			, m_height(height)
		{}
		void Scene::Render()
		{
			// TODO: RR: Move this to renderer class
			//
			glClearColor(m_background.x,
				m_background.y,
				m_background.z,
				1.0f);

			glClear(GL_COLOR_BUFFER_BIT);

			// Call render in base class
			//
			GameObject::Render();
		}
	}
}