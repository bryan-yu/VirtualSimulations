#pragma once

#include "types.h"
#include "Evaluator.h"

namespace AABSEngine
{
	namespace AI
	{
		/**
		* @struct NeedDefinition
		*
		* @brief needs data
		*
		*/
		struct NeedDefinition
		{
		  std::string name;
		  int max;
		  int min;
		  int base;
		  std::string affordance;
		  std::string evaluatorFunction;
		  int evaluatorFunctionParam; /* TODO more generic for future expansion */
		  int lowWaterMark; /* threshold to reach before starting action - percentage */
		  int highWaterMark; /* threshold to reach before stopping action - percentage */
		};

		/**
		* @class Need
		*
		* @brief Handling of an agent's needs/desires
		*
		* @author AABS
		* @version X
		* @date October 2013
		*
		*/
		class Need
		{
		public:
			Need(Decimal _min = 0.0, Decimal _max = 100.0, Decimal _base = 0.0);

		    Need(NeedDefinition need);

			Need(const Need& other);

			Need& operator=(const Need& other);

			/**
			** @brief Return base(current) value of need
			** @return m_base
			**/
			Decimal GetBase()const;

			/**
			** @brief Return max value of need
			** @return m_maximum
			**/
			Decimal GetMaximum()const;

			/**
			** @brief Return min value of need
			** @return m_minimum
			**/
			Decimal GetMinimum()const;

			/**
			* @brief Return the range between maximum and minimum.
			* return m_maximum - m_minimum
			*/
			Decimal GetRange() const;

			/**
			** @brief Get name
			** @return m_name
			**/
			std::string GetName()const;

			/**
			** @brief Set min value of need(if _min > max, then the values swap(min,max))
			** @param min
			**/
			void SetMinimum(Decimal _min);

			/**
			** @brief Set min value of need(if _max < min, then the values swap(min,max))
			** @param max
			**/
			void SetMaximum(Decimal _max);

			/**
			** @brief Set name
			** @param name
			**/
			void SetName(std::string name);

			/**
			** @brief Set base value
			** @param base value(should call ClampBase() after)
			**/
			void SetBase(Decimal _base);

			/**
			** @brief Apply linear decay of current need
			** @param delta
			** @param duration in time
			**/
			void ApplyDecay(Decimal x, Decimal duration=1.0);

			/**
			** @brief Apply growth of current need
			** @param delta
			** @param duration
			**/
			void ApplyGrowth(Decimal x, Decimal duration=1.0);

			/**
			** @brief Ensures base value is between min and max
			**/
			void ClampBase();

			/**
			** @brief to be implemented by derived needs
			** @param time
			**/
		    virtual void Evaluate(Decimal t=0) { SetBase(m_evaluation(this)); };

			/**
			** @Brief Set evaluator functor
			** @param evaluator functor to calculate new base need per frame
			**/
			template<class Functor>
			void SetEvaluator(Functor functor);

			/**
			* @brief Returns the type of affordance that satisfies this need 
			*/
			std::string GetSatisfyingAffordance() const;

			/**
			* @brief Sets the threshold to reach before taking action as a percentage.
			*/
			void SetLowWaterMark(Decimal mark);

			/**
			* @brief Gets the threshold to reach before taking action as a percentage.
			*/
			Decimal GetLowWaterMark() const;

			/**
			* @brief Sets the threshold to reach before leaving action as a percentage.
			*/
			void SetHighWaterMark(Decimal mark);

			/**
			* @brief Gets the threshold to reach before leaving action as a percentage.
			*/
			Decimal GetHighWaterMark() const;

		protected:

			Evaluator<const Need*, Decimal> m_evaluation;

			std::string m_name;

			Decimal m_maximum;

			Decimal m_minimum;

			Decimal m_base;

			Decimal m_lowWaterMark;
			Decimal m_highWaterMark;

			std::string m_affordance; /**< The name of the affordance which satisfies this need */
		};

		template<class Functor>
		void Need::SetEvaluator(Functor functor)
		{
			m_evaluation = functor;
		}
	}
}