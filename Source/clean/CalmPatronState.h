#pragma once

#include "State.h"
#include "Agent.h"

namespace AABSEngine
{
	namespace AI
	{
		/**
		* @class CalmPatronState
		*
		* @brief State of a patron agent while calm
		*
		* @author AABS
		* @version X
		* @date October 2013
		*
		*/
		class CalmPatronState: public State<Agent>
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