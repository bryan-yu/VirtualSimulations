#pragma once

#include "AffordanceEvaluator.h"
#include "Agent.h"
#include "AffordanceManager.h"

namespace AABSEngine
{
	namespace AI
	{
		/**
		* @class SocialiseAffordanceEvaluator
		*
		* @brief Affordance evaluator for socilaising associated action
		*
		* @author AABS
		* @version X
		* @date October 2013
		*
		*/
		class SocialiseAffordanceEvaluator : public AffordanceEvaluator
		{
		private:
		protected:
		public:

			SocialiseAffordanceEvaluator();
			SocialiseAffordanceEvaluator(std::string name);
			/**
			* @brief Evaluation based on initiating agent data and interactive object data
			* returns affordance value between 0 and 100
			*/
			int Evaluate(Agent* socialiser, AABSEngine::Core::InteractiveObject* socialisee);
		};
	}
}