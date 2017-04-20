#pragma once
#ifndef _UNIQUEID_H_

namespace Engine
{
	namespace Core
	{
		class UniqueID
		{
		public:
			/* =============================================================
			* CTOR
			* ============================================================= */
			UniqueID();
			UniqueID(const UniqueID& orig);

			/* =============================================================
			* OPERATORS
			* ============================================================= */
			UniqueID& operator=(const UniqueID& orig);

			/* =============================================================
			* MEMBERS
			* ============================================================= */
			int id;
		protected:
			static int nextID;
		};
	}
}

#endif // !_UNIQUEID_H_