#ifndef AFFORDANCE_MANAGER_H
#define AFFORDANCE_MANAGER_H

#include <vector>
#include <map>
#include <string>
#include "BaseFactory.h"
#include "Affordance.h"
#include "Object.h"
#include "Drink.h"
#include "Relieve.h"
#include "Social.h"
#include "AffordanceEvaluator.h"
namespace AABSEngine
{
	namespace AI
	{
		/**
		 * @class AffordanceManager
		 * @brief Affordance manager, handles interactive object affordances
		 * @author AABS
		 * @version X
		 * @date October 2013
		 */
		class AffordanceManager
		{
		public:
			/**
			 * @brief get the singleton instance
			 */
			static AffordanceManager* Instance();

			/**
			 * @brief create a new affordance using the factory
			 */
			Affordance* CreateAffordance(std::string affType, int initialValue);

			/** 
			* @brief Gets a vector of the object types which satisfy this affordance
			*/
			const std::vector<std::string>* GetTypesByAffordance(std::string affordance) const;

			/**
			* @brief Returns an affordance evaluator object.
			*/
			AffordanceEvaluator* GetAffordanceEvaluator(std::string affordance);

			/**
			* @brief Registers a particular object type as being able to provide an affordance.
			*/
			bool RegisterAffordanceProvider(std::string affordance, std::string type);
		private:
			/**
			* @brief default private constructor
			*/
			AffordanceManager();

			static AffordanceManager* m_singleton; ///< singletone pointer

			std::map<std::string, std::vector<std::string>> m_affordanceObjectList;

			Utility::Factory<Affordance> m_affordanceFactory; ///< factory to create affordances
		};
	}
}

#endif