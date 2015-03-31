#pragma once

#include <string>
#include "State.h"
#include "Agent.h"

namespace AABSEngine
{
	namespace AI
	{
		/**
		* @class StateManager
		*
		* @brief Manages states
		*
		* @author AABS
		* @version X
		* @date October 2013
		*
		*/
		class StateManager
		{
		private:
		protected:
		public:
			StateManager();
			State<Agent>* GetState(std::string state);
		};
	}
}