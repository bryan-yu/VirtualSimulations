#pragma once

#include <string>
#include "types.h"

namespace AABSEngine
{
	namespace AI
	{
	/**
	* @struct TraitDefinition
	*
	* @brief trait data
	*
	*/
	struct TraitDefinition
    {
      std::string name;
      std::string need;
      Decimal bias;
    };

	/**
	* @class Trait
	*
	* @brief Personality traits for agents
	*
	* @author AABS
	* @version X
	* @date October 2013
	*
	*/
	class Trait
		{
		public:
			Trait(int bias = 0);

			Trait(const Trait&);

			Trait& operator=(const Trait&);

			/**
			* @brief Return trait bias
			*/
			Decimal GetBias()const;

			/**
			* @brief Return trait name
			*/
			std::string GetName()const;

			/**
			* @brief Return need
			*/
			std::string GetNeed() const;

			/**
			* @brief Set need
			*/
			void SetNeed(std::string);

			/**
			* @brief Set bias
			*/
			void SetBias(Decimal bias);

		protected:
			friend class Personality;

			/**
			* @brief Set name
			*/
			void SetName(std::string name); 

			std::string m_name;

			std::string m_need;

			Decimal m_bias;
		};
	}
}