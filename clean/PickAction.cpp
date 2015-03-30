#include "StdAfx.h"
#include "PickAction.h"
#include "Object.h"
#include "PhysicsManager.h"
#include "RigidBody.h"
#include "Constants.h"


void AABSEngine::Core::PickAction::SetInternals(Physics::PhysicsManager* physMgr)
{
	m_physManager = physMgr;
}

void AABSEngine::Core::PickAction::Begin()
{	
	AABSEngine::Core::GameObject* obj = m_user.SearchWorld(QueryMasks::TAVERN_INTERACTABLE);

	if(!obj) return;

	if(!m_user.IsHoldingObject())
	{	
		AABSEngine::Physics::RigidBody *targetRB = obj->GetPhysicsObject();
		//check for the target
		if(!targetRB->IsKinematic() && !targetRB->IsStatic()) //only works for non static and non kinematic object
		{
			targetRB->Awaken(); //awaken the object
			m_user.SetTarget(obj);
			m_user.PickUpObject(obj);
			m_physManager->DeregisterRigidBodyFromForceGenerator("GravityForceGenerator", targetRB); //remove the gravity
		}
	}
	else
	{
		//drop the object if the player is holding something
		m_physManager->RegisterRigidBodyWithForceGenerator("GravityForceGenerator", m_user.DropObject());
	}
}

void AABSEngine::Core::PickAction::Execute()
{
}

void AABSEngine::Core::PickAction::End()
{
}