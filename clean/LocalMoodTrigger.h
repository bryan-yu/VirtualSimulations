#pragma once

#include "ActionTrigger.h"

namespace AABSEngine
{
	namespace AI
	{
		class LocalMoodTrigger: public ActionTrigger
		{
		private:
		protected:
		public:
			LocalMoodTrigger();
			virtual void Evaluate(Agent* agent, AABSEngine::Core::InteractiveObject* object);
		};
	}
}