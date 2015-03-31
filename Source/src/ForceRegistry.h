#pragma once

#include <vector>
#include "ForceRegistration.h"
#include "RigidBody.h"

namespace AABSEngine
{
	namespace Physics
	{
		/**
		 * @class ForceRegistry
		 *
		 * @brief 
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class ForceRegistry
		{
		private:
			std::vector<AABSEngine::Physics::ForceRegistration> m_registrations;
		protected:
		public:
			~ForceRegistry();
			ForceRegistry();
			void RegisterForce(AABSEngine::Physics::ForceGenerator* generator, RigidBody* body);
			void DeRegisterForce(AABSEngine::Physics::ForceGenerator* generator, RigidBody* body);
			void DeRegisterAllForces(RigidBody* body); 
			void Update(Decimal duration);
		};
	}
}