#pragma once 

#include "types.h"
#include <vector>

namespace AABSEngine
{
	namespace Core
	{
		class GameObject;
		class Point3;
		class Vector3;
	}

	namespace Physics
	{
		struct Manifold;

		/**
		 * @class ManifoldBag
		 *
		 * @brief 
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class ManifoldBag
		{
		private:
			typedef std::vector<Manifold*> MFContainer;

			MFContainer m_bag1;

			MFContainer m_bag2;

			/**
			** @brief Find existing contact manifold and return it wrapped in vector iterator
			** @param GameObject1
			** @param GameObject2
			** @return end of vector if not found, else an iterator pointing to the manifold object
			**/
			MFContainer::iterator FindExisting(AABSEngine::Core::GameObject* o1, AABSEngine::Core::GameObject* o2);

		public:
			Manifold* operator[](int index);
			const Manifold* operator[](int index)const;

			ManifoldBag();

			~ManifoldBag();

			/**
			** @brief Return total items in the bag of manifolds
			**/
			size_t Items()const { return m_bag1.size(); }

			/**
			** @brief Return contact manifold bag
			** @return m_bag by ref
			**/
			MFContainer& GetBag() { return m_bag1; }

			/**
			** @brief Add new batch of contact data to bag as a manifold, if exists, then pick one with greater penetration dist
			** @param GameObject1
			** @param GameObject2
			** @param collision normal on B  i.e.  |A|<-----|B|
			** @param penetration depth into b
			** @param world contact position on object/shape A
			** @param world contact position on object/shape B
			**/
			void Put(AABSEngine::Core::GameObject* o1, AABSEngine::Core::GameObject* o2, AABSEngine::Core::Vector3 nB, Decimal pB, 
				const AABSEngine::Core::Point3& worldOnA, const AABSEngine::Core::Point3& worldOnB);

			/**
			** @brief Remove existing manifold in bag(order matters) 
			** @param GameObject1
			** @param GameObject2
			** @return true if suceeded, else false
			**/
			bool Discard(AABSEngine::Core::GameObject* o1, AABSEngine::Core::GameObject* o2);

			/**
			** @param safely delete manifold objects and empty out all contents
			**/
			void Empty();
		};
	}
}