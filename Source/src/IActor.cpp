#include "StdAfx.h"
#include "IActor.h"


AABSEngine::Core::IActor::~IActor()
{
	ClearActions();
}

void AABSEngine::Core::IActor::ClearActions()
{
	ActionMap::iterator itr = m_actionMap.begin();

	while(itr != m_actionMap.end())
	{
		delete itr->second;

		m_actionMap.erase(itr++);
	}
}