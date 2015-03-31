#include "StdAfx.h"

#include "ActionBlackboard.h"

using namespace AABSEngine::AI;

ActionBlackboardEntry* ActionBlackboard::GetEntryFromAction(std::string action)
{
  ActionBlackboardEntry* entry;
  Blackboard::IndexFirstEntry();
  while(Blackboard::GetNextEntry(&entry))
  {
    if (entry->m_action == action)
      return entry;
  }
  return NULL;
}

ActionBlackboardEntry* ActionBlackboard::GetEntryFromActionerType(std::string actioner)
{
  ActionBlackboardEntry* entry = NULL;
  Blackboard::IndexFirstEntry();
  while(Blackboard::GetNextEntry(&entry))
  {
    if (entry)
      if (entry->m_actionertype == actioner)
        return entry;
  }
  return NULL;
}

ActionBlackboardEntry* ActionBlackboard::GetEntryFromActionObject(std::string action, AABSEngine::Core::InteractiveObject* object)
{
	ActionBlackboardEntry* entry = NULL;
	Blackboard::IndexFirstEntry();
	while(Blackboard::GetNextEntry(&entry))
	{
		if (entry)
		{
			//check against action and object
			if (entry->m_action == action && entry->m_object == object)
			{
				return entry;
			}
		}
	}
	return NULL;
}

void ActionBlackboard::DeleteEntry(ActionBlackboardEntry* entry)
{
  Blackboard::RemoveEntry(entry);
}

bool ActionBlackboard::EntryExist(std::string action, std::string actionertype, AABSEngine::Core::InteractiveObject* object)
{
	std::vector<ActionBlackboardEntry*> entries = Blackboard::GetItemList();
	for(int i=0; i<entries.size(); i++)
	{
		ActionBlackboardEntry *entry = entries[i];
		if(entry->m_action == action && entry->m_actionertype == actionertype && entry->m_object == object)
		{
			return true;
		}
	}

	return false;
}