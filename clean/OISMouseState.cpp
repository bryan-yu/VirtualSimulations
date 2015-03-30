#include "StdAfx.h"
#include "OISMouseState.h"
#include <iostream>

using namespace AABSEngine::Input;

OISMouseState::OISMouseState(OIS::Mouse* mouse)
{
	m_mouse = mouse;
	m_x = 0;
	m_y = 0;
	m_lockPositionX = 0;
	m_lockPositionY = 0;
}

bool OISMouseState::UpdateState()
{
	bool success = true;
	m_mouse->capture();

	/* store a copy of last state */
	std::copy(std::begin(m_buttonStates), std::end(m_buttonStates), std::begin(m_oldButtonStates));

	/* update state */
	OIS::MouseState state = m_mouse->getMouseState();
	m_buttonStates[BUTTON_LEFT] = state.buttonDown(OIS::MB_Left);

	int tempx = m_x, tempy = m_y;
	m_x = state.X.abs; 
	m_y = state.Y.abs;
	m_deltax = state.X.rel;
	m_deltay = state.Y.rel;

	m_mouseMoved = m_deltax != 0 || m_deltay != 0;

	if(m_lockToPosition)
	{
		//m_x=m_lockPositionX;
		//m_y=m_lockPositionY;
		//state.X.abs = m_x;
		//state.Y.abs = m_y; // TODO ~~~ does this warp mouse pointer ??? 
	}
	
	return success;
}

bool OISMouseState::Update()
{
	bool success = true;

	success = success && UpdateState();
	success = success && UpdateEvents();

	return success;
}