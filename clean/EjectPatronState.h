#pragma once

#include "State.h"
#include "Agent.h"

namespace AABSEngine
{
	namespace AI
	{
		/**
		* @class EjectPatronState
		* 
		* @brief Specific to security guard type agents, for ejecting drunk patron agents
		*
		* @author AABS
		* @version X
		* @date October 2013
		*
		*/
		class EjectPatronState: public State<Agent>
		{
		private:
		protected:
		public:
			/**
			* @brief Enter state
			*/
			virtual void Enter(Agent*);
			/**
			* @brief Execute state
			*/
			virtual void Execute(Agent*);
			/**
			* @brief Exit state
			*/
			virtual void Exit(Agent*);
		};
	}
}