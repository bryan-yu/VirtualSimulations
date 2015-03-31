#pragma once

#include "InputCallback.h"
#include "Player.h"

namespace AABSEngine
{
	namespace Input
	{
		class InputManager;
	}

	namespace Rendering
	{
		class MouseCursor;
	}

	namespace Core
	{
		class GameObject;

		/**
		* @class DrinkAction
		*
		* @brief Agents drinking beverages action
		*
		* @author AABS
		* @version X
		* @date October 2013
		*
		*/
		class DrinkAction : public InputCallback<Player>
		{
		public:
			DrinkAction(Player& player) : InputCallback(player){}

			void Begin();

			void Execute();

			void End();

			void SetInternals( AABSEngine::Rendering::MouseCursor* cursor);

		private:

			AABSEngine::Rendering::MouseCursor* m_cursorGraphic;
		};
	}
}