#include "StdAfx.h"
#include "KeyboardState.h"

using namespace AABSEngine::Input;

bool KeyboardState::UpdateEvents()
{
	bool success = true;  

	/* examine states and fire events */
	for (int i = 0; i < NUM_KEYS; i++)
	{
		if (m_keyStates[i] != m_oldKeyStates[i])
		{
			events.insert(events.end(), KeyboardEvent((KeyboardKeys)i, m_keyStates[i] ? KEY_DOWN : KEY_UP, ON_PRESS));
		}
		else 
		{
			events.insert(events.end(), KeyboardEvent((KeyboardKeys)i, m_keyStates[i] ? KEY_DOWN : KEY_UP, ON_HOLD));
		}
	}

	return success;
}

bool KeyboardState::EventFired(KeyboardEvent kevent)
{
	for (std::vector<KeyboardEvent>::iterator it = events.begin(); it != events.end(); it++)
	{
		if (kevent == *it)
			return true;
	}
	return false;
}

void KeyboardState::ClearEvents()
{
	events.clear();
}