#pragma once

#include "ForceGenerator.h"
#include "RigidBody.h"

namespace AABSEngine
{
	namespace Physics
	{
		/**
		 * @class ForceRegistration
		 *
		 * @brief 
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class ForceRegistration
		{
		private:

			ForceGenerator* m_generator;
			RigidBody* m_body;
		protected:
		public:
			~ForceRegistration();

			ForceRegistration();
			ForceRegistration(RigidBody* body, AABSEngine::Physics::ForceGenerator* generator);

			void Update(Decimal duration);
			void Clear();

			RigidBody* GetBody();
			bool operator==(const ForceRegistration& rhs) const;
			bool operator!=(const ForceRegistration& rhs) const;
		};
	}
}