#pragma once
#include "types.h"
#include "Point3.h"
#include "Vector3.h"

namespace AABSEngine
{
	namespace Core
	{
		class GameObject;
	}

	namespace Physics
	{

		/**
		 * @struct Manifold 
		 *
		 * @brief Manifold data
		 *
		 */
		struct Manifold
		{
		public:
			Manifold();

			Manifold(AABSEngine::Core::GameObject* o1, AABSEngine::Core::GameObject* o2, const AABSEngine::Core::Vector3& nB, Decimal pB, 
				const AABSEngine::Core::Point3& worldOnA, const AABSEngine::Core::Point3& worldOnB);
		

			AABSEngine::Core::GameObject* m_ob[2];

			AABSEngine::Core::Point3 m_worldCP[2];
			AABSEngine::Core::Vector3 m_linear[2];

			AABSEngine::Core::Vector3 m_nB;
			Decimal m_pB;
		};
	}

}