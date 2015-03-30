#include "StdAfx.h"
#include "CollisionSphere.h"

AABSEngine::Physics::CollisionSphere::CollisionSphere(float mass, float radius)
{
	m_mass = mass;
	m_radius = radius;
	m_inertiaTensor.SetInertiaTensor(0,0,0,0,0,0);

	CalculateInertiaTensor();
}

AABSEngine::Physics::CollisionSphere::~CollisionSphere()
{
}

void AABSEngine::Physics::CollisionSphere::CalculateInertiaTensor()
{
	if(m_mass > 0.0f)
	{
		m_inertiaTensor = AABSEngine::Utility::ITensorCalculator::CreateSphereITensor(m_radius, m_mass);
	}
}

OgreBulletCollisions::CollisionShape *AABSEngine::Physics::CollisionSphere::CreateOgreBTShape()
{
	//create a new ogre bullet box with half extents
	OgreBulletCollisions::SphereCollisionShape *shape = new OgreBulletCollisions::SphereCollisionShape(m_radius);

	return shape;
}