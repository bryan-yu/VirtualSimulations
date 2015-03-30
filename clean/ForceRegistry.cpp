#include "StdAfx.h"
#include "ForceRegistry.h"

using namespace AABSEngine::Physics;

ForceRegistry::ForceRegistry()
{

}
ForceRegistry::~ForceRegistry()
{
	std::vector<AABSEngine::Physics::ForceRegistration>::iterator it;

	while(it != m_registrations.end())
	{
		it->Clear();
		it = m_registrations.erase(it);
	}
}

void ForceRegistry::RegisterForce(AABSEngine::Physics::ForceGenerator* generator, RigidBody* body)
{
	m_registrations.push_back(ForceRegistration(body, generator));
}

void ForceRegistry::DeRegisterForce(AABSEngine::Physics::ForceGenerator* generator, RigidBody* body)
{
	ForceRegistration r(body, generator);
	std::vector<AABSEngine::Physics::ForceRegistration>::iterator it;
	
	for (it = m_registrations.begin(); it != m_registrations.end(); )
	{
		if (*it == r)
		{
		//	it->Clear();
			it = m_registrations.erase(it);
		}
		else
			it++;
	}
}

void ForceRegistry::DeRegisterAllForces(RigidBody* body)
{
	std::vector<AABSEngine::Physics::ForceRegistration>::iterator it;
	for (it = m_registrations.begin(); it != m_registrations.end(); )
	{
		if (it->GetBody() == body)
		{
		//	it->Clear();
			it = m_registrations.erase(it);
		}
		else
			it++;
	}
}

void ForceRegistry::Update(Decimal duration)
{
  std::vector<AABSEngine::Physics::ForceRegistration>::iterator it;
  for (it = m_registrations.begin(); it != m_registrations.end(); it++)
    it->Update(duration);
}