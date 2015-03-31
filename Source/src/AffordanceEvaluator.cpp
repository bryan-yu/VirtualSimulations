#include "StdAfx.h"
#include "AffordanceEvaluator.h"

using namespace AABSEngine::AI;

AffordanceEvaluator::AffordanceEvaluator()
{

}

AffordanceEvaluator::AffordanceEvaluator(std::string name)
{
  m_name = name;
}

std::string AffordanceEvaluator::GetName() const
{
  return m_name;
}

void AffordanceEvaluator::SetName(const std::string name)
{
  m_name = name;
}