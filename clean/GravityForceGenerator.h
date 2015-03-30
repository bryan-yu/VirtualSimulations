#pragma once

#include "ForceGenerator.h"
#include "Vector3.h"

namespace AABSEngine
{
	namespace Physics
	{
		/**
		 * @class GravityForceGenerator
		 *
		 * @brief 
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class GravityForceGenerator: public ForceGenerator
		{
		private:
			AABSEngine::Core::Vector3 m_gravity;
		protected:
		public:
			GravityForceGenerator(AABSEngine::Core::Vector3 gravity);
			void UpdateForce(RigidBody* body, Decimal duration);
		};
	}
}
