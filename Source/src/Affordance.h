#ifndef AFFORDANCE_H
#define AFFORDANCE_H

#include <string>
#include <typeinfo>

namespace AABSEngine
{
	namespace AI
	{
		/**
		* @class Affordance
		* @brief affordance class for game objects that are interactable
		* @author Alexander Arif
		*/
		class Affordance
		{
		public:
			/**
			 * @brief return the current value of the affordance
			 */
			int GetAffordanceCurrentValue();

			/**
			* @brief Get Max Value
			*/
			int GetAffordanceMaxValue();

			/**
			 * @brief initialise the affordance
			 */
			void Initialize(std::string, int initialValue);

			/**
			 * @brief add an affordance value to this object
			 */
			void AddAffordance(int amount);

			/**
			 * @brief reduce the current affordance of this object by a certain amount
			 */
			void ReduceAffordance(int amount);

			/**
			 * @brief get the name of the affordances
			 */
			std::string GetName();

		protected:
			int m_baseValue; ///< base value of the affordance (the maximum value that this object can have)
			int m_currentValue; ///< current value of the affordance
			std::string m_name; ///< the type of the affordance
      
			/** 
			* @brief Restricts affordance value to the appropriate range.
			*/
			void ClampAffordance();
		};
	}

}

#endif