#pragma once

#include <string>
#include "Blackboard.h"
#include "InteractiveObject.h"

namespace AABSEngine
{
  namespace AI
  {
		/**
		* @struct ActionBlackboardEntry
		* @brief data structure for blackboard entry
		*
		*/
    struct ActionBlackboardEntry
    {
      std::string m_action;
      std::string m_actionertype;
      AABSEngine::Core::InteractiveObject* m_object;
	  bool m_locked;
      ActionBlackboardEntry(std::string action, std::string actionertype, AABSEngine::Core::InteractiveObject* object) : m_action(action), m_actionertype(actionertype), m_object(object), m_locked(false) { }
    };

    class ActionBlackboard: public AABSEngine::AI::Blackboard<ActionBlackboardEntry>
    {
    private:
    protected:
    public:
      ActionBlackboard() { }
      ActionBlackboardEntry* GetEntryFromAction(std::string action);
      ActionBlackboardEntry* GetEntryFromActionerType(std::string actioner);
	  ActionBlackboardEntry* GetEntryFromActionObject(std::string action, AABSEngine::Core::InteractiveObject* m_object);
      void DeleteEntry(ActionBlackboardEntry* entry);

	  /**
	   * @brief check if an entry with specified parameters already exist
	   */
	  bool EntryExist(std::string action, std::string actionertype, AABSEngine::Core::InteractiveObject* object);
    };
  }
}