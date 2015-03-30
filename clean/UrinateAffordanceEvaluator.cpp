#include "StdAfx.h"
#include "UrinateAffordanceEvaluator.h"
#include "AffordanceManager.h"

UrinateAffordanceEvaluator::UrinateAffordanceEvaluator()
{

}

UrinateAffordanceEvaluator::UrinateAffordanceEvaluator(std::string name) : AffordanceEvaluator(name)
{
  
}

int UrinateAffordanceEvaluator::Evaluate(Agent* drinker, AABSEngine::Core::InteractiveObject* drinkee)
{
  if (drinker != NULL && drinkee != NULL)
  {
    Affordance* aff = drinkee->GetAffordance("Urinate");
    if (aff)
      return aff->GetAffordanceCurrentValue();
  }
  return 0;
}