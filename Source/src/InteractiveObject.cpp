#include "StdAfx.h"
#include "InteractiveObject.h"

AABSEngine::Core::InteractiveObject::InteractiveObject()
{
}

AABSEngine::Core::InteractiveObject::~InteractiveObject()
{
	//clear all affordances
	for(int i=0; i<m_affordances.size(); i++)
	{
		delete m_affordances[i];
	}
}

void AABSEngine::Core::InteractiveObject::AddAffordance(std::string affordanceName, int initValue)
{
	AI::Affordance *aff = AI::AffordanceManager::Instance()->CreateAffordance(affordanceName, initValue);
	m_affordances.push_back(aff);
}

bool AABSEngine::Core::InteractiveObject::HasAffordance(std::string affordanceName)
{
	for(int i=0; i<m_affordances.size(); i++)
	{
		if(m_affordances[i]->GetName() == affordanceName)
		{
			return true;
		}
	}
	return false;
}

AABSEngine::AI::Affordance* AABSEngine::Core::InteractiveObject::GetAffordance(std::string affordanceName)
{
	for(int i=0; i<m_affordances.size(); i++)
	{
		if(m_affordances[i]->GetName() == affordanceName)
		{
			return m_affordances[i];
		}
	}

	return NULL;
}

std::vector<AABSEngine::AI::Affordance*> AABSEngine::Core::InteractiveObject::GetAffordances()
{
	return m_affordances;
}

void AABSEngine::Core::InteractiveObject::AddAffordanceModifier(std::string affordance, int mod)
{
  m_affordanceModifiers[affordance] = mod;
}

void AABSEngine::Core::InteractiveObject::ActionAffordanceModifier(std::string affordance)
{
  AABSEngine::AI::Affordance* aff = GetAffordance(affordance);
  if (aff)
  {
    if (m_affordanceModifiers.count(affordance) > 0)
    {
      int change = aff->GetAffordanceMaxValue() * (1.0 / m_affordanceModifiers[affordance]);
      aff->ReduceAffordance(change);
    }
  }
}

void AABSEngine::Core::InteractiveObject::ResolveAffordanceModifier(std::string affordance)
{
  AABSEngine::AI::Affordance* aff = GetAffordance(affordance);
  if (aff)
  {
    if (m_affordanceModifiers.count(affordance) > 0)
    {
      int change = aff->GetAffordanceMaxValue() * (1.0 / m_affordanceModifiers[affordance]);
      aff->AddAffordance(change);
    }
  }
}