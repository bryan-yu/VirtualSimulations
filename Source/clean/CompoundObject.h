#ifndef COMPOUND_OBJECT_H
#define COMPOUND_OBJECT_H

#include <string>
#include <vector>

#include "OgreBulletCollisions.h"
#include "OgreBulletCollisionsObject.h"
#include "OgreBulletCollisionsCompoundShape.h"
#include "CollisionObject.h"
#include "Point3.h"
#include "Matrix3.h"
#include "Quaternion.h"
#include "ITensorCombiner.h"

namespace AABSEngine
{
	namespace Physics
	{
		/**
		 * @struct CompoundChildObjectData 
		 *
		 * @brief Compound child object data
		 *
		 */
		struct CompoundChildObjectData
		{
			CollisionObject *m_object;
			Core::Point3 m_position;
			Core::Quaternion m_orientation;

		};

		/**
		 * @class CollisionObject
		 *
		 * @brief collision object class that will be created by reading the xml file
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class CompoundObject
		{
		public:

			/**
			 * @brief default constructor
			 */
			CompoundObject();

			/**
			 * @brief default destructor
			 */
			~CompoundObject();

			/**
			 * @brief get the ogre bullet collision object as a new copy
			 * @retval ogre bullet collision object
			 */
			OgreBulletCollisions::CollisionShape *CreateOgreBTCompoundShape();

			/**
			 * @brief add child shape for the compound shape
			 * @param the child shape and its position
			 */
			void AddChildShape(CollisionObject *childObject, Core::Point3 localPosition, Core::Quaternion localOrientation);

			/**
			 * @brief calculate the inertia tensor, center of mass, also reposition the child objects based on the center of mass
			 */
			void SetupPhysics(bool isStatic, bool isKinematic);

			/**
			 * @brief get the total mass for this object
			 * @retval total mass in kg as float
			 */
			float GetMass();

			/**
			 * @brief get the inertia tensor for this object
			 * @retval Matrix 3x3
			 */
			AABSEngine::Core::Matrix3 GetInertiaTensor();

			/**
			 * @brief get the center of mass for this object (local coordinate)
			 * @retval center of mass of the compound object
			 */
			AABSEngine::Core::Point3 GetCenterOfMass();

			/**
			 * @brief check whether this object is a static object
			 */
			bool GetIsStatic();

			/**
			 * @brief check whether this object is a kinematic object
			 */
			bool GetIsKinematic();

			/**
			 * @brief set the linearDamping for the compound object
			 */
			void SetLinearDamping(float damping);

			/**
			 * @brief get the linear damping for this object
			 * @retval linear damping as float
			 */
			float GetLinearDamping();

			/**
			 * @brief set the angular damping for the object
			 */
			void SetAngularDamping(float damping);

			/**
			 * @brief get angular damping for this object
			 * @retval angular damping as float
			 */
			float GetAngularDamping();

			/**
			 * @brief set the velocity threshold
			 */
			void SetVelocityThreshold(float linear, float angular);

			/**
			 * @brief get the linear velocity threshold
			 */
			float GetLinearThreshold();

			/**
			 * @brief get the angular velocity threshold
			 */
			float GetAngularThreshold();

		private:
			std::vector<CompoundChildObjectData*> m_shapeList; ///< the list of collision objects
			AABSEngine::Core::Matrix3 m_inertiaTensor; ///< the combined inertia tensor

			float m_mass; ///< the mass of the compound object
			float m_linearDamping; ///< linear damping property
			float m_angularDamping; ///< angular damping property
			AABSEngine::Core::Point3 m_centerOfMass; ///< the combined center of mass

			bool m_static; ///< to mark if this object is static or not
			bool m_kinematic; ///< to mark if this is a kinematic object

			float m_linearThreshold; ///< linear velocity threshold
			float m_angularThreshold; ///< angular velocity threshold
		};
	}
}

#endif