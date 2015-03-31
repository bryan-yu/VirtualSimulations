#include "StdAfx.h"
#include "MouseState.h"

using namespace AABSEngine::Input;

bool MouseState::UpdateEvents()
{
  bool success = true;  

  /* examine states and fire events */
  for (int i = 0; i < NUM_BUTTONS; i++)
  {
    if (m_buttonStates[i] != m_oldButtonStates[i])
    {
      m_buttonEvents.insert(m_buttonEvents.end(), MouseButtonEvent((MouseButtons)i, m_buttonStates[i] ? BUTTON_DOWN : BUTTON_UP, BUTTON_ON_PRESS));
    }
	else
	{
	  m_buttonEvents.insert(m_buttonEvents.end(), MouseButtonEvent((MouseButtons)i, m_buttonStates[i] ? BUTTON_DOWN : BUTTON_UP, BUTTON_ON_HOLD));
	}
  }

  if (m_deltax != 0 && m_deltay != 0)
    m_mouseMoved = true;

  return success;
}

int MouseState::X()
{
	return m_x;
}

int MouseState::DeltaX()
{
	return m_deltax;
}

int MouseState::Y()
{
	return m_y;
}

int MouseState::DeltaY()
{
	return m_deltay;
}

bool MouseState::ButtonEventFired(MouseButtonEvent bevent)
{
	for (std::vector<MouseButtonEvent>::iterator it = m_buttonEvents.begin(); it != m_buttonEvents.end(); it++)
	{
		if (bevent == *it)
		return true;
	}
	return false;
}

bool MouseState::MovementEventFired()
{
	if (m_mouseMoved)
		return true;
	return false;
}

void MouseState::ClearEvents()
{
  m_buttonEvents.clear();
  m_mouseMoved = false;
}