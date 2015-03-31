#pragma once

#include "Input.h"
#include <vector>

namespace AABSEngine
{
	namespace Input
	{
		/**
		 * @class MouseState
		 *
		 * @brief 
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class MouseState
		{
		private:
		protected:
			bool m_oldButtonStates[NUM_BUTTONS];
			bool m_buttonStates[NUM_BUTTONS];
			int m_x;
			int m_y;
			int m_deltax;
			int m_deltay;
			bool m_lockToPosition;
			int m_lockPositionX;
			int m_lockPositionY;

			std::vector<MouseButtonEvent> m_buttonEvents;
			bool m_mouseMoved;

			virtual bool UpdateState() = 0;
			bool UpdateEvents();
		public:
			int X();
			int DeltaX();
			int Y();
			int DeltaY();
			bool ButtonEventFired(MouseButtonEvent bevent);
			bool MovementEventFired();
			void ClearEvents();
			virtual bool Update() = 0;
		};
	}
}