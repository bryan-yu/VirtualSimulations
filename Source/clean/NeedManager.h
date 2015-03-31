#pragma once

#include <map>
#include <string>
#include "Need.h"

namespace AABSEngine
{
	namespace AI
	{
		/**
		* @class NeedManager
		*
		* @brief Manages needs system for agents
		*
		* @author AABS
		* @version X
		* @date October 2013
		*
		*/
		class NeedManager
		{
		private:
			std::map<std::string, NeedDefinition> m_needDefinitions;
		protected:
		public:
			NeedManager();
			/**
			* @brief Initialisation
			*/
			bool Initialise();
			/**
			* @brief Add need to system
			*/
			void AddNeed(NeedDefinition needdef);
			/**
			* @brief Return specified need
			*/
			Need* GetNeed(std::string name);
		};
	}
}