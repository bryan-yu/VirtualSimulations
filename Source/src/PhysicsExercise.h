#pragma once
#include "StdAfx.h"
#include <iostream>

#include "SceneManager.h"
#include "Object.h"
#include "PhysicsManager.h"
#include "OISInputManager.h"
#include "Quaternion.h"
#include "BaseFactory.h"
#include "StringTokenizer.h"
#include "Camera.h"
#include "Player.h"

/**
 * @class PhysicsExercise
 *
 * @brief main application
 * 
 * @author AABS
 * @version X
 * @date 2013
 *
 */
class PhysicsExercise : public Ogre::WindowEventListener, public Ogre::FrameListener
{
public:
	/**
	 * @brief default constructor
	 */
	PhysicsExercise();

	/**
	 * @brief default destructor
	 */
	virtual ~PhysicsExercise();

	/**
	 * @brief the start of the application
	 */
	virtual bool go();
private:
	Ogre::Root* mRoot; ///< the ogre root pointer
	Ogre::String mPluginsCfg; ///< plugins config file
	Ogre::String mResourcesCfg; ///< resources config file
	Ogre::RenderWindow* mWindow; ///< rendering system (openGL or DirectX)

	AABSEngine::Input::InputManager *m_inputManager; ///< input manager
	AABSEngine::Core::SceneManager *m_sceneManager; ///< scene manager
	AABSEngine::Physics::PhysicsManager *m_physicsManager; ///< physics manager
	Ogre::Real deltaTime;
	Ogre::Camera *m_camera;
	AABSEngine::Core::GameObject* m_wall;
	AABSEngine::Rendering::Camera* aabscamera;
	Player *m_player;

	/**
	 * @brief setup the scene manager
	 */
	bool SceneManagerSetup();

	/**
	 * @brief setup the physics manager
	 */
	void PhysicsManagerSetup();

	/**
	 * @brief input manager setup
	 */
	void InputManagerSetup();

	/**
	 * @brief set up the models and objects
	 */
	void ModelsSetup();

	/** 
	 * @brief set up aabs camera 
	 */
	void CameraSetup();

	/**
	 * @brief handle input camera movement (temporary)
	 */
	void ShootProjectile();

	void LeftClick(int x, int y);

	void ExitProcedure();
	void ToggleWireframe();

	bool showPhoto;
	bool exitNow;

	std::string photoName;

	/**
	 * @brief setup player object
	 */
	void PlayerSetup();

protected:
	virtual void windowResized(Ogre::RenderWindow *win);
	virtual void windowClosed(Ogre::RenderWindow *win);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent &evt);
};