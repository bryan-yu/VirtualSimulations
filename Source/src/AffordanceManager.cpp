#include "StdAfx.h"
#include "AffordanceManager.h"

#include "DrinkAffordanceEvaluator.h"
#include "SocialiseAffordanceEvaluator.h"
#include "UrinateAffordanceEvaluator.h"

AABSEngine::AI::AffordanceManager* AABSEngine::AI::AffordanceManager::m_singleton = NULL;

AABSEngine::AI::AffordanceManager::AffordanceManager()
{
  /* Register to create affordances */
  m_affordanceFactory.Register<AI::Affordance>("Affordance");
}

AABSEngine::AI::AffordanceManager* AABSEngine::AI::AffordanceManager::Instance()
{
	if(m_singleton == NULL)
	{
		m_singleton = new AABSEngine::AI::AffordanceManager();
	}

	return m_singleton;
}

AABSEngine::AI::Affordance* AABSEngine::AI::AffordanceManager::CreateAffordance(std::string affType, int initValue)
{
	AI::Affordance* newAff = m_affordanceFactory.Create("Affordance");
	newAff->Initialize(affType, initValue);

	return newAff;
}

const std::vector<std::string>* AABSEngine::AI::AffordanceManager::GetTypesByAffordance(std::string affordance) const
{
  if (m_affordanceObjectList.count(affordance) > 0)
    return &m_affordanceObjectList.find(affordance)->second;
  return NULL;
}

AABSEngine::AI::AffordanceEvaluator* AABSEngine::AI::AffordanceManager::GetAffordanceEvaluator(std::string affordance)
{
  if (affordance == "Drink")
    return new DrinkAffordanceEvaluator(affordance);
  else if (affordance == "Urinate")
    return new UrinateAffordanceEvaluator(affordance);
  else if (affordance == "Socialise")
    return new SocialiseAffordanceEvaluator(affordance);
  else
    return NULL;
}

bool AABSEngine::AI::AffordanceManager::RegisterAffordanceProvider(std::string affordance, std::string type)
{
  std::vector<std::string>::iterator it;
  for (it = m_affordanceObjectList[affordance].begin(); 
    it != m_affordanceObjectList[affordance].end() && *it != type; it++);

  if (it == m_affordanceObjectList[affordance].end())
    m_affordanceObjectList[affordance].push_back(type);

  return true;
}