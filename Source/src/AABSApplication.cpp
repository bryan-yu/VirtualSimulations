#include "StdAfx.h"
#include "AABSApplication.h"
#include "Matrix3.h"
#include "GravityForceGenerator.h"



//#include "AABSNPC.h"
//#include "Emotions.h"
#include "Singleton.h"
#include "GameObjectManager.h"
#include "InteractiveObject.h"
#include "AffordanceManager.h"
#include "NeedManager.h"
#include "ActionManager.h"
#include "Personality.h"
#include "Trait.h"

#include "TextRenderer.h"

#include "DrinkAction.h"
#include "SocialiseAction.h"
#include "PickAction.h"
#include "ProvokeAction.h"
#include "Constants.h"

#include "ActionBlackboard.h" // TODO remove

//##TO BE REMOVED
const float projectileSpeed = 5.0f;
std::string photoName = "GroupPhoto";

AABSApplication::AABSApplication() : mRoot(0), mPluginsCfg(Ogre::StringUtil::BLANK), mResourcesCfg(Ogre::StringUtil::BLANK)
{
	exitNow = false;
	showPhoto = false;
}

AABSApplication::~AABSApplication()
{
	//remove this application as window listener
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);

	delete m_mouseCursor;
	delete mRoot; //remove Ogre root
}

void AABSApplication::InputManagerSetup()
{
	//setup input
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;
	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	m_inputManager = new AABSEngine::Input::AABSOISInputManager(windowHndStr.str());
  
	using namespace AABSEngine::Rendering;

	////////////ACTIONS/////////////////
	m_player->SetInputManager(m_inputManager);

	AABSEngine::Core::DrinkAction* act1 = m_player->AddAction<AABSEngine::Core::DrinkAction>();
	AABSEngine::Core::ProvokeAction* act2 = m_player->AddAction<AABSEngine::Core::ProvokeAction>();
	AABSEngine::Core::SocialiseAction* act3 = m_player->AddAction<AABSEngine::Core::SocialiseAction>();
	AABSEngine::Core::PickAction* act4 = m_player->AddAction<AABSEngine::Core::PickAction>();
	
	act1->SetInternals(m_mouseCursor);
	act2->SetInternals(m_mouseCursor);
	act3->SetInternals(m_mouseCursor);
	act4->SetInternals(m_physicsManager);

	m_inputManager->Register(new AABSEngine::Input::KeyboardEvent(AABSEngine::Input::KEY_1, AABSEngine::Input::KEY_DOWN, AABSEngine::Input::ON_PRESS), boost::bind(&AABSEngine::Core::DrinkAction::Begin, act1));
	m_inputManager->Register(new AABSEngine::Input::KeyboardEvent(AABSEngine::Input::KEY_2, AABSEngine::Input::KEY_DOWN, AABSEngine::Input::ON_PRESS), boost::bind(&AABSEngine::Core::ProvokeAction::Begin, act2));
	m_inputManager->Register(new AABSEngine::Input::MouseButtonEvent(AABSEngine::Input::BUTTON_LEFT, AABSEngine::Input::BUTTON_DOWN, AABSEngine::Input::BUTTON_ON_PRESS), 
		boost::bind(&AABSEngine::Core::PickAction::Begin, act4));
	

	m_inputManager->Register(new AABSEngine::Input::KeyboardEvent(AABSEngine::Input::G, AABSEngine::Input::KEY_DOWN, AABSEngine::Input::ON_PRESS), boost::bind(&AABSApplication::ShootProjectile, this));
	m_inputManager->Register(new AABSEngine::Input::KeyboardEvent(AABSEngine::Input::W, AABSEngine::Input::KEY_DOWN, AABSEngine::Input::ON_HOLD), boost::bind(&Player::MoveForward, m_player));
	m_inputManager->Register(new AABSEngine::Input::KeyboardEvent(AABSEngine::Input::A, AABSEngine::Input::KEY_DOWN, AABSEngine::Input::ON_HOLD), boost::bind(&Player::StrafeLeft, m_player));
	m_inputManager->Register(new AABSEngine::Input::KeyboardEvent(AABSEngine::Input::S, AABSEngine::Input::KEY_DOWN, AABSEngine::Input::ON_HOLD), boost::bind(&Player::MoveBackward, m_player));
	m_inputManager->Register(new AABSEngine::Input::KeyboardEvent(AABSEngine::Input::D, AABSEngine::Input::KEY_DOWN, AABSEngine::Input::ON_HOLD), boost::bind(&Player::StrafeRight, m_player));
	m_inputManager->Register(new AABSEngine::Input::KeyboardEvent(AABSEngine::Input::Q, AABSEngine::Input::KEY_DOWN, AABSEngine::Input::ON_HOLD), boost::bind(&Camera::RotateLeft, m_aabsCamera));
	m_inputManager->Register(new AABSEngine::Input::KeyboardEvent(AABSEngine::Input::E, AABSEngine::Input::KEY_DOWN, AABSEngine::Input::ON_HOLD), boost::bind(&Camera::RotateRight, m_aabsCamera));
	m_inputManager->Register(new AABSEngine::Input::KeyboardEvent(AABSEngine::Input::K, AABSEngine::Input::KEY_DOWN, AABSEngine::Input::ON_PRESS), boost::bind(&AABSApplication::ToggleWireframe, this));
	m_inputManager->Register(new AABSEngine::Input::KeyboardEvent(AABSEngine::Input::ESC, AABSEngine::Input::KEY_DOWN, AABSEngine::Input::ON_PRESS), boost::bind(&AABSApplication::ExitProcedure, this));
	

	m_inputManager->Register(boost::bind(&Camera::Rotate, m_aabsCamera, _1, _2));

	m_inputManager->Register(new AABSEngine::Input::KeyboardEvent(AABSEngine::Input::SPACE, AABSEngine::Input::KEY_DOWN, AABSEngine::Input::ON_PRESS), boost::bind(&AABSApplication::ShootProjectile, this));
}

