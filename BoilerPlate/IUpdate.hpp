#ifndef _IUPDATE_H_
#define _IUPDATE_H_

namespace Engine
{
	namespace Core
	{
		class IUpdate
		{
		public:
			IUpdate() : m_nUpdates(0) {}
			virtual ~IUpdate() = default;

			/* =============================================================
			* PUBLIC FUNCTIONS
			* ============================================================= */
			void virtual Update(double deltaTime) { m_nUpdates++; };
		protected:
			/* =============================================================
			* MEMBERS
			* ============================================================= */
			int	m_nUpdates;
		};
	}
}

#endif // !IUPDATABLE_HPP#pragma once
