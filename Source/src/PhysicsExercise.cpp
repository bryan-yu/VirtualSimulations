#include "StdAfx.h"
#include "PhysicsExercise.h"
#include "Matrix3.h"
#include "OgreBulletCollisionsBoxShape.h"
#include "OgreBulletCollisionsCompoundShape.h"

/* TODO do somewhere else??? */
#include "GravityForceGenerator.h"

//##TO BE REMOVED
const float projectileSpeed = 7.0f;

PhysicsExercise::PhysicsExercise() : mRoot(0), mPluginsCfg(Ogre::StringUtil::BLANK), mResourcesCfg(Ogre::StringUtil::BLANK)
{
	exitNow = false;
	showPhoto = false;
}

PhysicsExercise::~PhysicsExercise()
{
	//remove this application as window listener
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);

	delete mRoot; //remove Ogre root
}

void PhysicsExercise::InputManagerSetup()
{
	//setup input
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;
	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	m_inputManager = new AABSEngine::Input::AABSOISInputManager(windowHndStr.str());
  
	using namespace AABSEngine::Rendering;

	m_inputManager->Register(new AABSEngine::Input::KeyboardEvent(AABSEngine::Input::G, AABSEngine::Input::KEY_DOWN, AABSEngine::Input::ON_PRESS), boost::bind(&PhysicsExercise::ShootProjectile, this));
	m_inputManager->Register(new AABSEngine::Input::KeyboardEvent(AABSEngine::Input::W, AABSEngine::Input::KEY_DOWN, AABSEngine::Input::ON_HOLD), boost::bind(&Player::MoveForward, m_player));
	m_inputManager->Register(new AABSEngine::Input::KeyboardEvent(AABSEngine::Input::A, AABSEngine::Input::KEY_DOWN, AABSEngine::Input::ON_HOLD), boost::bind(&Player::StrafeLeft, m_player));
	m_inputManager->Register(new AABSEngine::Input::KeyboardEvent(AABSEngine::Input::S, AABSEngine::Input::KEY_DOWN, AABSEngine::Input::ON_HOLD), boost::bind(&Player::MoveBackward, m_player));
	m_inputManager->Register(new AABSEngine::Input::KeyboardEvent(AABSEngine::Input::D, AABSEngine::Input::KEY_DOWN, AABSEngine::Input::ON_HOLD), boost::bind(&Player::StrafeRight, m_player));
	m_inputManager->Register(new AABSEngine::Input::KeyboardEvent(AABSEngine::Input::Z, AABSEngine::Input::KEY_DOWN, AABSEngine::Input::ON_HOLD), boost::bind(&Camera::MoveUp, aabscamera));
	m_inputManager->Register(new AABSEngine::Input::KeyboardEvent(AABSEngine::Input::X, AABSEngine::Input::KEY_DOWN, AABSEngine::Input::ON_HOLD), boost::bind(&Camera::MoveDown, aabscamera));
	m_inputManager->Register(new AABSEngine::Input::KeyboardEvent(AABSEngine::Input::K, AABSEngine::Input::KEY_DOWN, AABSEngine::Input::ON_PRESS), boost::bind(&PhysicsExercise::ToggleWireframe, this));
	m_inputManager->Register(new AABSEngine::Input::KeyboardEvent(AABSEngine::Input::ESC, AABSEngine::Input::KEY_DOWN, AABSEngine::Input::ON_PRESS), boost::bind(&PhysicsExercise::ExitProcedure, this));
	
	m_inputManager->Register(new AABSEngine::Input::MouseButtonEvent(AABSEngine::Input::BUTTON_LEFT, AABSEngine::Input::BUTTON_DOWN, AABSEngine::Input::BUTTON_ON_PRESS), 
		boost::bind(&PhysicsExercise::LeftClick, this, _1, _2));
	m_inputManager->Register(boost::bind(&Camera::Rotate, aabscamera, _1, _2));
	
	m_inputManager->Register(new AABSEngine::Input::KeyboardEvent(AABSEngine::Input::SPACE, AABSEngine::Input::KEY_DOWN, AABSEngine::Input::ON_PRESS), boost::bind(&PhysicsExercise::ShootProjectile, this));

	//m_inputManager->Register(new AABSEngine::Input::KeyboardEvent(AABSEngine::Input::R, AABSEngine::Input::KEY_DOWN, AABSEngine::Input::ON_PRESS), boost::bind(&PhysicsExercise::reset, this));
}

