#include "StdAfx.h"
#include "ForceRegistration.h"

using namespace AABSEngine::Physics;

ForceRegistration::ForceRegistration(RigidBody* body, AABSEngine::Physics::ForceGenerator* generator)
{
	m_generator = generator;
	m_body = body;
}

ForceRegistration::~ForceRegistration()
{
}

void ForceRegistration::Clear()
{
	if(m_generator) delete m_generator;
	
	m_generator = NULL;
	m_body = NULL;
}

ForceRegistration::ForceRegistration()
{
	m_generator = NULL;
	m_body = NULL;
}

void ForceRegistration::Update(Decimal duration)
{
	m_generator->UpdateForce(m_body, duration);
}

RigidBody* ForceRegistration::GetBody()
{
  return m_body;
}

bool ForceRegistration::operator==(const ForceRegistration& rhs) const
{
	return ((this->m_body == rhs.m_body) && (this->m_generator == rhs.m_generator));
}

bool ForceRegistration::operator!=(const ForceRegistration& rhs) const
{
	return !(*this == rhs);
}