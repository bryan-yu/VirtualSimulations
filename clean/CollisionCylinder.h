#ifndef COLLISION_CYLINDER_H
#define COLLISION_CYLINDER_H

#include "CollisionObject.h"
#include "OgreBulletCollisionsCylinderShape.h"

namespace AABSEngine
{
	namespace Physics
	{
		/**
		 * @class CollisionCylinder
		 *
		 * @brief Collision cylinder object for physics simulations
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class CollisionCylinder : public CollisionObject
		{
		public:
			/**
			 * @brief constructor
			 * @param mass, radius and height
			 */
			CollisionCylinder(float mass, float radius, float height);

			/**
			 * @brief destructor
			 */
			~CollisionCylinder();
		
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
			float m_height; /// height of the box - y_axis
		};
	}
}

#endif