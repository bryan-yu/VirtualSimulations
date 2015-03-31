#pragma once

#include "Input.h"
#include <vector>

namespace AABSEngine
{
	namespace Input
	{
		/**
		 * @class KeyboardState
		 *
		 * @brief 
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class KeyboardState
		{
		private:
		protected:
			bool m_oldKeyStates[NUM_KEYS];
			bool m_keyStates[NUM_KEYS];
			std::vector<KeyboardEvent> events;

			virtual bool UpdateState() = 0;
			bool UpdateEvents();
		public:
			bool EventFired(KeyboardEvent kevent);
			void ClearEvents();
			virtual bool Update() = 0;
		};
	}
}