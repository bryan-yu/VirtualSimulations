#pragma once

#include "State.h"
#include "Agent.h"

namespace AABSEngine
{
	namespace AI
	{
		/**
		* @class TidyState
		*
		* @brief Specific to bartender staff agents, for when 'cleaning' needs to be done
		*
		* @author AABS
		* @version X
		* @date October 2013
		*
		*/
		class TidyState: public State<Agent>
		{
		private:
		protected:
		public:
			/**
			* @brief Enter state
			*/
			virtual void Enter(Agent* agent);
			/**
			* @brief Execute state
			*/
			virtual void Execute(Agent* agent);
			/**
			* @brief Exit state
			*/
			virtual void Exit(Agent* agent);
		};
	}
}