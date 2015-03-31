#include "StdAfx.h"
#include "SocialiseAffordanceEvaluator.h"
#include "AffordanceManager.h"

SocialiseAffordanceEvaluator::SocialiseAffordanceEvaluator()
{

}

SocialiseAffordanceEvaluator::SocialiseAffordanceEvaluator(std::string name) : AffordanceEvaluator(name)
{
  
}

int SocialiseAffordanceEvaluator::Evaluate(Agent* socialiser, AABSEngine::Core::InteractiveObject* socialisee)
{
  if (socialiser != NULL && socialisee != NULL)
  {
    Affordance* aff = socialisee->GetAffordance("Socialise");
    if (aff)
      return aff->GetAffordanceCurrentValue();
  }
  return 0;
}