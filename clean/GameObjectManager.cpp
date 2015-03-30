#include "StdAfx.h"
#include "GameObjectManager.h"
#include "InteractiveObject.h"
#include "Agent.h"
#include "ActionBlackboard.h"
#include "Singleton.h"
#include "Singleton.h"
#include "AABSApplication.h"
#include "Constants.h"

using namespace AABSEngine::Core;

GameObjectManager::GameObjectManager()
{
  m_gameObjectFactory.Register<GameObject>("GameObject");
  m_gameObjectFactory.Register<InteractiveObject>("InteractiveObject");
  m_gameObjectFactory.Register<Agent>("Agent");
}

GameObject* GameObjectManager::Create(std::string id)
{
  GameObject* obj = m_gameObjectFactory.Create(id);
  return obj;
}

void GameObjectManager::AddObject(GameObject* obj, std::string type)
{
  if (obj)
  {
    m_objectList.push_back(obj);
    if (type == "Agent")
	{
		m_agentList.push_back((Agent*)obj);
	}
  }
}

void GameObjectManager::AddPendingObject(GameObject* obj, std::string type)
{
	if (obj)
	{
		PendingObject toBeAdded;
		toBeAdded.m_gameObject = obj;
		toBeAdded.m_type = type;
		m_pendingObjects.push_back(toBeAdded);
	}
}

void GameObjectManager::Update(float dt) /* TODO move to AI manager, Decimal duration */
{
	//setup blackboard object
	AABSEngine::AI::ActionBlackboard *abb = AABSEngine::Core::Singleton<AABSEngine::AI::ActionBlackboard>::Instance();

	for(int i=0; i<m_objectList.size(); i++)
	{
		GameObject *gObj = m_objectList[i];
		gObj->GetSceneNode()->showBoundingBox(false);
		if (dynamic_cast<Agent*>(gObj))
		{
		    Agent* agent = (Agent*)gObj;
		    agent->SetDeltaTime(dt);
		    agent->AnimationUpdate(dt);
		    agent->UpdateEmotionColour(dt);

			if(agent->IsActionDone())
			{
				agent->Update();
			}
		}
		else if (dynamic_cast<InteractiveObject*>(gObj))
		{
		    InteractiveObject* obj = (InteractiveObject*)gObj;
			if (!obj->ToBeRemoved() && obj->GetAffordance("Tidy") && obj->GetSceneNode()->getPosition()[1] < 0.35)
		    {
				if(abb->EntryExist("Tidy", "BarStaff", obj) == false)
				{
					AABSEngine::AI::ActionBlackboardEntry *ent = new AABSEngine::AI::ActionBlackboardEntry("Tidy", "BarStaff", obj);
					abb->AddEntry(ent);
				}
			}
		}
	}

	//add any objects that should be added
	for(int i=0; i<m_pendingObjects.size(); i++)
	{
		AddObject(m_pendingObjects[i].m_gameObject, m_pendingObjects[i].m_type);
	}

	m_pendingObjects.clear(); //clear the vector
}

void GameObjectManager::RemoveObject(GameObject* obj)
{
	for (std::vector<GameObject*>::iterator it = m_objectList.begin(); it != m_objectList.end(); it++)
	{
		if((*it) == obj)
		{
			m_objectList.erase(it); //erase from vector
			delete obj; //delete the object
			obj = NULL;
			break;
		}
	}
}

InteractiveObject* GameObjectManager::CreateInteractiveObject(InteractiveObjectDefinition def)
{
	InteractiveObject* obj = (InteractiveObject*)Create("InteractiveObject");
	//setup the wrapper node
	SceneManager* sman = AABSEngine::Core::Singleton<AABSApplication>::Instance()->GetSceneManager();
	AABSEngine::Physics::PhysicsManager* pman = AABSEngine::Core::Singleton<AABSApplication>::Instance()->GetPhysicsManager();

	if (!sman || !pman)
	{
		return NULL;
	}

	Ogre::SceneNode *parentNode = sman->GetOgreSceneManager()->getRootSceneNode()->createChildSceneNode();

	//get the meshfile name
	Ogre::SceneNode *node = sman->CreateSceneNode(def.m_gameobject.m_meshfile, parentNode, QueryMasks::TAVERN_INTERACTABLE);

	obj->SetSceneNode(parentNode);
  
	if(def.m_gameobject.m_collisiongroup == "ENV")
	{
		parentNode->setVisible(false);
		pman->AddObject(obj, def.m_gameobject.m_physicsobjectname, def.m_gameobject.m_position, def.m_gameobject.m_orientation, 
		AABSEngine::Physics::PhysicsManager::CollisionMask::COL_ENVIRONMENT, AABSEngine::Physics::ENV_COLLISION_FILTER); //setup the physics object with collision filter and mask
	}
	else
	{
		pman->AddObject(obj, def.m_gameobject.m_physicsobjectname, def.m_gameobject.m_position, def.m_gameobject.m_orientation);
	}
		
	if(def.m_gameobject.m_gravity)
	{
		pman->RegisterRigidBodyWithForceGenerator("GravityForceGenerator", obj->GetPhysicsObject());
	}

	parentNode->setVisible(def.m_gameobject.m_visible); 

	obj->AddAffordance(def.m_affordance.GetName(), def.m_affordance.GetAffordanceMaxValue()); /* TODO this is a horrible way to intialise the affordances. its not generic. its not tidy. it sucks. fix it */

	return obj;
}