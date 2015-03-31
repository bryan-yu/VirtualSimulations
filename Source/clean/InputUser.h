#pragma once

#include <map>
#include "types.h"
#include "InputCallback.h"

namespace AABSEngine
{
	namespace Input
	{
		class InputManager;
	}

	namespace Core
	{
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
		template<class UserType>
		class InputUser
		{
		private:
			typedef std::map<const std::type_info*,AABSEngine::Core::InputCallback<UserType>*,Type_Info_Cmp> ActionMap;

			AABSEngine::Input::InputManager* m_inputManager;

			ActionMap m_actionMap;

		public:
			InputUser(AABSEngine::Input::InputManager* inputMgr = nullptr) : m_inputManager(inputMgr){}

			void SetInputManager(AABSEngine::Input::InputManager* inputMgr){ m_inputManager = inputMgr; }

			AABSEngine::Input::InputManager& GetInputManager(){ return *m_inputManager; }

			template<class ActionType>
			ActionType* AddAction();

			template<class ActionType>
			ActionType* GetAction();

			template<class ActionType>
			bool RemoveAction();

			virtual ~InputUser();

			void ClearActions();
		};
	}

}

template<class UserType>
template<class ActionType>
ActionType* AABSEngine::Core::InputUser<UserType>::AddAction()
{
	const std::type_info& info = typeid(ActionType);

	ActionMap::iterator itr = m_actionMap.find(&info);	

	if(itr == m_actionMap.end())
	{
		ActionType* action = new ActionType(dynamic_cast<UserType&>(*this));

		m_actionMap.insert(std::make_pair(&info,action));

		return action;
	}
	return NULL;
}

template<class UserType>
AABSEngine::Core::InputUser<UserType>::~InputUser()
{
	ClearActions();
}

template<class UserType>
void AABSEngine::Core::InputUser<UserType>::ClearActions()
{
	ActionMap::iterator itr = m_actionMap.begin();

	while(itr != m_actionMap.end())
	{
		delete itr->second;
		m_actionMap.erase(itr++);
	}
}

template<class UserType>
template<class ActionType>
ActionType* AABSEngine::Core::InputUser<UserType>::GetAction()
{
	const std::type_info& info = typeid(ActionType);

	ActionMap::iterator itr = m_actionMap.find(&info);
	
	if(itr != m_actionMap.end())
	{	
		return static_cast<ActionType*>(itr->second);
	}
	return NULL;
}

template<class UserType>
template<class ActionType>
bool AABSEngine::Core::InputUser<UserType>::RemoveAction()
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