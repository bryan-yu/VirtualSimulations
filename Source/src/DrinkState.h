#pragma once

#include "Agent.h"
#include "State.h"

namespace AABSEngine
{
	namespace AI
	{	
		/**
		* @class DrinkState
		* 
		* @brief Agent beverage consumption state
		*
		* @author AABS
		* @version X
		* @date October 2013
		*
		*/
		class DrinkState : public State<Agent>
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