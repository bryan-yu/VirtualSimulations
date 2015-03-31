#pragma once

#include "State.h"
#include "Agent.h"

namespace AABSEngine
{
	namespace AI
	{
		/**
		* @class SocialiseState
		* 
		* @brief Agents socialising state
		*
		* @author AABS
		* @version X
		* @date October 2013
		*
		*/
		class SocialiseState: public State<Agent>
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