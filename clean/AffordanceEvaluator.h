#pragma once

#include <string>

namespace AABSEngine { namespace Core { class InteractiveObject; } }
namespace AABSEngine { namespace AI { class Agent; } }

namespace AABSEngine
{
	namespace AI
	{
		/**
		* @class AffordanceEvaluator
		*
		* @brief Base class for affordance evaluation
		*
		* @author AABS
		* @version X
		* @date October 2013
		*
		*/
		class AffordanceEvaluator
		{
		private:
			std::string m_name;
		protected:
		public:
			AffordanceEvaluator();
			AffordanceEvaluator(std::string name);
			/**
			* @brief Evaluation based on initiating agent data and interactive object data
			* returns affordance value between 0 and 100
			*/
			virtual int Evaluate(Agent* agent, AABSEngine::Core::InteractiveObject* obj) = 0;
			/**
			* @brief Returns name of evaluator
			*/
			std::string GetName() const;
			/**
			* @brief Sets name of evaluator
			*/
			void SetName(const std::string name);
		};
	}
}