bool AABSApplication::AISetup()
{
  bool success = true;
  success = success && AABSEngine::Core::Singleton<AABSEngine::AI::NeedManager>::Instance()->Initialise();
  success = success && AABSEngine::Core::Singleton<AABSEngine::AI::ActionManager>::Instance()->Initialise();
  success = success && AABSEngine::Core::Singleton<AABSEngine::AI::TraitManager>::Instance()->Initialise();
  return true;
}

bool AABSApplication::SceneManagerSetup()
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
	mWindow = mRoot->initialise(true, "AABSApplication Render Window");
	mWindow->setVSyncEnabled(true);
	mWindow->setVSyncInterval(1);

	// Set default mipmap level (note: some APIs ignore this)
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	// initialise all resource groups
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	//------create the scene manager--------//
	m_sceneManager = new AABSEngine::Core::SceneManager(mRoot->createSceneManager("DefaultSceneManager"));

	//-------set atmospherics--------//
	m_sceneManager->GetOgreSceneManager()->setFog(Ogre::FOG_LINEAR, Ogre::ColourValue(51.0f/255.0f,24.0f/255.0f,183.0f/255.0f), 0.0, 1.0, 100.0);

	//-------set ambient light--------//
	m_sceneManager->GetOgreSceneManager()->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	Ogre::Light *light = m_sceneManager->GetOgreSceneManager()->createLight("MainLight");
    light->setType(Ogre::Light::LT_DIRECTIONAL);
//	light->setCastShadows(true);
	light->setCastShadows(false);
	light->setDirection(Ogre::Vector3( 1, -1, 2 ));
    light->setDiffuseColour(Ogre::ColourValue(1.0, 1.0, 1.0));
    light->setSpecularColour(Ogre::ColourValue(1.0, 1.0, 1.0));
	//------set shadow type------//
	m_sceneManager->GetOgreSceneManager()->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);//CPU intensive
	//m_sceneManager->GetOgreSceneManager()->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);//CPU intensive
	//m_sceneManager->GetOgreSceneManager()->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_ADDITIVE);//GPU 'intensive'
	//m_sceneManager->GetOgreSceneManager()->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_MODULATIVE);//GPU 'intensive'
	m_sceneManager->GetOgreSceneManager()->setShadowTextureSelfShadow(true);//for texture based shadowtype...
  
	return true;
}

bool AABSApplication::frameStarted(const Ogre::FrameEvent& ev)
{
	if(Ogre::FrameListener::frameStarted(ev) == false) return false;

	m_mouseCursor->AlignCenter();

	return true;
}

