#include "StdAfx.h"
#include "Camera.h"
#include "Ray.h"
#include "SceneManager.h"

AABSEngine::AI::Ray::Ray(AABSEngine::Core::SceneManager* sceneMgr)
{
	m_ogreSceneQuery = NULL;
	if(sceneMgr)
	{
		ConstructSceneQuery(sceneMgr);
	}
}
		

void AABSEngine::AI::Ray::ConfigureFromCamera(AABSEngine::Rendering::Camera* camera, Decimal castDistance)
{
	if(!camera) return;

	SetRayHeading(camera->GetDirection(),castDistance);
	SetRayOrigin(camera->GetOrigin());
}


void AABSEngine::AI::Ray::SetRayObject(const Ogre::Ray& ogreRay)
{
	Ogre::SceneNode* node;
//	node->getUserObjectBindings().setUserAny("RRR",Ogre::Any(0)); // or node->setUserAny(obj)

	if(!m_ogreSceneQuery) return; 

	m_ogreSceneQuery->setRay(ogreRay);
}

void AABSEngine::AI::Ray::SetQueryMask(uint32_t mask)
{
	if(!m_ogreSceneQuery) return;
		
	m_ogreSceneQuery->setQueryMask(mask);
}

void AABSEngine::AI::Ray::SetQueryTypeMask(uint32_t mask)
{
	if(!m_ogreSceneQuery) return; 

	m_ogreSceneQuery->setQueryTypeMask(mask);
}

bool AABSEngine::AI::Ray::ConstructSceneQuery(AABSEngine::Core::SceneManager* sceneMgr)
{
	if(m_ogreSceneQuery) return false;

	m_ogreSceneQuery = sceneMgr->GetOgreSceneManager()->createRayQuery(Ogre::Ray());

	m_ogreSceneQuery->setSortByDistance(true);

	return true;
}

bool AABSEngine::AI::Ray::DestructSceneQuery(AABSEngine::Core::SceneManager* sceneMgr)
{
	if(!m_ogreSceneQuery) return false; 

	m_ogreSceneQuery->clearResults();

	sceneMgr->GetOgreSceneManager()->destroyQuery(m_ogreSceneQuery);
	
	m_ogreSceneQuery = 0;

	return true;
}

Ogre::MovableObject* AABSEngine::AI::Ray::CastQueryForNearestObject()
{
	if(!m_ogreSceneQuery) return NULL;

	Ogre::RaySceneQueryResult& result = m_ogreSceneQuery->execute();

	if(!result.empty())
	{
		Ogre::MovableObject* object = result.begin()->movable;

		Ogre::RaySceneQueryResult::iterator itr = result.begin();

		m_ogreSceneQuery->clearResults();

		return object;
	}

	return NULL;
}

void AABSEngine::AI::Ray::SetRayHeading(Decimal x, Decimal y, Decimal z, Decimal t)
{
	if(!m_ogreSceneQuery) return; 

	Ogre::Ray ray = m_ogreSceneQuery->getRay();

	ray.setDirection( Ogre::Vector3(x*t, y*t, z*t) );
	
	m_ogreSceneQuery->setRay(ray);

}

void AABSEngine::AI::Ray::SetRayOrigin(Decimal x, Decimal y, Decimal z)
{
	if(!m_ogreSceneQuery) return; 

	Ogre::Ray ray = m_ogreSceneQuery->getRay();

	ray.setOrigin(Ogre::Vector3(x,y,z));

	m_ogreSceneQuery->setRay(ray);
}

void AABSEngine::AI::Ray::SetRayHeading(const AABSEngine::Core::Vector3& heading, Decimal t)
{
	if(!m_ogreSceneQuery) return; 
		
	Ogre::Ray ray = m_ogreSceneQuery->getRay();
		
	ray.setDirection( Ogre::Vector3(heading.X()*t,
							        heading.Y()*t,
								    heading.Z()*t) );
	m_ogreSceneQuery->setRay(ray);
}

void AABSEngine::AI::Ray::SetRayOrigin(const AABSEngine::Core::Point3& origin)
{
	if(!m_ogreSceneQuery) return; 

	Ogre::Ray ray = m_ogreSceneQuery->getRay();
		
	ray.setOrigin(Ogre::Vector3(origin.X(), origin.Y(), origin.Z()));
		
	m_ogreSceneQuery->setRay(ray);
}