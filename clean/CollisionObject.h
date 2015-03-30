#ifndef COLLISION_SHAPE_H
#define COLLISION_SHAPE_H

#include "Vector3.h"
#include "Matrix3.h"
#include "ITensorCalculator.h"

namespace AABSEngine
{
	namespace Physics
	{
		/**
		 * @class CollisionObject
		 * @brief collision object abstract class
		 */
		class CollisionObject
		{
		public:
			/**
			 * @brief set mass
			 */
			void SetMass(float const mass);

			/**
			 * @brief get mass
			 */
			float GetMass() const;

			/**
			 * @brief get the inertia tensor
			 */
			AABSEngine::Core::Matrix3 GetInertiaTensor() const;

			/**
			 * @brief get a collision shape
			 */
			virtual OgreBulletCollisions::CollisionShape *CreateOgreBTShape() = 0;

		protected:

			float m_mass; ///< mass of the object
			AABSEngine::Core::Matrix3 m_inertiaTensor;

		private:
			/**
			 * @brief calculate the inertia tensor for this shape - to be overriden by the derived class
			 */
			virtual void CalculateInertiaTensor() = 0;
		};
	}
}

#endif