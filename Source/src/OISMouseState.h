#pragma once

#include "Input.h"
#include "MouseState.h"
#include <vector>
#include <OISMouse.h>

namespace AABSEngine
{
	namespace Input
	{
		/**
		 * @class OISMouseState
		 *
		 * @brief 
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class OISMouseState: public MouseState
		{
		private:
			OIS::Mouse* m_mouse;
		protected:
			bool UpdateState();
		public:
			OISMouseState(OIS::Mouse* mouse);
			bool Update();
		};
	}
}