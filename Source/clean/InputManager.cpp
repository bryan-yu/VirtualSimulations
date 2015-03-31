#include "StdAfx.h"
#include "InputManager.h"

using namespace AABSEngine::Input;

InputManager::InputManager()
{
	m_interruptedMsIt = false;
	m_interruptedKbIt = false;

	m_keyboardState = nullptr;
	m_mouseState = nullptr;

	m_keyboardCallbacks.clear();
	m_mouseButtonCallbacks.clear();
	m_mouseMovementCallbacks.clear();

	/* init OIS here */
}

void InputManager::ProcessMouseCallbackEvents()
{
	if (m_mouseState != nullptr)
	{
		m_mouseState->Update();
		
		m_msIt = m_mouseButtonCallbacks.begin(); 
		
		while(m_msIt != m_mouseButtonCallbacks.end())
		{
			if (m_mouseState->ButtonEventFired(*m_msIt->first))
			{
				m_msIt->second(m_mouseState->X(), m_mouseState->Y());
			}

			if(m_interruptedMsIt)
			{
				m_interruptedMsIt = false;
			}
			else
			{
				++m_msIt;
			}	
		}

		for (std::vector<boost::function<void (int, int)>>::iterator it = m_mouseMovementCallbacks.begin(); it != m_mouseMovementCallbacks.end(); it++)
		{
			if (m_mouseState->MovementEventFired())
				(*it)(m_mouseState->DeltaX(), m_mouseState->DeltaY());
		}
	}
	m_mouseState->ClearEvents();
}

void InputManager::ResetInterruptedIteratorFlags()
{
	m_interruptedKbIt = false;
	m_interruptedMsIt = false;
}

void InputManager::ProcessKeyboardCallbackEvents()
{
	if (m_keyboardState != nullptr)
	{
		m_keyboardState->Update();

		m_kbIt = m_keyboardCallbacks.begin();
			
		while(m_kbIt != m_keyboardCallbacks.end())
		{
			if (m_keyboardState->EventFired(*m_kbIt->first))
			{
				m_kbIt->second();
			}

			if(m_interruptedKbIt)
			{
				m_interruptedKbIt = false;
			}
			else
			{
				++m_kbIt;
			}
		}
	}
	m_keyboardState->ClearEvents();
}


bool InputManager::Update()
{
	bool success = true;

	ResetInterruptedIteratorFlags();
	ProcessKeyboardCallbackEvents();
	ProcessMouseCallbackEvents();

	return success;
}

InputManager::~InputManager()
{
	Clear();
}

void InputManager::Register(KeyboardEvent* kevent, boost::function<void ()> func)
{
	m_keyboardCallbacks[kevent] = func;
}

void InputManager::Register(MouseButtonEvent* mevent, boost::function<void(int, int)> func)
{
	m_mouseButtonCallbacks[mevent] = func;
}

void InputManager::Register(boost::function<void (int, int)> func)
{
	m_mouseMovementCallbacks.push_back(func);
}

void InputManager::DeRegister(const KeyboardEvent& kevent)
{
	std::map<KeyboardEvent*, boost::function<void ()> >::iterator it = Find(kevent);

	if(kevent == *(*it).first)
	{
		delete it->first;
		m_keyboardCallbacks.erase(it++);

		m_kbIt = it;
		m_interruptedKbIt = true;	

		return;
	}
	++it;
}

void InputManager::DeRegister(const MouseButtonEvent& mevent)
{
	std::map<MouseButtonEvent*, boost::function<void (int, int)> >::iterator it = Find(mevent);

	if (mevent == *(*it).first)
	{
		delete it->first;
		m_mouseButtonCallbacks.erase(it++);

		m_msIt = it;
		m_interruptedMsIt = true;
			
		return;
	}
	++it;
}

void InputManager::DeRegister(boost::function<void (int, int)> func)
{
  /* TODO
  std::vector<boost::function<void (int, int)> >::iterator it =  m_mouseMovementCallbacks.begin();
  for (it; it != m_mouseMovementCallbacks.end(); )
  {
    if (func == *it)
    {
      it = m_mouseMovementCallbacks.erase(it);
    }
    else
      it++;
  }
  */
}
			

std::map<KeyboardEvent*, boost::function<void ()> >::iterator InputManager::Find(const KeyboardEvent& kbEvent)
{
	std::map<KeyboardEvent*, boost::function<void ()> >::iterator it = m_keyboardCallbacks.begin();
	while(it != m_keyboardCallbacks.end())
	{
		if(*it->first == kbEvent)
		{
			break;
		}
		++it;
	}
	return it;
}

std::map<MouseButtonEvent*, boost::function<void (int, int)> >::iterator InputManager::Find(const MouseButtonEvent& mbEvent)
{
	std::map<MouseButtonEvent*, boost::function<void (int, int)> >::iterator it = m_mouseButtonCallbacks.begin();

	while(it != m_mouseButtonCallbacks.end())
	{
		if(*it->first == mbEvent)
		{
			break;
		}
	}
	return it;
}

void InputManager::Clear()
{
	std::map<KeyboardEvent*, boost::function<void ()> >::iterator it1 = m_keyboardCallbacks.begin();
	std::map<MouseButtonEvent*, boost::function<void (int, int)> >::iterator it2 = m_mouseButtonCallbacks.begin();

	while(it1 != m_keyboardCallbacks.end())
	{
		delete it1->first;
		m_keyboardCallbacks.erase(it1++);
	}

	while(it2 != m_mouseButtonCallbacks.end())
	{
		delete it2->first;
		m_mouseButtonCallbacks.erase(it2++);
	}

	m_mouseMovementCallbacks.clear();
}

