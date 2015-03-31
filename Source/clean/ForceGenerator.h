#pragma once

#include "RigidBody.h"

namespace AABSEngine
{
	namespace Physics
	{
		/**
		 * @class ForceGenerator
		 *
		 * @brief Physics force generator
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class ForceGenerator
		{
		private:
		protected:
		public:
			/**
			* @brief Update force applied
			* @return void
			*/
			virtual void UpdateForce(RigidBody* body, Decimal duration) = 0;
		};
	}
}