bool PhysicsExercise::SceneManagerSetup()
{
#ifdef _DEBUG
	mResourcesCfg = "resources_d.cfg";
	mPluginsCfg = "plugins_d.cfg";
#else
	mResourcesCfg = "resources.cfg";
	mPluginsCfg = "plugins.cfg";
#endif

	//----construct Ogre root-----//
	mRoot = new Ogre::Root(mPluginsCfg);

	//----setup the resources path from the config file-----//
	Ogre::ConfigFile cf;
	cf.load(mResourcesCfg);

	//go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String secName, typeName, archName;
	while(seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator it;
		for(it = settings->begin(); it != settings->end(); it++)
		{
			typeName = it->first;
			archName = it->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
		}
	}

	//show the config dialog and initialize the system
	if(!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
	{
		return false;
	}
	
	//render window
	mWindow = mRoot->initialise(true, "PhysicsExercise Render Window");
	mWindow->setVSyncEnabled(true);
	mWindow->setVSyncInterval(1);

	// Set default mipmap level (note: some APIs ignore this)
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	// initialise all resource groups
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	//------create the scene manager--------//
	m_sceneManager = new AABSEngine::Core::SceneManager(mRoot->createSceneManager("DefaultSceneManager"));
  
	//-------set ambient light--------//
	m_sceneManager->GetOgreSceneManager()->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	Ogre::Light *light = m_sceneManager->GetOgreSceneManager()->createLight("MainLight");
	light->setPosition(20, 80, 50);

	return true;
}

bool PhysicsExercise::go()
{
	if(!SceneManagerSetup())
	{
		return false;
	}
	
	//setup the physics
	PhysicsManagerSetup();

	//setup the models
	ModelsSetup();

	// set up the camera
	CameraSetup();

	//setup the player
	PlayerSetup();
	
	//setup the input manager
	InputManagerSetup();
	

	OgreBulletCollisions::DebugDrawer *m_debugDrawer = new OgreBulletCollisions::DebugDrawer();
	m_debugDrawer->setDrawWireframe(true);
	m_debugDrawer->setDrawContactPoints(true);

	m_physicsManager->GetCollisionWorld()->setDebugDrawer(m_debugDrawer);
	m_physicsManager->GetCollisionWorld()->setShowDebugShapes(true);

	//set initial mouse clipping size
	windowResized(mWindow);

	//register as a window listener
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	//alternative to the while loop
	mRoot->addFrameListener(this);
	mRoot->startRendering();

	return true;
}

void PhysicsExercise::windowResized(Ogre::RenderWindow* rw)
{
	
}

void PhysicsExercise::windowClosed(Ogre::RenderWindow* rw)
{
	
}

bool PhysicsExercise::frameRenderingQueued(const Ogre::FrameEvent &evt)
{
	//set the delta time
	//deltaTime = timer.getMilliseconds() / 1000.0f;
	deltaTime = evt.timeSinceLastFrame;
	//deltaTime = bTimer.TimeElapsed();

	if(mWindow->isClosed())
	{
		return false;
	}
	if(exitNow)
	{
		return false;
	}

	aabscamera->SetDeltaTime(deltaTime);

	if (m_inputManager)
	{
		m_inputManager->Update();
	}

	if (m_physicsManager)
	{
		m_physicsManager->Update(deltaTime);	
	}

	//readjust the player and camera
	aabscamera->SetPosition(m_player->GetPosition());
	m_player->ResetVelocity();

	return true;
}


void PhysicsExercise::ShootProjectile()
{
	Ogre::Camera *m_camera = m_sceneManager->GetCamera("DefaultCamera");
	AABSEngine::Core::Point3 startPosition(m_camera->getPosition().x, m_camera->getPosition().y, m_camera->getPosition().z);
	AABSEngine::Core::Vector3 dir(m_camera->getDirection().x,m_camera->getDirection().y,m_camera->getDirection().z);
	
	//create a projectile object
	Ogre::SceneNode *projectileWrapper = m_sceneManager->GetOgreSceneManager()->getRootSceneNode()->createChildSceneNode();
	Ogre::SceneNode * projectile = m_sceneManager->CreateSceneNode("CS_StopSign.mesh", projectileWrapper);
	AABSEngine::Core::GameObject *m_projectile = new AABSEngine::Core::GameObject(projectileWrapper);

	m_physicsManager->AddObject(m_projectile, "TableTall", startPosition);
	m_physicsManager->RegisterRigidBodyWithForceGenerator("GravityForceGenerator", m_projectile->GetPhysicsObject());

	//set linear velocity in camera direction
	m_projectile->GetPhysicsObject()->SetLinearVelocity(dir * projectileSpeed);
}

void PhysicsExercise::ExitProcedure()
{
	if(showPhoto)
	{
		exitNow = true;
	}
	
	//show our photos here
	showPhoto = true;
	
	m_sceneManager->GetSceneNode(photoName)->setVisible(true);
}


void PhysicsExercise::ModelsSetup()
{
	//setup the physics collision objects
	m_physicsManager->InitialiseAllObjects("../resources/scripts/PhysicsDefinition.xml");

	pugi::xml_document xDoc;
	if(!xDoc.load_file("../resources/scripts/PhysicsExerciseWorldObjects.xml"))
	{
		return;
	}

	pugi::xml_node objectNodes = xDoc.child("Objects");
	for (pugi::xml_node obj = objectNodes.first_child(); obj; obj = obj.next_sibling())
	{
		//setup the wrapper node
		Ogre::SceneNode *parentNode = m_sceneManager->GetOgreSceneManager()->getRootSceneNode()->createChildSceneNode();

		//get the meshfile name
		std::string meshFile = obj.child_value("MeshFile");
		Ogre::SceneNode *node = m_sceneManager->CreateSceneNode(meshFile, parentNode);
		AABSEngine::Core::GameObject *gObj = new AABSEngine::Core::GameObject(parentNode);

		std::string physicsObjectName = obj.child_value("PhysicsObjectName"); //physics object name

		//position
		std::string str_pos_x = obj.child("Position").attribute("x").value(); float posx = atof(str_pos_x.c_str());
		std::string str_pos_y = obj.child("Position").attribute("y").value(); float posy = atof(str_pos_y.c_str());
		std::string str_pos_z = obj.child("Position").attribute("z").value(); float posz = atof(str_pos_z.c_str());

		//orientation
		std::string str_quat_w = obj.child("Orientation").attribute("w").value(); float quatw = atof(str_quat_w.c_str());
		std::string str_quat_x = obj.child("Orientation").attribute("x").value(); float quatx = atof(str_quat_x.c_str());
		std::string str_quat_y = obj.child("Orientation").attribute("y").value(); float quaty = atof(str_quat_y.c_str());
		std::string str_quat_z = obj.child("Orientation").attribute("z").value(); float quatz = atof(str_quat_z.c_str());

		m_physicsManager->AddObject(gObj, physicsObjectName, AABSEngine::Core::Point3(posx,posy,posz), AABSEngine::Core::Quaternion(quatw,quatx,quaty,quatz)); //setup the physics object

		std::string gravity = obj.child_value("Gravity"); 
		if(gravity == "true")
		{
			m_physicsManager->RegisterRigidBodyWithForceGenerator("GravityForceGenerator", gObj->GetPhysicsObject());
		}

		std::string visible = obj.child_value("Visible"); 
		if(visible == "false")
		{
			parentNode->setVisible(false);
		}
	}

			
	//instantiate the group photo node
	m_sceneManager->GroupPhoto("GroupPhoto");
}

void PhysicsExercise::PhysicsManagerSetup()
{
	//setup physics world
	m_physicsManager = AABSEngine::Physics::PhysicsManager::Instance();
	m_physicsManager->SetupPhysicsWorld(m_sceneManager->GetOgreSceneManager());

	m_physicsManager->AddForceGenerator("GravityForceGenerator", new AABSEngine::Physics::GravityForceGenerator(AABSEngine::Core::Vector3(0,-9.8,0)));
}

void PhysicsExercise::CameraSetup()
{
	aabscamera = m_sceneManager->CreateCamera("DefaultCamera", Ogre::Vector3(0,0, 60), Ogre::Vector3(0,5,10), Ogre::Quaternion::IDENTITY, 0.1, 1000, 60);

	//-------creating viewport-------//
	Ogre::Viewport *vp = mWindow->addViewport(m_sceneManager->GetCamera("DefaultCamera"));
	vp->setBackgroundColour(Ogre::ColourValue(51.0f/255.0f,24.0f/255.0f,183.0f/255.0f));

	//alter the camera aspect ratio to match the viewport
	m_sceneManager->GetCamera("DefaultCamera")->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

void PhysicsExercise::ToggleWireframe()
{
	m_physicsManager->GetCollisionWorld()->setShowDebugShapes(!m_physicsManager->GetCollisionWorld()->getShowDebugShapes());
}

void PhysicsExercise::LeftClick(int x, int y)
{
	if(showPhoto)
	{
		exitNow = true;
	}
}
void PhysicsExercise::PlayerSetup()
{
	m_player = new Player();
	m_physicsManager->AddObject(m_player, "Player", AABSEngine::Core::Point3(0, 5, 10));
	m_physicsManager->RegisterRigidBodyWithForceGenerator("GravityForceGenerator", m_player->GetPhysicsObject());
	m_player->SetCamera(aabscamera);
	m_player->SetMoveSpeed(5.0f);
}