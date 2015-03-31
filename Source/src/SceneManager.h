#pragma once
#ifndef AABSceneManager_h
#define AABSceneManager_h

#include <vector>
#include <string>
#include "OgreVector3.h"
#include "OgreQuaternion.h"
#include "OgreSceneManager.h"
#include "OgreString.h"
#include "OgreLight.h"

#include "Object.h"

#include "Camera.h"

namespace Ogre
{
	class Node;
	class Entity;
	class ColourValue;
}


 namespace AABSEngine
 {
	 namespace Core
	 {
		/**
		 * @class SceneManager
		 *
		 * @brief Manages scene
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		 class SceneManager
		 {
		 public:

			 ~SceneManager();
		 
			 SceneManager(Ogre::SceneManager *sm);

			 /**
			 ** @brief Reset ogre scene, remove all scene nodes etc
			 **/
			 void ResetScene();

			 /**
			 ** @brief Check if a scene node exists( used to prevent crashes when adding new scene nodes with same name)
			 ** @param name of node
			 ** @return true if exists, else false
			 **/
			 bool SceneNodeExists(Ogre::String nodeName)const;

			 /**
			 ** @brief Attach a scene node to a parent
			 ** @param parent name
			 ** @param pointer to a child node
			 ** @return true if found parent and attached child, else false
			 **/
			 bool AttachSceneNode(Ogre::String parentName, Ogre::SceneNode* childNode);

			 /**
			 ** @brief Remove and delete all children belonging to this parent
			 ** @param parent node name
			 ** @return true if found and destroyed child nodes, else false
			 **/
			 bool UprootSceneChildren(Ogre::String parentName);

			 /**
			 ** @brief Safetly remove a scene node located anywhere(excluding the root for safety reasons) within the scene graph
			 ** @param name of parent node
			 ** @param name of child node supposedly belonging to the parent
			 ** @return true if success finding and deleting the child, else false
			 **/
			 bool UprootSceneChild(Ogre::String parentName, Ogre::String childName); 

			 /**
			 * @brief Create a new scene node and attempt to attach it to a parent node
			 * @param entMeshFilename is the filepath of the mesh
			 * @param parentNode is the name of the parent node to attach this child node to 
			 * @param pos is the world coordinate in which rendering occurs for this node		
			 * @param rot is the orientation in which rendering occurs for this node, possibly taking into account relative transformations if attached to a parent node
			 * @param scale is the scale in whih rendering occurs for this node
			 * @return a pointer to the newly scene node with its respective entity attached to it
			 **/
			 Ogre::SceneNode* CreateSceneNode(Ogre::String entMeshFilename, Ogre::SceneNode* parentNode = 0, Ogre::uint32 mask = 1,  
				 const Ogre::Vector3 &pos = Ogre::Vector3::ZERO, const Ogre::Quaternion& orient = Ogre::Quaternion::IDENTITY, 
				 const Ogre::Vector3& scale = Ogre::Vector3(1,1,1)); 

			 /*
			 * @brief Attempt to retrieve a scene node
			 * @param target is the name of the scene node to be retrieved
			 * @return NULL if not found, else the scene node
			 */
			 Ogre::SceneNode* GetSceneNode(Ogre::String nodeName);
		 
			 /**
			 * @brief Attempt to retrieve a constant pointer to a scene node
			 * @param target is the name of the scene node to be retrieved
			 * @return NULL if not found, else the scene node
			 **/
			 const Ogre::SceneNode* GetSceneNode(Ogre::String nodeName)const;

			 /**
			 * @brief Retrieve the root node
			 * @return root node of the scene
			 **/
			 Ogre::SceneNode* GetRootSceneNode();

			 /**
			 * @brief Retrieve constant pointer to the root node
			 * @return root node of the scene
			 **/
			 const Ogre::SceneNode* GetRootSceneNode()const;

			 /**
			 * @brief Destroy a camera with specified name
			 * @param name of camera to search for when removing it
			 **/
			 void DestroyCamera(Ogre::String name);

			 /**
			 * @brief Setup 3d camera with specified parameters. Every call creates a camera and places it within the records of other cameras
			 * @param name is the name to be assigned to the camera
			 * @param lookat is the directional look at for the camera
			 * @param pos is the world position
			 * @param orient is the rotation of the camera
			 * @param nearDist is the near clipping distance
			 * @param farDist is the far clipping distance
			 * @param aspRatio is the aspect ratio which is usually (screen width / screen height)
			 * @param fovY is the field of view in degrees
			 * @return newly constructed camera object
			 **/
			 //void CreateCamera(Ogre::String name, const Ogre::Vector3& lookat, const Ogre::Vector3& pos, const Ogre::Quaternion& orient,
			 //	 Ogre::Real nearDist,  Ogre::Real farDist,  /*Ogre::Real aspRatio,*/  Ogre::Real fovYDegree);
			 AABSEngine::Rendering::Camera* CreateCamera(Ogre::String name, const Ogre::Vector3& lookat, const Ogre::Vector3& pos, const Ogre::Quaternion& orient,
				 Ogre::Real nearDist,  Ogre::Real farDist,  /*Ogre::Real aspRatio,*/  Ogre::Real fovYDegree);

			 /**
			 * @brief retrieve a camera from current records containing all recently created cameras
			 * @param name of camera
			 * @return camera object if found, else NULL
			 **/
			 Ogre::Camera* GetCamera(Ogre::String cameraName);

			 /**
			 ** @brief retrieve constant pointer to a camera object if it exists
			 ** @param camera name
			 ** @return camera object if found, else NULL
			 **/
			 const Ogre::Camera* GetCamera(Ogre::String cameraName)const;
		
			 /**
			 * @brief Setup a basic light source
			 * @param light name
			 * @param light type found in Ogre::Light::LightTypes
			 * @param direction of light
			 * @param position of light
			 * @param specular color of light
			 * @param diffuse color of light
			 * @return newly constructed light object
			 **/
			 void CreateLight(Ogre::String lightName, Ogre::Light::LightTypes type, const Ogre::ColourValue &specular, const Ogre::ColourValue &diffuse);


			 /**
			 * @brief retrieve a light object from list of recently created lights
			 * @param name of light object
			 * @return light object if found, else NULL
			 **/
			 Ogre::Light* GetLight(Ogre::String lightName);


			/**
			 ** @brief retrieve constant pointer to a light object if it exists
			 ** @param light name
			 ** @return camera object if found, else NULL
			 **/
			 const Ogre::Light* GetLight(Ogre::String lightName)const;

			 /**
			 ** @brief Destroy a light object of the given name
			 ** @param light name
			 **/
			 void DestroyLight(Ogre::String lightName);

			 /**
			 ** @brief Set ambient light of the scene
			 ** @param colour values 
			 **/
			 void SetAmbientLight(const Ogre::ColourValue& colour); 

			 /**
			  * @brief Create ogre entity based on a given mesh file
			  */
			 Ogre::Entity* CreateOgreEntity(const Ogre::String &filename);

			 /**
			  * @brief get the ogre scene manager
			  */
			 Ogre::SceneManager *GetOgreSceneManager();\

			 //## TO BE DONE PROPERLY
			 /**
			  * @brief function to spawn group photo
			  */
			 void GroupPhoto(std::string nodeName);

		 private:
			 Ogre::SceneManager *m_ogreSceneMgr;
		 };
	}
 }

#endif