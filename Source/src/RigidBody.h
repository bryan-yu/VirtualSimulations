#pragma once

#include <string>
#include "OgreBulletCollisionsObject.h"

#include "Point3.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix3.h"

namespace AABSEngine
{
	namespace Physics
	{
		/**
		 * @class RigidBody
		 *
		 * @brief Rigid body class
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class RigidBody
		{
		public:

			/**
			 * @brief parameterized constructor
			 * @param ogre Node object
			 */
			RigidBody(OgreBulletCollisions::Object *input, Decimal mass, Decimal in_linearDamping = 1.0f, Decimal in_angularDamping = 1.0f);

			/**
			 * @brief default destructor
			 */
			~RigidBody();

			/**
			** @brief Set linear damping
			** @param damping factor
			**/
			void SetLinearDamping(Decimal damping);

			/**
			** @brief Retrieve linear damping value
			** @return linear damping by value
			**/
			Decimal GetLinearDamping()const;

			/**
			** @brief set angular damping factor 
			** @param angular damping 
			**/
			void SetAngularDamping(Decimal damping);

			/**
			** @brief Get angular damping
			** @return angular damping by value
			**/
			Decimal GetAngularDamping()const;

			/**
			* @brief get the mass of the object 
			* @return mass by value
			*/
			Decimal GetMass() const;

			/**
			** @brief get inverse mass
			** @return inverse mass, if mass is 0, then this returns 0 to prevent divide by 0
			**/
			Decimal GetInverseMass()const;

			/**
			 * @brief set the mass for this object and also updates the inverse mass value
			 * @param mass 
			 */
			void SetMass(Decimal mass);

			/**
			** @brief Set inertia tensor of the rigid body and also updates the inverse inertia tensor
			** @param inertia tensor
			**/
			void SetITensor(const AABSEngine::Core::Matrix3& tensor);
			
			/**
			** @brief Retrieve an inverse of this inertia tensor
			** @return inverse of current inertia tensor
			**/
			AABSEngine::Core::Matrix3 GetInverseITensor()const;

			/**
			** @brief Retrieve current inertia tensor
			** @return Inertia tensor matrix3x3 by reference
			**/
			const AABSEngine::Core::Matrix3& GetITensor()const;


			/**
			 * @brief get the linear velocity
			 * @return linear velocity by const reference
			 */
			const AABSEngine::Core::Vector3& GetLinearVelocity()const;

			/**
			 * @brief set the linear velocity
			 * @param linear velocity
			 */
			void SetLinearVelocity(const AABSEngine::Core::Vector3& in_velocity);

			/**
			 * @brief get the angular velocity
			 * @return angular velocity by const reference
			 */
			const AABSEngine::Core::Vector3& GetAngularVelocity()const;

			/**
			 * @brief set the angular velocity
			 * @param angular velocity
			 */
			void SetAngularVelocity(const AABSEngine::Core::Vector3& in_velocity);

			/**
			 * @brief get the center of mass
			 * @return center of mass position by const reference
			 */
			const AABSEngine::Core::Point3& GetCOM()const;

			/**
			 * @brief set the center of mass
			 * @param center of mass
			 */
			void SetCOM(const AABSEngine::Core::Point3& centerOfMass);

			/**
			 * @brief Get the ogre bullet collisions object
			 * @return pointer to underlying ogre collision object 
			 */
			OgreBulletCollisions::Object * GetCollisionObject() { return m_physObject; }

			/**
			** @brief Set linear acceleration
			** @param acceleration
			**/
			void SetLinearAcceleration(const AABSEngine::Core::Vector3& accel);

			/**
			** @brief Add linear velocity scaled by 't'
			** @param linear velocity
			** @param scale
			**/
			void AddLinearVelocity(const AABSEngine::Core::Vector3& veloc, Decimal t=1.0);

			/**
			** @brief Add angular velocity scaled by 't'
			** @param angular velocity
			** @param scale
			**/
			void AddAngularVelocity(const AABSEngine::Core::Vector3& veloc, Decimal t=1.0);

			/**
			** @brief retrieve linear acceleration
			** @return linear acceleration by const reference
			**/
			const AABSEngine::Core::Vector3& GetLinearAcceleration()const;

