#pragma once

#include "Agent.h"
#include "InteractiveObject.h"

namespace AABSEngine
{
	namespace AI
	{

		/**
		* @class ActionTrigger
		*
		* @brief Abstract class for handling interactive object actions
		*
		* @author AABS
		* @version X
		* @date October 2013
		*
		* @todo this would be a better system for triggering actions than using a map, but
		* time to implement is limited. For now we will use the existing needs method plus
		* an event blackboard with will can be checked by agents for relevant information 
		* before they assess their own needs
		*/
		class ActionTrigger
		{
		private:
		protected:
		public:
			ActionTrigger();
			
			/**
			* @brief Evaluation
			*/
			virtual void Evaluate(Agent* agent, AABSEngine::Core::InteractiveObject* object) = 0;
		};
	}
}