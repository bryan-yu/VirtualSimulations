#pragma once

#include <vector>
#include "Point3.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "PriorityQ.h"

namespace AABSEngine
{
	namespace Core
	{
		class GameObject;
	}

	namespace Physics
	{
		struct Manifold;

		/**
		 * @class PResolver
		 *
		 * @brief Physics resolution class
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class PResolver
		{
		public:
			~PResolver();

			PResolver();

			/**
			** @brief Add new manifold
			**/
			void AddCollision(AABSEngine::Core::GameObject* o1, AABSEngine::Core::GameObject* o2, AABSEngine::Core::Vector3 nB, Decimal pB, 
				const AABSEngine::Core::Point3& worldOnA, const AABSEngine::Core::Point3& worldOnB);

			/**
			** @brief Clear all collision data
			**/
			void ClearCollisions();

			/**
			** @brief Perform penetration resolution
			** @param re-iterations
			**/
			void ResolveCollisions(int reiterations);

			/**
			** @brief Return total manifolds
			** @return total contacts
			**/
			int TotalContacts()const { return m_contacts.size(); }
			
			static bool Sort(Manifold* mf1, Manifold* mf2);


		protected:	
			void FirstPass();

			virtual void ApplyLinearChange(Manifold* mf);

			virtual void ApplyPenetrationChange(Manifold* mf);

			std::vector<Manifold*> m_contacts;

			AABSEngine::Utility::IndexedPQ<Manifold*> m_contactQ;;
		};


	}


}