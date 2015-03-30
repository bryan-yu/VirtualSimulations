#include "StdAfx.h"
#include "SceneManager.h"
#include "OgreNode.h"
#include "OgreColourValue.h"
#include "OgreLight.h"
#include "OgreEntity.h"
#include "OgreSubMesh.h"
#include <queue>

void AABSEngine::Core::SceneManager::ResetScene()
{
	Ogre::Camera* cam;

	m_ogreSceneMgr->clearScene();
}

AABSEngine::Core::SceneManager::~SceneManager()
{
	ResetScene();
}

AABSEngine::Core::SceneManager::SceneManager(Ogre::SceneManager *sm) : m_ogreSceneMgr(sm)
{
}

bool AABSEngine::Core::SceneManager::AttachSceneNode(Ogre::String parentName, Ogre::SceneNode* childNode)
{
	Ogre::SceneNode* node = GetSceneNode(parentName);

	if(node)
	{
		node->addChild(childNode);
		return true;
	}
	return false;
}


bool AABSEngine::Core::SceneManager::SceneNodeExists(Ogre::String nodeName)const
{
	if(GetSceneNode(nodeName))
	{
		return true;
	}
	return false;
}

Ogre::SceneNode* AABSEngine::Core::SceneManager::CreateSceneNode(Ogre::String entMeshFilename, Ogre::SceneNode* parentNode, Ogre::uint32 mask, 
	const Ogre::Vector3 &pos, const Ogre::Quaternion& orient, const Ogre::Vector3& scale)
{
	Ogre::Entity* entity = m_ogreSceneMgr->createEntity(entMeshFilename);
	
	entity->setCastShadows(true);
	entity->setQueryFlags(mask);

	Ogre::SceneNode* childNode = m_ogreSceneMgr->createSceneNode();

	childNode->attachObject(entity);
	childNode->setPosition(pos);
	childNode->setOrientation(orient);
	childNode->setScale(scale);

	if(parentNode)
	{
		parentNode->addChild(childNode);
	}

	return childNode;
}

bool AABSEngine::Core::SceneManager::UprootSceneChild(Ogre::String parentName, Ogre::String childName)
{
	Ogre::SceneNode* node = GetSceneNode(parentName);

	if(node)
	{
		node->removeAndDestroyChild(childName);
		return true;
	}
	return false;
}


void AABSEngine::Core::SceneManager::DestroyCamera(Ogre::String name)
{
	m_ogreSceneMgr->destroyCamera(name);
}

bool AABSEngine::Core::SceneManager::UprootSceneChildren(Ogre::String parentName)
{
	Ogre::SceneNode* node = GetSceneNode(parentName);
	
	if(node)
	{
		node->removeAndDestroyAllChildren();
		return true;
	}
	return false;
}


void AABSEngine::Core::SceneManager::SetAmbientLight(const Ogre::ColourValue& colour)
{
	m_ogreSceneMgr->setAmbientLight(colour);
}

AABSEngine::Rendering::Camera* AABSEngine::Core::SceneManager::CreateCamera(Ogre::String name, const Ogre::Vector3 &lookat, const Ogre::Vector3 &pos, const Ogre::Quaternion& orient,
 Ogre::Real nearDist, Ogre::Real farDist, /*Ogre::Real aspRatio,*/ Ogre::Real fovYDegree)
 {
	 Ogre::Camera* cam = m_ogreSceneMgr->createCamera(name);

	 cam->lookAt(lookat);
	 cam->setPosition(pos);
	 cam->setNearClipDistance(nearDist);
	 cam->setFarClipDistance(farDist);
	 cam->setFOVy(Ogre::Degree(fovYDegree));
	 cam->setOrientation(orient);
	 //cam->setAspectRatio(aspRatio);

	 return new AABSEngine::Rendering::Camera(cam, 5.0f, 20.0f);
 }

 const Ogre::Camera* AABSEngine::Core::SceneManager::GetCamera(Ogre::String name)const
 {
	 return m_ogreSceneMgr->getCamera(name);
 }

 Ogre::Camera* AABSEngine::Core::SceneManager::GetCamera(Ogre::String name)
 {
	 return m_ogreSceneMgr->getCamera(name);
 }