			/**
			** @brief set accumulated force
			** @param force
			**/
			void SetForceAccum(const AABSEngine::Core::Vector3& force);

			/**
			** @brief set accumulated torque
			** @param torqued
			**/
			void SetTorqueAccum(const AABSEngine::Core::Vector3& torque);

			/**
			** @brief Return accumulated force
			** @return force accumulation by const reference
			**/
			const AABSEngine::Core::Vector3& GetForceAccum()const;

			/**
			** @brief Return accumulated torque
			** @return torque accumulation by const reference
			**/
			const AABSEngine::Core::Vector3& GetTorqueAccum()const;

			/**
			** @brief Set world position if a physics object exists 
			** @param world position
			**/
			void SetWorldPosition(const AABSEngine::Core::Point3& worldPos);

			/**
			** @brief Retrieve world position of physics object
			** @return world position by value if physics object exists, else 0,0,0
			**/
			AABSEngine::Core::Point3 GetWorldPosition()const;

			/**
			** @brief Retrieve acceleration from the last frame
			** @return m_previousAcceleration
			**/
			const AABSEngine::Core::Vector3& GetPreviousAcceleration()const;

			/**
			** @brief Set m_previousAcceleration to m_linearAcceleration
			**/
			void SetPreviousAcceleration(const AABSEngine::Core::Vector3& accel);

			/**
			** @brief Set world position if a physics object exists 
			** @param world position
			**/
			void SetOrientation(const AABSEngine::Core::Quaternion& orient);

			/**
			** @brief Retrieve world position of physics object
			** @return world position by value if physics object exists, else 0,0,0
			**/
			AABSEngine::Core::Quaternion GetOrientation()const;

			/**
			** @brief Get linear momentum
			** @return linear momentum by const reference
			**/
			const AABSEngine::Core::Vector3& GetLinearMomentum()const;
			
			/**
			** @brief Set linear momentum
			** @param linear momentum
			**/
			void SetLinearMomentum(const AABSEngine::Core::Vector3& momentum);

			/**
			** @brief Get angular momentum
			** @return angular momentum by const reference
			**/
			const AABSEngine::Core::Vector3& GetAngularMomentum()const;
			
			/**
			** @brief Set Angular momentum
			** @param angular momentum
			**/
			void SetAngularMomentum(const AABSEngine::Core::Vector3& momentum);

			/**
			** @brief Clear accumulated force and torques of this rigid body
			**/
			void ClearAccumulators();

			/**
			** @brief Apply damping coefficients on linear and angular velocities 
			** @param duration
			**/
			void ApplyVelocityDamping(Decimal duration);

			/**
			** @brief Set look-up index of material id(used for restitution or friction calculations)
			** @param id of material
			**/
			void SetMaterialID(int id);

			/**
			** @brief Get material ID
			** @return material id by value
			**/
			int GetMaterialID()const;

			/**
			** @brief Transform a local point to world coordinate point, useful in situation when applying forces on a point etc
			** @param local point 
			** @param store world point
			**/
			void BodyToWorldPoint(const AABSEngine::Core::Point3& localPoint, AABSEngine::Core::Point3& worldPoint);

			/**
			** @brief Transform world to local coordinate point, useful in situation when applying forces on a point etc
			** @param world point
			** @param store local point
			**/
			void WorldToBodyPoint(const AABSEngine::Core::Point3& worldPoint, AABSEngine::Core::Point3& localPoint);

			/**
			** @brief Transform a local vector to world coordinate vector, useful in situation when applying forces on a point etc
			** @param local vector 
			** @param store world vector
			**/
			void BodyToWorldDirection(const AABSEngine::Core::Vector3& localDirect, AABSEngine::Core::Vector3& worldDirect);

			/**
			** @brief Transform world to local coordinate vector, useful in situation when applying forces on a point etc
			** @param world vector
			** @param store local vector
			**/
			void WorldToBodyDirection(const AABSEngine::Core::Vector3& worldDirct, AABSEngine::Core::Vector3& localDirect);

			/**
			** @brief Allow us to retrieve a world matrix from the current body-space inverse inertia tensor
			** @param rotation quaternion
			** @param body/local tensor
			** @param store resulting world tensor
			**/
			void WorldInverseTensor(AABSEngine::Core::Matrix3& iWorldTensor);

