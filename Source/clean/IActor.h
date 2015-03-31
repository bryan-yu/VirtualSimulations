#pragma once

#include <map>
#include "types.h"

namespace AABSEngine
{
	namespace Core
	{
		class IAction;

		/**
		* @class IActor
		*
		* @brief 
		*
		* @author AABS
		* @version X
		* @date October 2013
		*
		*/
		class IActor
		{
		public:
			virtual ~IActor();

			template<class ActionType>
			ActionType* AddAction();

			template<class ActionType>
			ActionType* GetAction();

			template<class ActionType>
			bool RemoveAction();

			void ClearActions();

		protected:

			typedef std::map<const std::type_info*,AABSEngine::Core::IAction*,Type_Info_Cmp> ActionMap;

			ActionMap m_actionMap;
		};
	}

}

template<class ActionType>
ActionType* AABSEngine::Core::IActor::AddAction()
{
	const std::type_info& info = typeid(ActionType);

	ActionMap::iterator itr = m_actionMap.find(&info);	

	if(itr == m_actionMap.end())
	{
		ActionType* action = new ActionType();

		m_actionMap.insert(std::make_pair(&info,action));

		return action;
	}
	return NULL;
}

template<class ActionType>
ActionType* AABSEngine::Core::IActor::GetAction()
{
	const std::type_info& info = typeid(ActionType);

	ActionMap::iterator itr = m_actionMap.find(&info);
	
	if(itr != m_actionMap.end())
	{	
		return itr->second;
	}
	return NULL;
}

template<class ActionType>
bool AABSEngine::Core::IActor::RemoveAction()
{
	const std::type_info& info = typeid(ActionType);

	ActionMap::iterator itr = m_actionMap.find(&info);
	
	if(itr != m_actionMap.end())
	{
		m_actionMap.erase(itr);
		return true;
	}
	return false;
}