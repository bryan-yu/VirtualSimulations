#ifndef COLLISION_BOX_H
#define COLLISION_BOX_H

#include "CollisionObject.h"
#include "OgreBulletCollisionsBoxShape.h"

namespace AABSEngine
{
	namespace Physics
	{
		/**
		 * @class CollisionBox
		 *
		 * @brief Collision box object for physics simulations
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class CollisionBox : public CollisionObject
		{
		public:
			/**
			 * @brief constructor
			 * @param mass, length, width, height
			 */
			CollisionBox(float mass, float width, float height, float length);

			/**
			 * @brief destructor
			 */
			~CollisionBox();
		
			/**
			 * @brief create a new ogre bt box shape
			 */
			virtual OgreBulletCollisions::CollisionShape *CreateOgreBTShape();

		private:
			/**
			 * @brief calculate the inertia tensor
			 */
			virtual void CalculateInertiaTensor();

			float m_width; ///< width of the box - x_axis
			float m_height; /// height of the box - y_axis
			float m_length; ///< length of the box - z_axis
		};
	}
}

#endif