bool AABSApplication::go()
{
	if(!SceneManagerSetup())
	{
		return false;
	}

	AISetup();

	//setup the physics
	PhysicsManagerSetup();

	//setup the models
	ModelsSetup();

	//setup cursor
	CursorGraphicSetup();

	// set up the camera
	CameraSetup();

	//setup the player
	PlayerSetup();
	
	//setup the input manager
	InputManagerSetup();

	//create textrenderer singleton object
	new TextRenderer();
	TextRenderer::getSingleton().addTextBox("txtStatus", "", 10, 10, 1000, 1000, Ogre::ColourValue::Green);

	OgreBulletCollisions::DebugDrawer *m_debugDrawer = new OgreBulletCollisions::DebugDrawer();
	m_debugDrawer->setDrawWireframe(true);
	m_debugDrawer->setDrawContactPoints(true);

	m_physicsManager->GetCollisionWorld()->setDebugDrawer(m_debugDrawer);
	m_physicsManager->GetCollisionWorld()->setShowDebugShapes(false);//debug lines

	//set initial mouse clipping size
	windowResized(mWindow);

	//register as a window listener
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	//alternative to the while loop
	mRoot->addFrameListener(this);
	mRoot->startRendering();

	return true;
}

void AABSApplication::windowResized(Ogre::RenderWindow* rw)
{
	////ADDED///////
	m_mouseCursor->SetWindowDimensions(rw->getWidth(), rw->getHeight());

}

void AABSApplication::windowClosed(Ogre::RenderWindow* rw)
{
	
}

bool AABSApplication::frameRenderingQueued(const Ogre::FrameEvent &evt)
{
	//set the delta time
	deltaTime = evt.timeSinceLastFrame;

	if(mWindow->isClosed())
	{
		return false;
	}
	if(exitNow)
	{
		return false;
	}

	//OUR UPDATE LOOP
    m_aabsCamera->SetDeltaTime(deltaTime);

    if (m_inputManager)
	   m_inputManager->Update();
	
	m_player->Update(); //update player after input

    if (m_physicsManager)
	   m_physicsManager->Update(deltaTime);

	AABSEngine::AI::ActionBlackboard *bb = AABSEngine::Core::Singleton<AABSEngine::AI::ActionBlackboard>::Instance();
	AABSEngine::Core::Singleton<AABSEngine::Core::GameObjectManager>::Instance()->Update(deltaTime);

	//readjust the player and camera
    m_aabsCamera->SetPosition(AABSEngine::Core::Point3(m_player->GetPosition().X(), m_player->GetPosition().Y() + 1.0f, m_player->GetPosition().Z()));
	m_player->ResetVelocity();

	//myTextBox->setText("txtStatus", "YO");
	UpdateInfoText();

	return true;
}

void AABSApplication::ShootProjectile()
{
 	Ogre::Camera *m_camera = m_sceneManager->GetCamera("DefaultCamera");
	AABSEngine::Core::Point3 startPosition(m_camera->getPosition().x, m_camera->getPosition().y, m_camera->getPosition().z);
	AABSEngine::Core::Vector3 dir(m_camera->getDirection().x,m_camera->getDirection().y,m_camera->getDirection().z);
	AABSEngine::AI::Affordance *aff = AffordanceManager::Instance()->CreateAffordance("Pick", 100);

	AABSEngine::Core::GameObjectDefinition *gObjDef = new AABSEngine::Core::GameObjectDefinition("Jug01.mesh", "Jug", startPosition+dir, AABSEngine::Core::Quaternion::IDENTITY, true, true, "TAVERN_INTERACTABLE");
	AABSEngine::Core::InteractiveObjectDefinition *objDef = new AABSEngine::Core::InteractiveObjectDefinition((*gObjDef), (*aff));

	AABSEngine::Core::GameObject *m_projectile = AABSEngine::Core::Singleton<AABSEngine::Core::GameObjectManager>::Instance()->CreateInteractiveObject(*objDef);
	m_projectile->GetPhysicsObject()->SetLinearVelocity(dir * projectileSpeed);

	AABSEngine::Core::Singleton<AABSEngine::Core::GameObjectManager>::Instance()->AddObject(m_projectile, "InteractiveObject");

	delete gObjDef;
	delete objDef;
	delete aff;
}

void AABSApplication::ExitProcedure()
{
	if(showPhoto)
	{
		exitNow = true;
	}
	
	//show our photos here
	showPhoto = true;
	m_mouseCursor->SetVisible(false);
	m_sceneManager->GetSceneNode(photoName)->setVisible(true);	
}

void AABSApplication::CursorGraphicSetup()
{
	//////ADDED///////////////////////////
	m_mouseCursor = new AABSEngine::Rendering::MouseCursor();
	m_mouseCursor->SetTexture("Cursor.png");
	m_mouseCursor->SetVisible(true);
	m_mouseCursor->SetWindowDimensions(mWindow->getWidth(), mWindow->getHeight());
}

