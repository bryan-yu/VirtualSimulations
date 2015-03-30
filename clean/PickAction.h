#pragma once

#include "InputCallback.h"
#include "Player.h"

namespace AABSEngine
{
	namespace Physics
	{
		class PhysicsManager;
	}

	namespace Core
	{
		class PickAction : public InputCallback<Player>
		{
		public:
			PickAction(Player& player) : InputCallback(player) {}

			void SetInternals(Physics::PhysicsManager* physMgr);

			void Begin();

			void Execute();

			void End();

		private:
			Physics::PhysicsManager* m_physManager;
		};
	}
}