#include "StdAfx.h"
#include "Trait.h"

AABSEngine::AI::Trait::Trait(int bias)
{
	SetBias(bias);
}

AABSEngine::AI::Trait::Trait(const Trait& other)
{
	SetBias(other.m_bias);
}

AABSEngine::AI::Trait& AABSEngine::AI::Trait::operator=(const Trait& other)
{
	if(this != &other)
	{
		SetBias(other.m_bias);
	}
	return *this;
}

Decimal AABSEngine::AI::Trait::GetBias()const
{
	return m_bias;
}

void AABSEngine::AI::Trait::SetBias(Decimal bias)
{
	m_bias = bias;
}

std::string AABSEngine::AI::Trait::GetName()const
{
	return m_name;
}

std::string AABSEngine::AI::Trait::GetNeed() const
{
  return m_need;
}

void AABSEngine::AI::Trait::SetNeed(std::string need)
{
  m_need = need;
}

void AABSEngine::AI::Trait::SetName(std::string name)
{
	m_name = name;
}