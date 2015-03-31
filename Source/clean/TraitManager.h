#pragma once

#include <map>
#include <string>
#include "types.h"
#include "Trait.h"

namespace AABSEngine
{
	namespace AI
	{
		/**
		 * @class TraitManager
		 *
		 * @brief Traits manager class
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class TraitManager
		{
		private:
			std::map<std::string, TraitDefinition> m_traitDefinitions;
		protected:
		public:
			TraitManager();
			bool Initialise();
			void AddTraitDefinition(TraitDefinition def);
			TraitDefinition GetTraitDefinition(std::string name);
		};
	}
}