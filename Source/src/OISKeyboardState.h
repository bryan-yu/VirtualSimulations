#pragma once

#include "Input.h"
#include "KeyboardState.h"
#include <vector>
#include <OISKeyboard.h>

namespace AABSEngine
{
	namespace Input
	{
		/**
		 * @class OISKeyboardState
		 *
		 * @brief 
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class OISKeyboardState: public KeyboardState
		{
		private:
			OIS::Keyboard* m_keyboard;
		protected:
			bool UpdateState();
		public:
			OISKeyboardState(OIS::Keyboard* keyboard);
			bool Update();
		};
	}
}