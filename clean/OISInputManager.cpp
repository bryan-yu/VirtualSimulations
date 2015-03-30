#include "StdAfx.h"
#include "OISInputManager.h"
#include <OISMouse.h>
#include <OISKeyboard.h>
#include <OISJoyStick.h>

using namespace AABSEngine::Input;

AABSOISInputManager::AABSOISInputManager(std::string windowHandleString)
{
	/* do OIS setup here */ /* i think this is it ??? */
	OIS::ParamList paramList; 
	paramList.insert(std::make_pair(std::string("WINDOW"), windowHandleString));
	m_inputSystem = OIS::InputManager::createInputSystem(paramList);

	if (m_inputSystem->getNumberOfDevices(OIS::OISKeyboard) > 0) 
	{
        m_keyboardState = std::shared_ptr<OISKeyboardState>(new OISKeyboardState(static_cast<OIS::Keyboard*>(m_inputSystem->createInputObject(OIS::OISKeyboard, false))));
    }
 
    if (m_inputSystem->getNumberOfDevices(OIS::OISMouse) > 0) 
	{
        m_mouseState = std::shared_ptr<OISMouseState>(new OISMouseState(static_cast<OIS::Mouse*>(m_inputSystem->createInputObject(OIS::OISMouse, false))));
    }
}

bool AABSOISInputManager::Update()
{
	return InputManager::Update(); /* this should be all that is needed */
}