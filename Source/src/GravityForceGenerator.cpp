#include "StdAfx.h"
#include "GravityForceGenerator.h"

using namespace AABSEngine::Physics;

GravityForceGenerator::GravityForceGenerator(AABSEngine::Core::Vector3 gravity)
{
	m_gravity = gravity;
}

void GravityForceGenerator::UpdateForce(RigidBody* body, Decimal duration)
{
	body->AddForce(m_gravity * body->GetMass()); // ???
}