Ogre::SceneNode* AABSEngine::Core::SceneManager::GetSceneNode(Ogre::String nodeName)
{
	return m_ogreSceneMgr->getSceneNode(nodeName);
}
		 
const Ogre::SceneNode* AABSEngine::Core::SceneManager::GetSceneNode(Ogre::String nodeName)const
{
	return m_ogreSceneMgr->getSceneNode(nodeName);
}


const Ogre::SceneNode* AABSEngine::Core::SceneManager::GetRootSceneNode()const
{
	return m_ogreSceneMgr->getRootSceneNode();
}
		 
Ogre::SceneNode* AABSEngine::Core::SceneManager::GetRootSceneNode()
{
	return m_ogreSceneMgr->getRootSceneNode();
}

void AABSEngine::Core::SceneManager::CreateLight(Ogre::String lightName, Ogre::Light::LightTypes type,
	const Ogre::ColourValue &specular, const Ogre::ColourValue &diffuse)
{
	Ogre::Light* light = m_ogreSceneMgr->createLight(lightName);

	light->setType(type);
	light->setSpecularColour(specular);
	light->setDiffuseColour(diffuse);
}


Ogre::Light* AABSEngine::Core::SceneManager::GetLight(Ogre::String lightName)
{
	return m_ogreSceneMgr->getLight(lightName);
}

const Ogre::Light* AABSEngine::Core::SceneManager::GetLight(Ogre::String lightName)const
{
	return m_ogreSceneMgr->getLight(lightName);
}

void AABSEngine::Core::SceneManager::DestroyLight(Ogre::String lightName)
{
	return m_ogreSceneMgr->destroyLight(lightName);
}

Ogre::Entity* AABSEngine::Core::SceneManager::CreateOgreEntity(const Ogre::String &filename)
{
	return m_ogreSceneMgr->createEntity(filename);
}


Ogre::SceneManager *AABSEngine::Core::SceneManager::GetOgreSceneManager()
{
	return m_ogreSceneMgr;
}

void AABSEngine::Core::SceneManager::GroupPhoto(std::string nodeName)
{
	// Create a manual object for 2D
	Ogre::ManualObject* groupPhoto = m_ogreSceneMgr->createManualObject(nodeName);
 
	// Use identity view/projection matrices
	groupPhoto->setUseIdentityProjection(true);
	groupPhoto->setUseIdentityView(true);
 
	groupPhoto->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
 
	groupPhoto->setMaterialName(0, "AABSPicture");

	groupPhoto->position(-1, -1, 0.0); //bottom left
	groupPhoto->textureCoord(0,1);
	groupPhoto->position( 1, -1, 0.0); //bottom right
	groupPhoto->textureCoord(1,1);
	groupPhoto->position( 1,  1, 0.0); //top right
	groupPhoto->textureCoord(1,0);
	groupPhoto->position(-1,  1, 0.0); //top left
	groupPhoto->textureCoord(0,0);
 
	groupPhoto->index(0);
	groupPhoto->index(1);
	groupPhoto->index(2);
	groupPhoto->index(0);
	groupPhoto->index(3);
	groupPhoto->index(2);
 
	groupPhoto->end();
 
	groupPhoto->setQueryFlags(0);
	// Use infinite AAB to always stay visible
	Ogre::AxisAlignedBox aabInf;
	aabInf.setInfinite();
	groupPhoto->setBoundingBox(aabInf);
 
	// Render just before overlays
	groupPhoto->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY - 1);
 
	// Attach to scene
	m_ogreSceneMgr->getRootSceneNode()->createChildSceneNode(nodeName)->attachObject(groupPhoto);
	Ogre::SceneNode *node = m_ogreSceneMgr->getSceneNode(nodeName);

	node->setVisible(false);
}
