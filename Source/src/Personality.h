#pragma once

#include <vector>
#include "TraitManager.h"
namespace AABSEngine
{
	namespace AI
	{
		struct Trait;

		/**
		* @class Personality
		*
		* @brief Personality of an agent
		*
		* @author AABS
		* @version X
		* @date October 2013
		*
		*/
		class Personality
		{
		public:
			template<class Type>
			Type* Create(std::string, std::string need, int bias);
      
		    template<class Type>
			Type* Create(TraitDefinition def);

			/**
			* @brief Access by trait name
			*/
			Trait* Access(std::string name);

			/**
			* @brief Access by need name
			*/
			Trait* AccessByNeed(std::string name);

			/**
			* @brief Access by trait name (constant return)
			*/
			const Trait* Access(std::string name)const;

			/**
			* @brief Remove trait by name
			*/
			bool Remove(std::string name);
		
			/**
			* @brief Remove all traits
			*/
			void Clear();

			std::vector<Trait*> GetTraits() { return m_traits; }

		private:
			std::vector<Trait*> m_traits;
		};

		template<class Type>
		Type* Personality::Create(TraitDefinition def)
		{
			if (!Access(def.name))
			{
			Type* trait = new Type();
			trait->SetBias(def.bias);
			trait->SetNeed(def.need);
			trait->SetName(def.name);
			m_traits.push_back(trait);
			}
			return NULL;
		}

		template<class Type>
		Type* Personality::Create(std::string name, std::string need, int bias)
		{
			if(!Access(name))
			{
				Type* trait = new Type();

				trait->SetBias(bias);
				trait->SetNeed(need);
				trait->SetName(name);

				m_traits.push_back(trait);
			}
			return NULL;
		}
	}
}