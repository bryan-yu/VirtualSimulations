#pragma once

#include "AffordanceEvaluator.h"
#include "Agent.h"
#include "AffordanceManager.h"

namespace AABSEngine
{
	namespace AI
	{
		/**
		* @class UrinateAffordanceEvaluator
		*
		* @brief Affordance evaluator for urination associated action
		*
		* @author AABS
		* @version X
		* @date October 2013
		*
		*/
		class UrinateAffordanceEvaluator : public AffordanceEvaluator
		{
		private:
		protected:
		public:
			UrinateAffordanceEvaluator();
			UrinateAffordanceEvaluator(std::string name);
			/**
			* @brief Evaluation based on initiating agent data and interactive object data
			* returns affordance value between 0 and 100
			*/
			int Evaluate(Agent* drinker, AABSEngine::Core::InteractiveObject* drinkee);
		};
	}
}