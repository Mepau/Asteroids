#pragma once

#ifndef _IRENDER_H_
#define _IRENDER_H_

namespace Engine
{
	namespace Core
	{
		class IRender
		{
		public:
			virtual ~IRender() = default;
			/* =============================================================
			* PUBLIC FUNCTIONS
			* ============================================================= */
			void virtual Render() = 0;
		};
	}
}

#endif // !_IRENDER_H_