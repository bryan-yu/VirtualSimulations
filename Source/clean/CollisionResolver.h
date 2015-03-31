#pragma once

#include "Object.h"
#include "Vector3.h"
#include "Point3.h"

namespace AABSEngine
{
	namespace Physics
	{
		/**
		 * @class CollisionResolver
		 *
		 * @brief Physics manager class
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class CollisionResolver
		{
		public:
			/**
			 * @brief collsion resolution for rigid body
			 */
			static void ResolveCollision(const Core::Point3 &contactA, const Core::Point3 &contactB, const Core::Vector3 &contactNormal, Core::GameObject *objectA, Core::GameObject *objectB);
		};
	}
}