#pragma once

#include "types.h"
#include "Emotions.h"
#include "Evaluator.h"

namespace AABSEngine
{
	namespace AI
	{
		class Trait;

		/**
		* @class IEmotionModifier
		*
		* @brief Modifier used to affect emotions over time. (Not currently implemented)
		*
		* @author Bryan Yu
		* @version 1.0
		* @date October 2013
		*
		*/
		class IEmotionModifier
		{
		public:
			virtual ~IEmotionModifier(){}
			/**
			* @brief Evaluation
			*/
			virtual Emotion EvaluateEmotion(const Trait* trait, const Emotion* emo)const;

		};
	}
}