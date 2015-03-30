#pragma once

#include "AffordanceEvaluator.h"
#include "Agent.h"
#include "AffordanceManager.h"

namespace AABSEngine
{
	namespace AI
	{
		/**
		* @class DrinkAffordanceEvaluator
		*
		* @brief Affordance evaluator for drinking associated action
		*
		* @author AABS
		* @version X
		* @date October 2013
		*
		*/
		class DrinkAffordanceEvaluator : public AffordanceEvaluator
		{
		private:
		protected:
		public:
			DrinkAffordanceEvaluator();
			DrinkAffordanceEvaluator(std::string name);
			/**
			* @brief Evaluation based on initiating agent data and interactive object data
			* returns affordance value between 0 and 100
			*/
			int Evaluate(Agent* drinker, AABSEngine::Core::InteractiveObject* drinkee);
		};
	}
}