#include "StdAfx.h"
#include "CollisionObject.h"

float AABSEngine::Physics::CollisionObject::GetMass() const
{
	return m_mass;
}

void AABSEngine::Physics::CollisionObject::SetMass(const float mass) 
{
	m_mass = mass;  
}

AABSEngine::Core::Matrix3 AABSEngine::Physics::CollisionObject::GetInertiaTensor() const
{
	return m_inertiaTensor;
}