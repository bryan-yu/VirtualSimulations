#include "StdAfx.h"
#include "IDesireModifier.h"
#include "Trait.h"
#include "Need.h"

Decimal AABSEngine::AI::IDesireModifier::EvaluateDesire(const AABSEngine::AI::Trait* trait, const AABSEngine::AI::Need* need)const
{
	return need->GetBase();
}