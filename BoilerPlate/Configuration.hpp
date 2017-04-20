#pragma once
#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

//
#include <vector>

//
#include "Vector2.hpp"

namespace Asteroids
{
	namespace Utilities
	{
		class Configuration
		{
		public:
			std::vector<std::vector<Engine::Math::Vector2>> LoadModels() const;
		};
	}
}

#endif // !_CONFIGURATION_H_
