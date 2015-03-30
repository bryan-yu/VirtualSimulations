#include "StdAfx.h"
#include "IEmotionModifier.h"
#include "Trait.h"

Emotion AABSEngine::AI::IEmotionModifier::EvaluateEmotion(const AABSEngine::AI::Trait* trait, const Emotion* emo)const
{
	return *emo;
}