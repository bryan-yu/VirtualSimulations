#include "StdAfx.h"
#include "CollisionCylinder.h"

AABSEngine::Physics::CollisionCylinder::CollisionCylinder(float mass, float radius, float height)
{
	m_mass = mass;
	m_radius = radius;
	m_height = height;
	m_inertiaTensor.SetInertiaTensor(0,0,0,0,0,0);

	CalculateInertiaTensor();
}

AABSEngine::Physics::CollisionCylinder::~CollisionCylinder()
{
}

void AABSEngine::Physics::CollisionCylinder::CalculateInertiaTensor()
{
	if(m_mass > 0.0f)
	{
		m_inertiaTensor = AABSEngine::Utility::ITensorCalculator::CreateCylinderITensor(m_radius, m_height, m_mass);
	}
}

OgreBulletCollisions::CollisionShape *AABSEngine::Physics::CollisionCylinder::CreateOgreBTShape()
{
	//create a new ogre bullet box with half extents
	Ogre::Vector3 halfExtents(m_radius, m_height / 2, m_radius);
	OgreBulletCollisions::CylinderCollisionShape *shape = new OgreBulletCollisions::CylinderCollisionShape(halfExtents, Ogre::Vector3::UNIT_Y);

	return shape;
}