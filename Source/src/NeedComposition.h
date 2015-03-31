#pragma once

#include "PriorityQ.h"
#include "types.h"
#include <queue>
#include <vector>

namespace AABSEngine
{
	namespace AI
	{
		class Need;

		/**
		* @struct OrderByNeed
		*
		* @brief Order by need data
		*
		*/
		struct OrderByNeed
		{
		public:
			bool operator()(const Need* n1, const Need* n2);
		};

		typedef std::priority_queue<const Need*, std::vector<const Need*>, OrderByNeed> PrioritizedNeeds;
		typedef std::vector<Need*> NeedVector;

		/**
		* @class NeedComposition
		*
		* @brief Container of needs for agents
		*
		* @author AABS
		* @version X
		* @date October 2013
		*
		*/
		class NeedComposition
		{
		public:
			~NeedComposition();

			NeedComposition(){}

			/**
			** @brief Create a new need and place in container
			** @param look-up name
			** @param min
			** @param max
			** @param base
			** @return need object if not duplicate, else NULL
			**/
			template<class Type>
			Type* Create(std::string name, Decimal _min = 0.0, Decimal _max = 100.0, Decimal _base = 0.0);

			/** 
			** @brief Access an existing need in container if found
			** @param look-up name
			** @return type casted need object if found, else NULL
			**/
			Need* Access(std::string name);

			/** 
			** @brief Access an existing need in container if found
			** @param look-up name
			** @return type casted need object if found, else NULL
			**/
			const Need* Access(std::string name)const;

			/**
			** @brief Retrieve prioritized needs
			** @param needs priority queue
			** @param first 'x' needs 
			**/
			void Access(PrioritizedNeeds& needs, size_t x);

			/**
			** @brief Remove an existing need
			** @param look-up name
			** @return true if found and deleted, else false
			**/
			bool Remove(std::string name);

			/**
			** @brief Do a full clean-up by deleting all current needs
			**/
			void Clear(); 

			/**
			** @brief Perform any need evaluations here
			** @param time
			**/
			void Update(Decimal t=0);

			/**
			*@brief Adds a need identified by the string. This need should have already been added to the NeedManager.
			*/
			void AddNeed(std::string name);

			/** 
			* @brief Returns reference to vector of needs.
			*/
			NeedVector& GetNeeds() { return m_needs; } /* TODO provide an iterator instead */


		private:

			NeedComposition(const NeedComposition&){}

			NeedComposition& operator=(const NeedComposition&){return *this;}
	

			/**
			** @brief Find an existing need
			** @param name
			** @return iterator to element
			**/
			NeedVector::iterator Find(std::string name);

			/**
			** @brief Find an existing need
			** @param name
			** @return const_iterator to element
			**/
			const NeedVector::const_iterator Find(std::string name)const;

			NeedVector m_needs;
		};

			
		template<class Type>
		Type* NeedComposition::Create(std::string _name, Decimal _min, Decimal _max, Decimal _base)
		{
			NeedVector::iterator itr = Find(_name);

			if(itr == m_needs.end())
			{				
				Type* need = new Type();

				if(!need) 
				{
					return 0; //error creating object occured
				}

				need->SetName(_name);

				need->SetMinimum(_min);
				
				need->SetMaximum(_max);
				
				need->SetBase(_base);

				need->ClampBase();
				
				m_needs.push_back(need);

				return need;
			}
			return 0;
		}


	}
}