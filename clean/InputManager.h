#pragma once

#include "Input.h"
#include "MouseState.h"
#include "KeyboardState.h"
#include <memory>
#include <map>
#include <vector>
#include "../resources/include/boost/bind.hpp"
#include "../resources/include/boost/function.hpp"

namespace AABSEngine
{
	namespace Input
	{
		/** @class InputManager
		 * @brief This is an abstract class which defines the functionality required of input system specific classes.
		 * @author Samuel Steere
		 * @version 1.0
		 */
		class InputManager
		{

		protected:
			virtual void ProcessMouseCallbackEvents();
			virtual void ProcessKeyboardCallbackEvents();

			bool m_interruptedKbIt;
			bool m_interruptedMsIt;

			std::map<KeyboardEvent*, boost::function<void ()> >::iterator m_kbIt;
			std::map<MouseButtonEvent*, boost::function<void (int, int)> >::iterator m_msIt;

			std::shared_ptr<KeyboardState> m_keyboardState; /**< Pointer to a keyboard */
			std::shared_ptr<MouseState> m_mouseState; /**< Pointer to mouse */

			std::map<KeyboardEvent*, boost::function<void ()> > m_keyboardCallbacks;
			std::map<MouseButtonEvent*, boost::function<void (int, int)> > m_mouseButtonCallbacks;
			std::vector<boost::function<void (int, int)> > m_mouseMovementCallbacks;

			std::map<KeyboardEvent*, boost::function<void ()> >::iterator Find(const KeyboardEvent& kbEvent);
			std::map<MouseButtonEvent*, boost::function<void (int, int)> >::iterator Find(const MouseButtonEvent& mbEvent);

			void ResetInterruptedIteratorFlags();

		public:
			~InputManager();

			InputManager();

			bool Update();

			void Register(KeyboardEvent* kevent, boost::function<void ()> func);
			void Register(MouseButtonEvent* kevent, boost::function<void(int, int)> func);
			void Register(boost::function<void (int, int)> func);

			void DeRegister(const KeyboardEvent& kevent);
			void DeRegister(const MouseButtonEvent& kevent);

			void DeRegister(boost::function<void (int, int)> func);

			void Clear();

			//## TEMP to be removed
			std::shared_ptr<MouseState> GetMouseState() { return m_mouseState; }
		};
	}
}