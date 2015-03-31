#pragma once

#include <vector>
#include <map>

#include <OgreRoot.h>
#include "OgreBulletCollisionsWorld.h"
#include "OgreBulletCollisionsObject.h"
#include "OgreBulletCollisionsMeshToShapeConverter.h"

#include "CompoundObject.h"
#include "CollisionBox.h"
#include "CollisionCylinder.h"
#include "CollisionSphere.h"

#include "Vector3.h"
#include "Point3.h"
#include "ForceRegistry.h"
#include "ManifoldBag.h"

#include "GravityForceGenerator.h"

namespace AABSEngine
{
	namespace Core
	{
		class GameObject;
	}

	namespace Physics
	{
		const Decimal DESIRED_TIMESTEP = (1/60.0f);

		class RigidBody;

		/**
		 * @class 
		 *
		 * @brief Physics manager class
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class PhysicsManager
		{
		public:

			enum CollisionShape { 
				SPHERE=0,
				BOX,
				TRIMESH,
				CYLINDER,
				CONVEX_DECOMPOSITION,
				COMPOUND
			};

			enum CollisionMask {
				COL_NOTHING = 0, ///< Collide with nothing
				COL_NORMAL = 1<<0, ///< Collide with normal objects
				COL_ENVIRONMENT = 1<<1, ///< Collide with environment
			};

			void ConvertToQuaternion(float &w, float &x, float &y, float &z);

			/**
			 * @brief get the singleton instance
			 */
			static PhysicsManager* Instance();

			/**
			 * @brief setup the physics world
			 * @param ogre scene manager to add ogrebullet collision object
			 * @param the bounding box (min and max vertices) to encapsulate the physics world - needed by bullet
			 */
			void SetupPhysicsWorld(Ogre::SceneManager* in_sceneMgr, int minx = -1000, int miny = -1000, int minz = -1000, int maxx = 1000, int maxy = 1000, int maxz = 1000);

			/**
			 * @brief add object to the physics world
			 */
			void AddObject(AABSEngine::Core::GameObject *input, std::string collisionObject, Core::Point3 initPosition = Core::Point3(0,0,0), Core::Quaternion initRotation = Core::Quaternion::IDENTITY, int collisionGroup = 1, int collisionFilter = -1);

			/**
			 * @brief add object to the physics world
			 */
			void AddSceneObject(AABSEngine::Core::GameObject *input, Ogre::Entity *entity);

			/**
			 * @brief update the physics world
			 */
			void Update(Decimal deltaTime);

			/**
			 * @brief get the collision world for debugging
			 */
			OgreBulletCollisions::CollisionsWorld *GetCollisionWorld() { return m_collisionWorld; }

			/**
			 * @brief Adds a force generator to the map
			 */
			bool AddForceGenerator(std::string name, ForceGenerator* gen);

			/**
			 * @brief Registers the given force generator by name with the rigid body.
			 */
			bool RegisterRigidBodyWithForceGenerator(std::string name, RigidBody* body);

			/**
			 * @brief remove force by the given force generator by name and the rigid body object.
			 */
			bool DeregisterRigidBodyFromForceGenerator(std::string name, RigidBody* body);

			/**
			 * @brief process xml file to populate the compound objects
			 */
			void InitialiseAllObjects(std::string xmlFile);

		private:
			/**
			** @brief Integrate rigid body by updating all rigid body member variables
			**/
			void Integrate(AABSEngine::Core::GameObject* gObj, Decimal deltaTime);

			/**
			 * @brief default private constructor
			 */
			PhysicsManager();

			/**
			 * @brief calculate the center of gravity for the object and its first moment of inertia
			 */
			void CalculateInertiaAndCOG(AABSEngine::Physics::RigidBody *input, OgreBulletCollisions::StaticMeshToShapeConverter &meshConverter);

			/**
			 * @brief solve for collision detection
			 */
			void CollisionDetection();

			/**
			 * @brief solve for penetration
			 */
			void PenetrationCalculation();

			/**
			 * @brief adjust position and rotation
			 */
			void Integrate(float deltaTime);


			static PhysicsManager* m_singleton;

			OgreBulletCollisions::CollisionsWorld *m_collisionWorld; ///<bullet collision world
			OgreBulletCollisions::DebugDrawer *m_debugDrawer; ///<for debebugging if needed be

			std::vector<AABSEngine::Physics::RigidBody *> m_physicsObjectList; ///< a list of physics objects

			std::map<std::string, AABSEngine::Physics::ForceGenerator*> m_forceGeneratorMap;
			std::map<std::string, AABSEngine::Physics::CompoundObject*> m_predefinedObjects; ///< list of predefined compound objects
			ForceRegistry* m_forceRegistry;
            
			ManifoldBag m_collisionFilter;

			struct AveragedContactPair
			{
				Core::Point3 m_contactA;
				Core::Point3 m_contactB; 
				Core::Vector3 m_contactNormal; 
				Core::GameObject *m_objA; 
				Core::GameObject *m_objB;
			};
			std::vector<AveragedContactPair> m_averagedContactPairs; ///< used for the final collision resolution

			Decimal timeAccumulator;

		};

		//collision mask definitions
		const int NORMAL_COLLISION_FILTER = PhysicsManager::CollisionMask::COL_NORMAL | PhysicsManager::CollisionMask::COL_ENVIRONMENT;
		const int ENV_COLLISION_FILTER = PhysicsManager::CollisionMask::COL_NORMAL;
	}
}