void AABSApplication::ModelsSetup()
{
	AABSEngine::Utility::Factory<AABSEngine::Core::GameObject> gameObjectFactory;
	gameObjectFactory.Register<AABSEngine::Core::GameObject>("AABSFactory");

	//load the scene
	LoadSceneMesh();

	pugi::xml_document xDoc;
	pugi::xml_parse_result result;
	if (!xDoc.load_file("../resources/scripts/ProjectObjects.xml"))
	{
		result = xDoc.load_file("../resources/scripts/ProjectObjects.xml");
		std::cout << result.description() << " " << result.offset << std::endl;
		return;
	}

	/* TODO move serialization to ISerializable */
	pugi::xml_node objectNodes = xDoc.child("Objects");
	for (pugi::xml_node obj = objectNodes.first_child(); obj; obj = obj.next_sibling())
	{
		AABSEngine::Core::GameObject *gObj = AABSEngine::Core::Singleton<AABSEngine::Core::GameObjectManager>::Instance()->Create("GameObject");
		if (DeserializeGameObject(gObj, obj))
			AABSEngine::Core::Singleton<AABSEngine::Core::GameObjectManager>::Instance()->AddObject(gObj, "GameObject");
		else
			delete gObj;
      
	}

    objectNodes = xDoc.child("InteractiveObjects");
	for (pugi::xml_node obj = objectNodes.first_child(); obj; obj = obj.next_sibling())
	{
		AABSEngine::Core::InteractiveObject *iObj = (AABSEngine::Core::InteractiveObject*)AABSEngine::Core::Singleton<AABSEngine::Core::GameObjectManager>::Instance()->Create("InteractiveObject");
		if (DeserializeInteractiveObject(iObj, obj))
			AABSEngine::Core::Singleton<AABSEngine::Core::GameObjectManager>::Instance()->AddObject(iObj, "InteractiveObject");
		else
			delete iObj;
	}

	objectNodes = xDoc.child("Agents");
	for (pugi::xml_node obj = objectNodes.first_child(); obj; obj = obj.next_sibling())
	{
		AABSEngine::AI::Agent *aObj = (AABSEngine::AI::Agent*)AABSEngine::Core::Singleton<AABSEngine::Core::GameObjectManager>::Instance()->Create("Agent");
		if (DeserializeAgent(aObj, obj))
		{
			AABSEngine::Core::Singleton<AABSEngine::Core::GameObjectManager>::Instance()->AddObject(aObj, "Agent");
			aObj->InitialiseAgent();
		}
		else
			delete aObj;
	}
	//instantiate the group photo node
	m_sceneManager->GroupPhoto("GroupPhoto");
}

void AABSApplication::PhysicsManagerSetup()
{
	//setup physics world
	m_physicsManager = AABSEngine::Physics::PhysicsManager::Instance();
	m_physicsManager->SetupPhysicsWorld(m_sceneManager->GetOgreSceneManager());

	//setup the physics collision objects
	m_physicsManager->InitialiseAllObjects("../resources/scripts/PhysicsDefinition.xml");

	//add gravity force generator which is (0, -9.8, 0)
	m_physicsManager->AddForceGenerator("GravityForceGenerator", new AABSEngine::Physics::GravityForceGenerator(AABSEngine::Core::Vector3(0,-9.8,0)));//gravity
}

