#pragma once

#include "Input.h"
#include "InputManager.h"
#include <string>
#include <memory>
#include <OISInputManager.h>

#include "OISMouseState.h"
#include "OISKeyboardState.h"

namespace AABSEngine
{
	namespace Input
	{
		/**
		 * @class AABSOISInputManager
		 *
		 * @brief 
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class AABSOISInputManager : public InputManager
		{
		private:
			OIS::InputManager* m_inputSystem;
		protected:
		public:
			AABSOISInputManager(std::string windowHandle);
			bool Update();
		};
	}
}