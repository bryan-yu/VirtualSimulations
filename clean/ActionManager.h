#pragma once

#include "BaseFactory.h"
#include "Action.h"

namespace AABSEngine
{
	namespace AI
	{
		/**
		* @class ActionManager
		*
		* @brief Interactive object action manager
		*
		* @author AABS
		* @version X
		* @date October 2013
		*
		*/
		class ActionManager
		{
		private:
			std::map<std::string, Action*> m_actions;
		protected:
		public:
			ActionManager();
			/**
			* @brief Initialises by reading actions from XML file
			*/
			bool Initialise();
			/**@brief Searches the map and creates a new object via m_Itr->second() which actually calls CreateRegis<AssignedType>
			**@return  NULL if no such object is found
			**@param id is the map key used to search for the item.
			**/
			Action* GetAction(std::string name);
		};
	}
}