#ifndef AABS_OBJECT_H
#define AABS_OBJECT_H

#include <string>
#include "Ogre.h"
#include "OgreSubMesh.h"
#include "RigidBody.h"

namespace AABSEngine
{
	namespace Core
	{
		/**
		 * @class GameObject
		 *
		 * @brief Game object class
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class GameObject
		{
		public:
			/**
			 * @brief default constructor
			 */
			GameObject();

			/**
			 * @brief default destructor
			 */
			~GameObject();

			/**
			 * @brief parameterized constructor
			 * @param ogre Node object
			 */
			GameObject(Ogre::SceneNode *ogreNode);

			/**
			 * @brief set ogre node
			 * @param Ogre SceneNode pointer
			 */
			void SetSceneNode(Ogre::SceneNode *ogreNode);

			/**
			 * @brief get the ogre node
			 * @retval Ogre SceneNode pointer contained in this object
			 */
			Ogre::SceneNode *GetSceneNode();

			/**
			 * @brief get the id/name of this object
			 */
			std::string GetName();

			/**
			 * @brief set physics object
			 * @param physics object pointer
			 */
			void SetPhysicsObject(AABSEngine::Physics::RigidBody *in_phyObj);

			/**
			 * @brief get the physics object
			 * @retval physics object pointer contained in this object
			 */
			AABSEngine::Physics::RigidBody *GetPhysicsObject();

			/**
			 * @brief Get deleteOnContact status
			 */
			bool DeleteIfCollide() { return m_deleteOnContact; }

			/**
			 * @brief set deleteOnContact status
			 */
			void SetDeleteOnContact(bool input) { m_deleteOnContact = input; }

			/**
			 * @brief set delete object status
			 */
			void MarkForRemoval() { m_deleteObject = true; }

			/**
			 * @brief if the object should be removed or not
			 */
			virtual bool ToBeRemoved() { return m_deleteObject; }

			/**
			** @brief Return unique id of this entity
			**/
			int ID()const { return m_objectID; }

		    /**
		     * @brief Sets the string type of the object.
		     */
		    void SetType(const std::string type);

		    /** 
		     * @brief Gets the string type of the object.
		     */
		    std::string GetType() const;

			/**
		     * @brief Sets the string type of the object.
		     */
		    void SetCoreType(const std::string cType);

			/** 
		     * @brief Gets the string type of the object.
		     */
		    std::string GetCoreType() const;


		private:
			Ogre::SceneNode *m_sceneNode; ///< ogre node

			AABSEngine::Physics::RigidBody *m_physObject; ///< physics object

			bool m_deleteOnContact; ///< temporary variable to delete this object when colliding with other object
			bool m_deleteObject; ///< marker to delete this object

			/**
			 * @brief assign id to this object
			 */
			void AssignID();

			std::string m_type;
			std::string m_coreType;
			std::string m_name;
			int m_objectID;
			static int m_id;
		};
	}
}

#endif