			/**
			 * @brief Adds a force to the force accumulator, to be applied during this update.
			 * TODO ~~~ maybe return bool
			 */
			void AddForce(AABSEngine::Core::Vector3& force);
			
			/**
			 * @brief Adds a force acting on a particular point, this results in a a force and torque being added as appropriate.
			 */
			void AddForceAtPoint(AABSEngine::Core::Vector3& force, AABSEngine::Core::Point3& point);

			/**
			 * @brief Adds a Torque to the torque accumulator, to be applied during this update.
			 * TODO ~~~ maybe return bool
			 */
			void AddTorque(AABSEngine::Core::Vector3& torque);

			/**
			 * @brief mark this rigid body as static object
			 */
			void SetStatic(bool staticStatus);

			/**
			 * @brief check whether this rigid body is a static object
			 */
			bool IsStatic() const;

			/**
			 * brief set the speed threshold for both linear and angular velocity
			 */
			void SetVelocityThreshold(float forLinear, float forAngular);

			/**
			 * @brief get the linear velocity threshold
			 * @retval linear velocity threshold in units/second
			 */
			float GetLinearVelocityThreshold();

			/**
			 * @brief get the angular velocity threshold
			 * @retval angular velocity threshold in units/second
			 */
			float GetAngularVelocityThreshold();

			/**
			 * @brief check if the object is sleeping
			 * @retval true/false if the object is asleep
			 */
			bool IsAsleep();

			/**
			 * @brief make the rigid body to sleep
			 */
			void Sleep();

			/**
			 * @brief awaken the rigid body to respond for physics
			 */
			void Awaken();

			/**
			 * @brief mark this rigid body as kinematic object
			 */
			void SetKinematic(bool kinematicStatus);

			/**
			 * @brief check whether this rigid body is a kinematic object
			 */
			bool IsKinematic() const;

			/**
			 * @brief set the previous position
			 * @param point3
			 */
			void SetPreviousWorldPosition(const Core::Point3 &prev);

			/**
			 * @brief Retrieve the previous position of the object
			 */
			AABSEngine::Core::Point3 GetPreviousWorldPosition()const;

		private:

			OgreBulletCollisions::Object *m_physObject; ///< ogre bullet collision object

			Decimal m_mass; ///< the mass of the object in kg
			Decimal m_inverseMass; ///< the inverse mass

			Decimal m_linearDamping; ///< to simulate friction-ish behaviour
			Decimal m_angularDamping; ///< to simulate friction-ish behaviour

			AABSEngine::Core::Vector3 m_linearVelocity; ///< linear velocity
			AABSEngine::Core::Vector3 m_angularVelocity; ///< angular velocity

			float m_minLinearVelocityMagnitude; ///< minimum linear speed for this object otherwise this rigid body will be marked to be at "rest" - using units/second -> requires deltaTime
		    float m_minAngularVelocityMagnitude; ///< same as above but for angular velocity
			
			AABSEngine::Core::Vector3 m_forceAccum; ///< force accumulator
			AABSEngine::Core::Vector3 m_torqueAccum; ///< torque accumulator

			AABSEngine::Core::Vector3 m_previousAcceleration; ///< use to handle jitter with resting contacts - NYI
			AABSEngine::Core::Vector3 m_linearAcceleration; ///< linear acceleration

			AABSEngine::Core::Vector3 m_linearMomentum; ///< linear momentum - NOT USED
			AABSEngine::Core::Vector3 m_angularMomentum; ///< angular momentum - NOT USED

			AABSEngine::Core::Point3 m_centerOfMass; ///< based on local coordinate of the object	

			AABSEngine::Core::Matrix3 m_inertiaTensor; ///< inertia tensor 3x3 matrix
			AABSEngine::Core::Matrix3 m_inverseInertiaTensor; ///< inverse inertia tensor

			AABSEngine::Core::Point3 m_previousPosition; ///< previous frame position

			bool m_static; ///< indicate if this is a static object
			bool m_kinematic; ///< indicate if this is a kinematic object
			int m_materialID; ///< material ID to be used to solve for coefficient of restitution
			bool m_sleep; ///< to sleep/awaken the object to respond with collision
		};
	}
}