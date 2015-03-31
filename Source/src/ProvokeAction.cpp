#include "StdAfx.h"
#include "ProvokeAction.h"
#include "Object.h"
#include "Cursor.h"
#include "Agent.h"
#include "InputManager.h"
#include "Constants.h"
#include "PickAction.h"

	void AABSEngine::Core::ProvokeAction::SetInternals(AABSEngine::Rendering::MouseCursor* cursor) 
	{ 
		m_cursorGraphic = cursor;	
	}

	void AABSEngine::Core::ProvokeAction::Begin()
	{
		m_cursorGraphic->SetTexture("Finger.png"); //lol	
		
		m_user.GetInputManager().DeRegister(AABSEngine::Input::MouseButtonEvent(AABSEngine::Input::BUTTON_LEFT, AABSEngine::Input::BUTTON_DOWN, AABSEngine::Input::BUTTON_ON_PRESS));	

		m_user.GetInputManager().Register(new AABSEngine::Input::KeyboardEvent(AABSEngine::Input::KEY_2, AABSEngine::Input::KEY_UP, AABSEngine::Input::ON_PRESS),
			boost::bind(&ProvokeAction::End,this));
		
		m_user.GetInputManager().Register(new AABSEngine::Input::MouseButtonEvent(AABSEngine::Input::BUTTON_LEFT, AABSEngine::Input::BUTTON_DOWN, AABSEngine::Input::BUTTON_ON_PRESS), 
		    boost::bind(&ProvokeAction::Execute,this));
	}

	void AABSEngine::Core::ProvokeAction::Execute()
	{
		AABSEngine::Core::GameObject* obj = m_user.SearchWorld(QueryMasks::TAVERN_INTERACTABLE);
	
		m_user.SetTarget(obj);

		if(m_user.GetTarget() && m_user.GetTarget()->GetCoreType() == "Agent")
		{
			AABSEngine::AI::Agent* agent = (AABSEngine::AI::Agent*)(m_user.GetTarget());
			agent->TriggerEmotion(-20, 3.0, 1.0, "Sad", Ogre::ColourValue(1.0f, 0.0f, 0.0f));
		}		
	}

	void AABSEngine::Core::ProvokeAction::End()
	{
		m_cursorGraphic->SetTexture("Cursor.png"); 
	
		m_user.GetInputManager().DeRegister(AABSEngine::Input::KeyboardEvent(AABSEngine::Input::KEY_2, AABSEngine::Input::KEY_UP, AABSEngine::Input::ON_PRESS));
		
		m_user.GetInputManager().DeRegister(AABSEngine::Input::MouseButtonEvent(AABSEngine::Input::BUTTON_LEFT, AABSEngine::Input::BUTTON_DOWN, AABSEngine::Input::BUTTON_ON_PRESS));
	
		m_user.GetInputManager().Register(new AABSEngine::Input::MouseButtonEvent(AABSEngine::Input::BUTTON_LEFT, AABSEngine::Input::BUTTON_DOWN, AABSEngine::Input::BUTTON_ON_PRESS), 
			boost::bind(&AABSEngine::Core::PickAction::Begin, m_user.GetAction<PickAction>()));
	}