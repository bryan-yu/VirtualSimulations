#include "StdAfx.h"
#include "Player.h"
#include "Constants.h"

#include "InputManager.h"
#include "Cursor.h"

Player::Player()
{
	m_pickedObject = NULL;
	m_isHoldingObject = false;
	//m_visualDistance = 0.001;
	m_target = NULL;
}

Player::~Player()
{
	ClearActions();
}

void Player::SetMoveSpeed(float movespeed)
{
	m_moveSpeed = movespeed;
}

AABSEngine::AI::Ray* Player::GetVisualRay()
{
	return &m_visualRay;
}

void Player::SetCamera(AABSEngine::Rendering::Camera *cam)
{
	m_camera = cam;
}

void Player::MoveUp()
{
}

void Player::MoveDown()
{
}


AABSEngine::Core::GameObject* Player::SearchWorld(uint32_t searchMask)
{
	m_visualRay.SetQueryMask(searchMask);

	m_visualRay.ConfigureFromCamera(m_camera,5.0);

	Ogre::MovableObject* movObject = m_visualRay.CastQueryForNearestObject();

	if(movObject && !movObject->getUserAny().isEmpty())
	{
		return movObject->getUserAny().get<AABSEngine::Core::GameObject*>();
	}
	return NULL;
}

void Player::MoveForward()
{
	GetPhysicsObject()->AddLinearVelocity(AABSEngine::Core::Vector3(m_camera->GetDirection().X(), 0, m_camera->GetDirection().Z()), m_moveSpeed);
	if(m_pickedObject != NULL)
	{
		m_pickedObject->GetPhysicsObject()->AddLinearVelocity(AABSEngine::Core::Vector3(m_camera->GetDirection().X(), 0, m_camera->GetDirection().Z()), m_moveSpeed);
	}
}

void Player::MoveBackward()
{
	GetPhysicsObject()->AddLinearVelocity(AABSEngine::Core::Vector3(m_camera->GetDirection().X(), 0, m_camera->GetDirection().Z()), -m_moveSpeed);
	if(m_pickedObject != NULL)
	{
		m_pickedObject->GetPhysicsObject()->AddLinearVelocity(AABSEngine::Core::Vector3(m_camera->GetDirection().X(), 0, m_camera->GetDirection().Z()), -m_moveSpeed);
	}
}

void Player::StrafeLeft()
{
	GetPhysicsObject()->AddLinearVelocity(AABSEngine::Core::Vector3(m_camera->GetDirection().Z(), 0, m_camera->GetDirection().X() * -1), m_moveSpeed);
	if(m_pickedObject != NULL)
	{
		m_pickedObject->GetPhysicsObject()->AddLinearVelocity(AABSEngine::Core::Vector3(m_camera->GetDirection().Z(), 0, m_camera->GetDirection().X() * -1), m_moveSpeed);
	}
}

void Player::StrafeRight()
{
	GetPhysicsObject()->AddLinearVelocity(AABSEngine::Core::Vector3(m_camera->GetDirection().Z(), 0, m_camera->GetDirection().X() * -1), -m_moveSpeed);
	if(m_pickedObject != NULL)
	{
		m_pickedObject->GetPhysicsObject()->AddLinearVelocity(AABSEngine::Core::Vector3(m_camera->GetDirection().Z(), 0, m_camera->GetDirection().X() * -1), -m_moveSpeed);
	}
}

void Player::RotateLeft()
{
}

void Player::RotateRight()
{
}


void Player::Rotate(int deltax, int deltay)
{
	
}

void Player::ResetVelocity()
{
	GetPhysicsObject()->SetLinearVelocity(AABSEngine::Core::Vector3(0,GetPhysicsObject()->GetLinearVelocity().Y(),0));
	if(m_pickedObject != NULL)
	{
		m_pickedObject->GetPhysicsObject()->SetLinearVelocity(AABSEngine::Core::Vector3(0,0,0));
	}
}

AABSEngine::Core::Point3 Player::GetPosition()
{
	return this->GetPhysicsObject()->GetWorldPosition();
}

void Player::PickUpObject(AABSEngine::Core::GameObject *target)
{
	m_pickedObject = target;
	m_isHoldingObject = true;

	m_prevObjectLocation = m_pickedObject->GetPhysicsObject()->GetWorldPosition();
}

AABSEngine::Physics::RigidBody* Player::DropObject()
{
	AABSEngine::Physics::RigidBody *result = m_pickedObject->GetPhysicsObject(); //save the return variable content

	m_pickedObject = NULL; //set pickedobject back to null
	m_isHoldingObject = false;

	return result;
}

bool Player::IsHoldingObject()
{
	return m_isHoldingObject;
}

void Player::Update()
{
	if(m_pickedObject != NULL)
	{
		if(m_pickedObject->ToBeRemoved() == false)
		{
			//reset the object based on the camera's and player position
			AABSEngine::Core::Point3 newObjectPosition = m_camera->GetOrigin() + m_camera->GetDirection() * 0.5f;

			//calculate velocity intended
			AABSEngine::Core::Vector3 velocity = newObjectPosition - m_pickedObject->GetPhysicsObject()->GetWorldPosition();
			m_pickedObject->GetPhysicsObject()->AddLinearVelocity(velocity, m_moveSpeed);
		}
		else
		{
			DropObject();
		}
	}
	else
	{
		m_isHoldingObject = false;
	}

	if(m_target != NULL)
	{
		if(m_target->ToBeRemoved())
		{
			m_target = NULL;
		}
	}
}

void Player::SetTarget(AABSEngine::Core::GameObject *target)
{
	m_target = target;
}

AABSEngine::Core::GameObject* Player::GetTarget() const
{
	return m_target;
}
