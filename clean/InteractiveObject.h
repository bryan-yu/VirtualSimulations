#ifndef INTERACTIVE_OBJECT_H
#define INTERACTIVE_OBJECT_H

#include "Affordance.h"
#include "Object.h"
#include "AffordanceManager.h"
#include <vector>
#include <string>

namespace AABSEngine
{
	namespace Core
	{
		/**
		 * @class InteractiveObject
		 *
		 * @brief Interface for interactive objects
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class InteractiveObject : public GameObject
		{
		public:
			/**
			 * @brief default constructor
			 */
			InteractiveObject();

			/**
			 * @default destructor
			 */
			~InteractiveObject();

			/**
			 * @brief add an affordance to this object
			 */
			virtual void AddAffordance(std::string affordanceName, int initialValue);

			/**
			 * @brief check if this object has a particular affordance
			 * @retval true/false
			 */
			virtual bool HasAffordance(std::string name);

			/**
			 * @brief get an affordance from this object
			 * @retval affordance pointer or NULL if not found
			 */
			virtual AI::Affordance* GetAffordance(std::string name);

			/**
			 * @brief get a list of affordances for this object
			 */
			virtual std::vector<AI::Affordance*> GetAffordances();

			/**
			* @brief Adds an affordance modifier to be actioned when an agent uses this object.
			*/
			void AddAffordanceModifier(std::string affordance, int mod);

			/**
			* @brief Action affordance modifier - alters the affordance by the set amount
			*/
			void ActionAffordanceModifier(std::string affordance);

			/**
			* @brief Resolve affordance modifier - reverses the effect of ActionAffordanceModifier
			*/
			void ResolveAffordanceModifier(std::string affordance);

		private:
			std::map<std::string, int> m_affordanceModifiers;
			std::vector<AI::Affordance*> m_affordances; ///< list of affordances for this object
		};
	}
}

#endif