void AABSApplication::CameraSetup()
{
	m_aabsCamera = m_sceneManager->CreateCamera("DefaultCamera", Ogre::Vector3(0,0, 1), Ogre::Vector3(0,0,0), Ogre::Quaternion::IDENTITY, 0.1, 1000, 60);

	//-------creating viewport-------//
	Ogre::Viewport *vp = mWindow->addViewport(m_sceneManager->GetCamera("DefaultCamera"));
	vp->setBackgroundColour(Ogre::ColourValue(51.0f/255.0f,24.0f/255.0f,183.0f/255.0f));

	//alter the camera aspect ratio to match the viewport
	m_sceneManager->GetCamera("DefaultCamera")->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

void AABSApplication::ToggleWireframe()
{
	m_physicsManager->GetCollisionWorld()->setShowDebugShapes(!m_physicsManager->GetCollisionWorld()->getShowDebugShapes());
}

void AABSApplication::LoadSceneMesh()
{
	std::ifstream inputFile;
	inputFile.open("../resources/scripts/scene_model.txt");
	if(!inputFile)
	{
		return;
	}

	//get line by line
    std::string line = "";
    while(std::getline(inputFile, line))
    {
        if(line != "")
        {
			//setup the wrapper node
			Ogre::SceneNode *parentNode = m_sceneManager->GetOgreSceneManager()->getRootSceneNode()->createChildSceneNode();

			//get the meshfile name from scene_model.txt
			std::string meshFile = line;
			Ogre::SceneNode *node = m_sceneManager->CreateSceneNode(meshFile, parentNode, QueryMasks::TAVERN_NONE);
			Ogre::Entity *ent = (Ogre::Entity *)node->getAttachedObject(0); //get the entity;

			//add game object to the scene manager
			AABSEngine::Core::GameObject *gObj = AABSEngine::Core::Singleton<AABSEngine::Core::GameObjectManager>::Instance()->Create("GameObject");
			gObj->SetSceneNode(parentNode);

			//add this object to the physics manager
			m_physicsManager->AddSceneObject(gObj, ent);
			
			break; //go out of the loop straight away
        }
    }

	inputFile.close();
}

void AABSApplication::PlayerSetup()
{
	m_player = new Player();
	m_physicsManager->AddObject(m_player, "Player", AABSEngine::Core::Point3(7, 0.6, -30));
	m_player->GetVisualRay()->ConstructSceneQuery(m_sceneManager);
	m_player->SetCamera(m_aabsCamera);
	m_player->SetMoveSpeed(8.0f);
}

bool AABSApplication::DeserializeGameObject(AABSEngine::Core::GameObject* gObj, pugi::xml_node obj, Ogre::uint32 mask) /* TODO Iserialisable */
{
	//setup the wrapper node
	Ogre::SceneNode *parentNode = m_sceneManager->GetOgreSceneManager()->getRootSceneNode()->createChildSceneNode();

	//get the meshfile name
	std::string meshFile = obj.child_value("MeshFile");
	Ogre::SceneNode *node = m_sceneManager->CreateSceneNode(meshFile, parentNode, mask);

	gObj->SetSceneNode(parentNode);
	gObj->SetCoreType("Object");

	std::string physicsObjectName = obj.child_value("PhysicsObjectName"); //physics object name

	//position
	std::string str_pos_x = obj.child("Position").attribute("x").value(); float posx = atof(str_pos_x.c_str());
	std::string str_pos_y = obj.child("Position").attribute("y").value(); float posy = atof(str_pos_y.c_str());
	std::string str_pos_z = obj.child("Position").attribute("z").value(); float posz = atof(str_pos_z.c_str());
		
	//orientation... need to check this, currently wrong orientations...
	std::string str_quat_w = obj.child("Orientation").attribute("w").value(); float quatw = atof(str_quat_w.c_str());
	std::string str_quat_x = obj.child("Orientation").attribute("x").value(); float quatx = atof(str_quat_x.c_str());
	std::string str_quat_y = obj.child("Orientation").attribute("y").value(); float quaty = atof(str_quat_y.c_str());
	std::string str_quat_z = obj.child("Orientation").attribute("z").value(); float quatz = atof(str_quat_z.c_str());

	
	AABSEngine::Core::Point3 initPosition(posx,posy,posz);
	//m_physicsManager->ConvertToQuaternion(quatw, quatx, quaty, quatz);
	AABSEngine::Core::Quaternion initRotation(quatw,quatx,quaty,quatz);

	std::string collisionGroup = obj.child_value("CollisionGroup"); 
	if(collisionGroup == "ENV")
	{
		parentNode->setVisible(false);
		m_physicsManager->AddObject(gObj, physicsObjectName, initPosition, initRotation, AABSEngine::Physics::PhysicsManager::CollisionMask::COL_ENVIRONMENT, AABSEngine::Physics::ENV_COLLISION_FILTER); //setup the physics object with collision filter and mask
	}
	else
	{
		m_physicsManager->AddObject(gObj, physicsObjectName, initPosition, initRotation); //setup the physics object
	}
		
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

    return true;
}

bool AABSApplication::DeserializeInteractiveObject(AABSEngine::Core::InteractiveObject* iObj, pugi::xml_node obj)
{
	DeserializeGameObject(iObj, obj.child("Object"), QueryMasks::TAVERN_INTERACTABLE);
	iObj->SetCoreType("Interactive");
    /* deserialize affordances */
    pugi::xml_node affordances = obj.child("Affordances");
    if (affordances.name() != "")
	{
		for (pugi::xml_node affordance = affordances.first_child(); affordance; affordance = affordance.next_sibling())
		{
		  std::string type = affordance.attribute("Type").value();
		  int basevalue = atoi(affordance.attribute("BaseValue").value());
		  int modifier = atoi(affordance.attribute("ExecutionModifier").value()); /* TODO error checking */
		  iObj->AddAffordance(type, basevalue);
		  iObj->AddAffordanceModifier(type, modifier);
		  AffordanceManager::Instance()->RegisterAffordanceProvider(type, iObj->GetType());
		}
	}
    return true;
}

bool AABSApplication::DeserializeAgent(AABSEngine::AI::Agent* aObj, pugi::xml_node obj)
{
    DeserializeInteractiveObject(aObj, obj.child("InteractiveObject"));
    /* deserialize agent stuff */
    std::string type = obj.child_value("AgentType");
    std::string name = obj.child_value("Name");
    
    aObj->SetAgentName(name);
    aObj->SetAgentType(type);
	aObj->SetCoreType("Agent");

    float awareness = atof(obj.child_value("AwarenessRadius"));
    aObj->SetAwarenessRadius(awareness);
    pugi::xml_node actionaffordancepairs = obj.child("ActionAffordanceMap");
    if (actionaffordancepairs.name() != "")
	{
		for (pugi::xml_node actionaffordancepair = actionaffordancepairs.first_child(); actionaffordancepair; actionaffordancepair = actionaffordancepair.next_sibling())
		{
		  std::string action = actionaffordancepair.attribute("Action").value();
		  std::string affordancestr = actionaffordancepair.attribute("Affordance").value();/* TODO error checking */
		  aObj->AddAffordanceActionPair(affordancestr, action);
		}
	}

    pugi::xml_node needs = obj.child("Needs");
    if (needs.name() != "")
	{
    for (pugi::xml_node need = needs.first_child(); need; need = need.next_sibling())
    {
		std::string needstr = need.attribute("Type").value(); /* TODO error checking */
		if (needstr != "")
		{
			aObj->AddNeed(needstr);
		}
    }
	}
	  
	pugi::xml_node traits = obj.child("Traits");
    if (needs.name() != "")
	{
		for (pugi::xml_node trait = traits.first_child(); trait; trait = trait.next_sibling())
		{
			std::string traitstr = trait.attribute("Name").value(); /* TODO error checking */
			if (traitstr != "")
				aObj->AddTrait(traitstr);
		}
	}

    return true;
}

void AABSApplication::UpdateInfoText()
{
	if(m_player->GetTarget() != NULL)
	{
		AABSEngine::Core::GameObject *target = m_player->GetTarget();
		std::string infoText;
		infoText = "Object ID: " + target->GetName() + "\n";

		//check if this is an agent
		if(target->GetCoreType() == "Agent")
		{
			target->GetSceneNode()->showBoundingBox(true);
			AABSEngine::AI::Agent* agent = (AABSEngine::AI::Agent*)target;
			infoText += "\nAgent: " + agent->GetAgentName(); //write the name

			if(agent->GetCurrentAction() != NULL)
			{
				infoText +="\nAction: " + agent->GetCurrentAction()->GetName(); //current action
			}

			infoText += "\nEmotion: " + agent->GetEmotion(); //current emotion

			std::stringstream ss;
			ss << agent->GetMoodValue();
			infoText += "\nMood: " + agent->GetMood() + " - " + ss.str(); //current mood

			//get the needs
			std::vector<AABSEngine::AI::Need*> needList = agent->GetNeeds()->GetNeeds();
			for(int i=0; i<needList.size(); i++)
			{
				AABSEngine::AI::Need *need = needList[i];
				std::stringstream ssNeed;
				ssNeed << need->GetBase();
				
				infoText += "\nNeed: " + need->GetName() + " - " + ssNeed.str();
			}

			//get the traits
			AABSEngine::AI::Personality *persona = agent->GetPersonality();
			if(persona != NULL)
			{
				std::vector<AABSEngine::AI::Trait*> traitList = persona->GetTraits();
				for(int i=0; i<traitList.size(); i++)
				{
					AABSEngine::AI::Trait *trait = traitList[i];				
					infoText += "\nTrait: " + trait->GetName();
				}
			}
		}

		TextRenderer::getSingleton().setText("txtStatus", infoText);
	}

	if(showPhoto)
	{
		TextRenderer::getSingleton().setText("txtStatus", "");
	}
}