#ifndef COLLISION_SPHERE_H
#define COLLISION_SPHERE_H

#include "CollisionObject.h"
#include "OgreBulletCollisionsSphereShape.h"

namespace AABSEngine
{
	namespace Physics
	{
		/**
		 * @class CollisionSphere
		 *
		 * @brief Collision sphere object for physics simulations
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class CollisionSphere : public CollisionObject
		{
		public:
			/**
			 * @brief constructor
			 * @param mass and radius
			 */
			CollisionSphere(float mass, float radius);

			/**
			 * @brief destructor
			 */
			~CollisionSphere();
		
			/**
			 * @brief create a new ogre bt box shape
			 */
			virtual OgreBulletCollisions::CollisionShape *CreateOgreBTShape();

		private:
			/**
			 * @brief calculate the inertia tensor
			 */
			virtual void CalculateInertiaTensor();

			float m_radius; ///< radius of the cylinder
		};
	}
}

#endif