#include "StdAfx.h"
#include "DrinkAction.h"
#include "Object.h"
#include "Cursor.h"
#include "InputManager.h"
#include "Agent.h"
#include "Constants.h"
#include "Ray.h"
#include "PickAction.h"

void AABSEngine::Core::DrinkAction::SetInternals(AABSEngine::Rendering::MouseCursor* cursor) 
{ 
	m_cursorGraphic = cursor;	
}

void AABSEngine::Core::DrinkAction::Begin()
{
	m_cursorGraphic->SetTexture("Mug.png"); //lol

	m_user.GetInputManager().DeRegister(AABSEngine::Input::MouseButtonEvent(AABSEngine::Input::BUTTON_LEFT, AABSEngine::Input::BUTTON_DOWN, AABSEngine::Input::BUTTON_ON_PRESS));

	m_user.GetInputManager().Register(new AABSEngine::Input::KeyboardEvent(AABSEngine::Input::KEY_1, AABSEngine::Input::KEY_UP, AABSEngine::Input::ON_PRESS),
		boost::bind(&DrinkAction::End,this));
	
	m_user.GetInputManager().Register(new AABSEngine::Input::MouseButtonEvent(AABSEngine::Input::BUTTON_LEFT, AABSEngine::Input::BUTTON_DOWN, AABSEngine::Input::BUTTON_ON_PRESS), 
		boost::bind(&DrinkAction::Execute,this));		
}

void AABSEngine::Core::DrinkAction::Execute()
{
	//check if this is an agent
	AABSEngine::Core::GameObject* obj = m_user.SearchWorld(QueryMasks::TAVERN_INTERACTABLE);
	
	m_user.SetTarget(obj);

	if(m_user.GetTarget() && m_user.GetTarget()->GetCoreType() == "Agent")
	{
		AABSEngine::AI::Agent* agent = (AABSEngine::AI::Agent*)(m_user.GetTarget());
		agent->TriggerEmotion(20, 3.0, 1.0, "Happy", Ogre::ColourValue(0.0f, 1.0f, 0.0f));
	}
}

void AABSEngine::Core::DrinkAction::End()
{
	m_cursorGraphic->SetTexture("Cursor.png"); 

	m_user.GetInputManager().DeRegister(AABSEngine::Input::KeyboardEvent(AABSEngine::Input::KEY_1, AABSEngine::Input::KEY_UP, AABSEngine::Input::ON_PRESS));
	
	m_user.GetInputManager().DeRegister(AABSEngine::Input::MouseButtonEvent(AABSEngine::Input::BUTTON_LEFT, AABSEngine::Input::BUTTON_DOWN, AABSEngine::Input::BUTTON_ON_PRESS));
	
	m_user.GetInputManager().Register(new AABSEngine::Input::MouseButtonEvent(AABSEngine::Input::BUTTON_LEFT, AABSEngine::Input::BUTTON_DOWN, AABSEngine::Input::BUTTON_ON_PRESS), 		
		boost::bind(&AABSEngine::Core::PickAction::Begin, m_user.GetAction<PickAction>()));
}