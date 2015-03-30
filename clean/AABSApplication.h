#pragma once
#include "StdAfx.h"
#include <iostream>

#include "Cursor.h"
#include "SceneManager.h"
#include "PrecisionTimer.h"
#include "Object.h"
#include "PhysicsManager.h"
#include "OISInputManager.h"
#include "Quaternion.h"

#include "BaseFactory.h"
#include "StringTokenizer.h"
#include "Ray.h"
#include "Camera.h"
#include "Player.h"

#include "Agent.h"

#include <time.h>

/**
 * @class AABSApplication
 * @brief main application
 * @author AABS
 * @version X
 * @date October 2013
 */
class AABSApplication : public Ogre::WindowEventListener, public Ogre::FrameListener
{
public:
	/**
	 * @brief default constructor
	 */
	AABSApplication();

	/**
	 * @brief default destructor
	 */
	virtual ~AABSApplication();

	/**
	 * @brief the start of the application
	 * @return bool
	 */
	virtual bool go();

	/** 
	  * @brief Returns a pointer to the scene manager. TODO fix with better design.   
	  * @return SceneManager*
	  */
	AABSEngine::Core::SceneManager* GetSceneManager() { return m_sceneManager; }

	/**
	 * @brief Returns a pointer to the scene manager. TODO fix with better design.
	 * @return PhysicsManager*
	 */
	AABSEngine::Physics::PhysicsManager* GetPhysicsManager() { return m_physicsManager; }

private:
	Ogre::Root* mRoot; ///< the ogre root pointer
	Ogre::String mPluginsCfg; ///< plugins config file
	Ogre::String mResourcesCfg; ///< resources config file
	Ogre::RenderWindow* mWindow; ///< rendering system (openGL or DirectX)

	AABSEngine::Input::InputManager *m_inputManager; ///< input manager
	AABSEngine::Core::SceneManager *m_sceneManager; ///< scene manager
	AABSEngine::Physics::PhysicsManager *m_physicsManager; ///< physics manager
	Ogre::Real deltaTime;

	Player *m_player;

	AABSEngine::Rendering::MouseCursor* m_mouseCursor;
	AABSEngine::Rendering::Camera* m_aabsCamera;


	/**
     * @brief Initialises AI systems (creates and initializes managers) 
	 * @return bool
	 */
    bool AISetup();

	/**
	 * @brief setup the scene manager
	 * @return bool
	 */
	bool SceneManagerSetup();

	/**
	 * @brief setup the physics manager
	 * @return void
	 */
	void PhysicsManagerSetup();

	/**
	 * @brief input manager setup
	 * @return void
	 */
	void InputManagerSetup();
	
	/**
	 ** @brief Setup cursor graphic
	 * @return void
	 **/
	void CursorGraphicSetup();

	/**
	 * @brief set up the models and objects
	 * @return void
	 */
	void ModelsSetup();

	/**
	 * @brief Deserializes the GameObject portion of an object
	 * @param gObj (AABSEngine::Core::GameObject*)
	 * @param obj (pugi::xml_node)
	 * @param mask (Ogre::uint32)
	 * @return bool
	 */
    bool DeserializeGameObject(AABSEngine::Core::GameObject* gObj, pugi::xml_node obj, Ogre::uint32 mask = 1);
	/**
	 * @brief Deserializes the InteractiveObject portion of an object
	 * @param iObj (AABSEngine::Core::InteractiveObject*)
	 * @param obj (pugi::xml_node)
	 * @return bool
	 */
	bool DeserializeInteractiveObject(AABSEngine::Core::InteractiveObject* iObj, pugi::xml_node obj);
	/**
	 * @brief Deserializes the Agent portion of an object
	 * @param aObj (AABSEngine::AI::Agent*)
	 * @param obj (pugi::xml_node)
	 * @return bool
	 */
	bool DeserializeAgent(AABSEngine::AI::Agent* aObj, pugi::xml_node obj);

	/**
	 * @brief load scene mesh file
	 * @return void
	 */
	void LoadSceneMesh();

	/** 
	 * @brief set up aabs camera 
	 * @return void
	 */
	void CameraSetup();

	/**
	 * @brief handle input camera movement (temporary)
	 * @return void
	 */
	void ShootProjectile();


	/**
	 * @return void
	 */
	void ExitProcedure();
	/**
	 * @return void
	 */
	void ToggleWireframe();

	bool showPhoto;
	bool exitNow;

	/**
	 * @brief setup player object
	 * @return void
	 */
	void PlayerSetup();


	/**
	 * @brief update npc agent information window
	 */
	void UpdateInfoText();

protected:
	virtual bool frameStarted(const Ogre::FrameEvent& ev);
	virtual void windowResized(Ogre::RenderWindow *win);
	virtual void windowClosed(Ogre::RenderWindow *win);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent &evt);
};