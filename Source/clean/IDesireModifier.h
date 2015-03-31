#pragma once
#include "types.h"
#include "Evaluator.h"

namespace AABSEngine
{
	namespace AI
	{
		class Trait;
		class Need;

		/**
		* @class IDesireModifier
		*
		* @brief Modifier used to affect desires/needs over time. (Not currently implemented)
		*
		* @author Bryan Yu
		* @version 1.0
		* @date October 2013
		*
		*/
		class IDesireModifier
		{
		public:
			virtual ~IDesireModifier(){}
			/**
			* @brief Evaluation
			*/
			virtual Decimal EvaluateDesire(const Trait* trait, const Need* need)const;
		};
	}
}