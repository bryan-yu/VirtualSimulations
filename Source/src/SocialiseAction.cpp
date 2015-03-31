#include "StdAfx.h"
#include "SocialiseAction.h"
#include "Object.h"
#include "Cursor.h"
#include "InputManager.h"
#include "Constants.h"
#include "PickAction.h"


	void AABSEngine::Core::SocialiseAction::SetInternals(AABSEngine::Rendering::MouseCursor* cursor) 
	{ 
		m_cursorGraphic = cursor;	
	}

	void AABSEngine::Core::SocialiseAction::Begin()
	{
		m_cursorGraphic->SetTexture("Lips.png");

		m_user.GetInputManager().DeRegister(AABSEngine::Input::MouseButtonEvent(AABSEngine::Input::BUTTON_LEFT, AABSEngine::Input::BUTTON_DOWN, AABSEngine::Input::BUTTON_ON_PRESS));

		m_user.GetInputManager().Register(new AABSEngine::Input::KeyboardEvent(AABSEngine::Input::KEY_3, AABSEngine::Input::KEY_UP, AABSEngine::Input::ON_PRESS), boost::bind(&SocialiseAction::End,this));
		
		m_user.GetInputManager().Register(new AABSEngine::Input::MouseButtonEvent(AABSEngine::Input::BUTTON_LEFT, AABSEngine::Input::BUTTON_DOWN, AABSEngine::Input::BUTTON_ON_PRESS), 
		boost::bind(&SocialiseAction::Execute,this));
	}

	void AABSEngine::Core::SocialiseAction::Execute()
	{
		
	}

	void AABSEngine::Core::SocialiseAction::End()
	{
		m_cursorGraphic->SetTexture("Cursor.png");

		m_user.GetInputManager().DeRegister(AABSEngine::Input::KeyboardEvent(AABSEngine::Input::KEY_3, AABSEngine::Input::KEY_UP, AABSEngine::Input::ON_PRESS));
		
		m_user.GetInputManager().DeRegister(AABSEngine::Input::MouseButtonEvent(AABSEngine::Input::BUTTON_LEFT, AABSEngine::Input::BUTTON_DOWN, AABSEngine::Input::BUTTON_ON_PRESS));	
	
		m_user.GetInputManager().Register(new AABSEngine::Input::MouseButtonEvent(AABSEngine::Input::BUTTON_LEFT, AABSEngine::Input::BUTTON_DOWN, AABSEngine::Input::BUTTON_ON_PRESS), 
			boost::bind(&AABSEngine::Core::PickAction::Begin, m_user.GetAction<PickAction>()));
	}