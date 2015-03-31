#include "StdAfx.h"
#include "Object.h"
#include <sstream>

int AABSEngine::Core::GameObject::m_id = 0;

std::string ConvertIntToString(int input)
{
    std::string result;
    std::ostringstream converter;
    converter << input;
    result = converter.str();

    return result;
}

void AABSEngine::Core::GameObject::AssignID()
{
	m_id++;
	m_objectID = m_id;
	m_name = ConvertIntToString(m_objectID);
}

AABSEngine::Core::GameObject::GameObject()
{
	AssignID();

	m_deleteOnContact = false;
	m_deleteObject = false;
	m_physObject = NULL;
	m_sceneNode = NULL;
}

AABSEngine::Core::GameObject::~GameObject()
{
	delete m_physObject;
	m_physObject = NULL;
}

AABSEngine::Core::GameObject::GameObject(Ogre::SceneNode *input)
{
	AssignID();
	
	SetSceneNode(input);

	m_deleteOnContact = false;
	m_deleteObject = false;
	m_physObject = NULL;
}

void AABSEngine::Core::GameObject::SetSceneNode(Ogre::SceneNode *input)
{
	if(input)
	{
		m_sceneNode = input;
		Ogre::SceneNode* childNode = (Ogre::SceneNode*)m_sceneNode->getChild(0); //the node that holds the ogre entity
		childNode->getAttachedObject(0)->setUserAny(Ogre::Any(this)); //set the user pointer on the entity for the raycast mechanism
	}
}

Ogre::SceneNode* AABSEngine::Core::GameObject::GetSceneNode()
{
	return m_sceneNode;
}

std::string AABSEngine::Core::GameObject::GetName()
{
	return m_name;
}

void AABSEngine::Core::GameObject::SetPhysicsObject(AABSEngine::Physics::RigidBody *input)
{
	m_physObject = input;
}

AABSEngine::Physics::RigidBody *AABSEngine::Core::GameObject::GetPhysicsObject()
{
	
	return m_physObject;
}

void AABSEngine::Core::GameObject::SetType(const std::string type)
{
    m_name = type;
}

std::string AABSEngine::Core::GameObject::GetType() const
{
    return m_name;
}

std::string AABSEngine::Core::GameObject::GetCoreType() const
{
    return m_coreType;
}

void AABSEngine::Core::GameObject::SetCoreType(const std::string type)
{
    m_coreType = type;
}