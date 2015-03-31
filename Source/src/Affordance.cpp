#include "StdAfx.h"
#include "Affordance.h"

int AABSEngine::AI::Affordance::GetAffordanceCurrentValue()
{
	return m_currentValue;
}

int AABSEngine::AI::Affordance::GetAffordanceMaxValue()
{
  return m_baseValue;
}

void AABSEngine::AI::Affordance::Initialize(std::string type, int initValue)
{
  m_name = type;
	m_currentValue = initValue;
	m_baseValue = initValue;
}

void AABSEngine::AI::Affordance::AddAffordance(int amount)
{
	m_currentValue += amount;
  ClampAffordance();
}

void AABSEngine::AI::Affordance::ReduceAffordance(int amount)
{
	m_currentValue -= amount;
  ClampAffordance();
}

std::string AABSEngine::AI::Affordance::GetName()
{
	return m_name;
}

void AABSEngine::AI::Affordance::ClampAffordance()
{
	if(m_currentValue > m_baseValue)
	{
		m_currentValue = m_baseValue;
	}
  if(m_currentValue < 0)
	{
		m_currentValue = 0;
	}
}