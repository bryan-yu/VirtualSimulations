#include "StdAfx.h"
#include "CollisionBox.h"

AABSEngine::Physics::CollisionBox::CollisionBox(float mass, float width, float height, float length)
{
	m_mass = mass;
	m_width = width;
	m_height = height;
	m_length = length;
	m_inertiaTensor.SetInertiaTensor(0,0,0,0,0,0);

	CalculateInertiaTensor();
}

AABSEngine::Physics::CollisionBox::~CollisionBox()
{
}

void AABSEngine::Physics::CollisionBox::CalculateInertiaTensor()
{
	//half the width, height, and length
	Core::Vector3 extents = Core::Vector3(m_width, m_height, m_length);

	if(m_mass > 0.0f)
	{
		m_inertiaTensor = AABSEngine::Utility::ITensorCalculator::CreateCuboidITensor(extents, m_mass);
	}
}

OgreBulletCollisions::CollisionShape *AABSEngine::Physics::CollisionBox::CreateOgreBTShape()
{
	//create a new ogre bullet box with half extents
	Ogre::Vector3 halfExtents(m_width / 2, m_height / 2, m_length / 2);
	OgreBulletCollisions::BoxCollisionShape *boxShape = new OgreBulletCollisions::BoxCollisionShape(halfExtents);

	return boxShape;
}