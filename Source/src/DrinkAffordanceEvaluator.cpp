#include "StdAfx.h"
#include "DrinkAffordanceEvaluator.h"
#include "AffordanceManager.h"

DrinkAffordanceEvaluator::DrinkAffordanceEvaluator()
{

}

DrinkAffordanceEvaluator::DrinkAffordanceEvaluator(std::string name) : AffordanceEvaluator(name)
{
  
}

int DrinkAffordanceEvaluator::Evaluate(Agent* drinker, AABSEngine::Core::InteractiveObject* drinkee)
{
  if (drinker != NULL && drinkee != NULL)
  {
    Affordance* aff = drinkee->GetAffordance("Drink");
    if (aff)
      return aff->GetAffordanceCurrentValue();
  }
  return 0;
}