#include "Testing.h"

#include "../clean/Input.h"
#include "../clean/InputManager.h"
#include "../clean/OISInputManager.h"
#include "../clean/AABSApplication.h"
#include "../clean/Camera.h"
#include "../clean/BaseFactory.h"

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <windows.h>

namespace InputTest
{
	class InputTestApplication : public Ogre::WindowEventListener, public Ogre::FrameListener
	{
	public:
		InputTestApplication()
		{
			keypresseddowntest = keyhelddowntest = keypresseduptest = keyhelduptest = false;
			mousepresseddowntest = mousepresseduptest = false;
			mousehelddowntest = mousehelduptest = false;
			mousemovetest = false;
			exitNow = false;
		}

		~InputTestApplication()
		{
		  //remove this application as window listener
			Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
			windowClosed(mWindow);

			delete mRoot; //remove Ogre root
		}

		///////////////////////////////////////////////////////////
		// Input test specific stuff
		bool keypresseddowntest;
		bool keyhelddowntest;
		bool keypresseduptest;
		bool keyhelduptest;
		bool mousepresseddowntest;
		bool mousepresseduptest;
		bool mousehelddowntest;
		bool mousehelduptest;
		bool mousemovetest;

		void kpdowntest() 
		{ 
		  keypresseddowntest = true; 
		}; 
		void kpuptest() 
		{ 
		  keypresseduptest = true; 
		};
		void khdowntest() 
		{ 
		  keyhelddowntest = true; 
		};
		void khuptest() 
		{ 
		  keyhelduptest = true; 
		}
		void mpdowntest(int x, int y) 
		{ 
		  mousepresseddowntest = true; 
		};
		void mpuptest(int x, int y) 
		{ 
		  mousepresseduptest = true; 
		};
		void mhdowntest(int x, int y) 
		{ 
		  mousehelddowntest = true; 
		};
		void mhuptest(int x, int y) 
		{ 
		  mousehelduptest = true; 
		};
		void mmovetest(int x, int y) 
		{ 
		  mousemovetest = true; 
		};

		bool checkComplete() 
		{ 
			if (keypresseddowntest && keypresseduptest && keyhelddowntest && keyhelduptest 
			&& mousepresseddowntest && mousepresseduptest && mousehelddowntest && mousehelduptest 
			&& mousemovetest)
				return true; 
			else
				return false;
		}
		void exitapp() { exitNow = true; };

		bool go()
		{
			if(!SceneManagerSetup())
			{
				return false;
			}
      	
		  CameraSetup();

		  PhysicsManagerSetup();

			//setup the input manager
			InputManagerSetup();

		  ModelsSetup();

		  //set initial mouse clipping size
		  windowResized(mWindow);

			//register as a window listener
			Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

			//alternative to the while loop
			mRoot->addFrameListener(this);
			mRoot->startRendering();

			return true;
		}

		AABSEngine::Input::InputManager* GetInputManager() { return m_inputManager; }
		private:
		bool exitNow;
		Ogre::Root* mRoot; ///< the ogre root pointer
		Ogre::String mPluginsCfg; ///< plugins config file
		Ogre::String mResourcesCfg; ///< resources config file
		Ogre::RenderWindow* mWindow; ///< rendering system (openGL or DirectX)

		AABSEngine::Input::InputManager *m_inputManager; ///< input manager
		AABSEngine::Core::SceneManager *m_sceneManager; ///< scene manager
    
		AABSEngine::Physics::PhysicsManager *m_physicsManager; ///< physics manager
		Ogre::Real deltaTime;
		AABSEngine::Rendering::Camera* m_camera;

		void ModelsSetup()
		{
			//-------adding to the scene------//
		/*

			Ogre::SceneNode *wall = m_sceneManager->CreateSceneNode("ogrehead.mesh", m_sceneManager->GetRootSceneNode());
			AABSEngine::Core::GameObject *m_wall = new AABSEngine::Core::GameObject(wall);
	
			//add this object to the physics manager
			m_physicsManager->AddObject(m_wall, AABSEngine::Physics::PhysicsManager::CollisionShape::CONVEX_DECOMPOSITION, 2);

			//TO BE REMOVED or REPLACED - calculating inertia tensor for the wall with the parameters x:20, y:30, z:3
			AABSEngine::Core::Matrix3 inertia;
			inertia[0][0] = ((float)1/12) * m_wall->GetPhysicsObject()->GetMass() * (900 + 9); //Ixx = 1/12 * mass * (y^2 + z^2)
			inertia[1][1] = ((float)1/12) * m_wall->GetPhysicsObject()->GetMass() * (400 + 9); //Iyy = 1/12 * mass * (x^2 + z^2)
			inertia[2][2] = ((float)1/12) * m_wall->GetPhysicsObject()->GetMass() * (400 + 900); //Izz = 1/12 * mass * (x^2 + y^2)
			m_wall->GetPhysicsObject()->SetITensor(inertia);
			*/

			AABSEngine::Utility::Factory<AABSEngine::Core::GameObject> gameObjectFactory;
			gameObjectFactory.Register<AABSEngine::Core::GameObject>("AABSFactory");

			std::ifstream inputFile;
			inputFile.open("../resources/scripts/import_model.txt");
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
					std::vector<std::string> lineData;
					AABSEngine::Utility::StringTokenizer::TokenizeString(line, lineData, ',');

					if(lineData.size() == 8)
					{
						//first item is the name of the mesh
						std::string meshName = lineData[0];

						//next 3 items are the position in the world
						float posX = std::atof(lineData[1].c_str());
						float posY = std::atof(lineData[2].c_str());
						float posZ = std::atof(lineData[3].c_str());

						//next 4 items are the orientation
						float angleW = std::atof(lineData[4].c_str());
						float rotX = std::atof(lineData[5].c_str());
						float rotY = std::atof(lineData[6].c_str());
						float rotZ = std::atof(lineData[7].c_str());

						Ogre::SceneNode *sn = m_sceneManager->CreateSceneNode(meshName, m_sceneManager->GetRootSceneNode());
						AABSEngine::Core::GameObject *gObj = gameObjectFactory.Create("AABSFactory");

						//set position and orientation
						sn->setPosition(posX, posY, posZ);
						Ogre::Quaternion orient(Ogre::Angle(angleW), Ogre::Vector3(rotX, rotY, rotZ));
						sn->setOrientation(orient);

						gObj->SetSceneNode(sn);
						m_sceneManager->AddGameObject(gObj);

					}
				}
			}

			inputFile.close();
		}
		void PhysicsManagerSetup()
	{
		//setup physics world
		m_physicsManager = AABSEngine::Physics::PhysicsManager::Instance();
		m_physicsManager->SetupPhysicsWorld(m_sceneManager->GetOgreSceneManager());
	}
		  void CameraSetup()
	{
		m_camera = m_sceneManager->CreateCamera("DefaultCamera", Ogre::Vector3(0,0, 5), Ogre::Vector3(0,1,10), Ogre::Quaternion::IDENTITY, 0.1, 1000, 60);

		//-------creating viewport-------//
		Ogre::Viewport *vp = mWindow->addViewport(m_sceneManager->GetCamera("DefaultCamera"));
		vp->setBackgroundColour(Ogre::ColourValue(51.0f/255.0f,24.0f/255.0f,183.0f/255.0f));

		//alter the camera aspect ratio to match the viewport
		m_sceneManager->GetCamera("DefaultCamera")->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	}

		bool SceneManagerSetup()
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

		virtual void InputManagerSetup()
			{
				using namespace AABSEngine::Input;
		  //setup input
			size_t windowHnd = 0;
			std::ostringstream windowHndStr;
		  mWindow->getCustomAttribute("WINDOW", &windowHnd);
			windowHndStr << windowHnd;
		  m_inputManager = (new AABSOISInputManager(windowHndStr.str()));
				m_inputManager->Register(new KeyboardEvent(A, KEY_DOWN, ON_PRESS), boost::bind(&InputTestApplication::keypresseddowntest, this));
				m_inputManager->Register(new KeyboardEvent(A, KEY_DOWN, ON_HOLD), boost::bind(&InputTestApplication::keyhelddowntest, this));
				m_inputManager->Register(new KeyboardEvent(A, KEY_UP, ON_PRESS), boost::bind(&InputTestApplication::keypresseduptest, this));
				m_inputManager->Register(new KeyboardEvent(A, KEY_UP, ON_HOLD), boost::bind(&InputTestApplication::keyhelduptest, this));
				m_inputManager->Register(new KeyboardEvent(Q, KEY_DOWN, ON_PRESS), boost::bind(&InputTestApplication::exitapp, this));
				m_inputManager->Register(new MouseButtonEvent(BUTTON_LEFT, BUTTON_DOWN, BUTTON_ON_PRESS), boost::bind(&InputTestApplication::mousepresseddowntest, this));
				m_inputManager->Register(new MouseButtonEvent(BUTTON_LEFT, BUTTON_DOWN, BUTTON_ON_HOLD), boost::bind(&InputTestApplication::mousehelddowntest, this));
				m_inputManager->Register(new MouseButtonEvent(BUTTON_LEFT, BUTTON_UP, BUTTON_ON_PRESS), boost::bind(&InputTestApplication::mousepresseduptest, this));
				m_inputManager->Register(new MouseButtonEvent(BUTTON_LEFT, BUTTON_UP, BUTTON_ON_HOLD), boost::bind(&InputTestApplication::mousehelduptest, this));
				m_inputManager->Register(boost::bind(&InputTestApplication::mousemovetest, this));
			}
		protected:
		  void windowResized(Ogre::RenderWindow* rw)
		  {
			  /*
			  unsigned int width, height, depth;
			  int left, top;
			  rw->getMetrics(width, height, depth, left, top);

			  const OIS::MouseState &ms = mMouse->getMouseState();
			  ms.width = width;
			  ms.height = height;
			  */
		  }

		  void windowClosed(Ogre::RenderWindow* rw)
		  {
			  /*
			  if(rw == mWindow)
			  {
				  if(mInputManager)
				  {
					  mInputManager->destroyInputObject(mMouse);
					  mInputManager->destroyInputObject(mKeyboard);

					  OIS::InputManager::destroyInputSystem(mInputManager);
					  mInputManager = 0;
				  }
			  }
			  */
		  }

		  bool frameRenderingQueued(const Ogre::FrameEvent &evt)
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

			m_camera->SetDeltaTime(deltaTime);
			m_physicsManager->Update(deltaTime);
			if (m_inputManager)
				m_inputManager->Update();
        
			  //update ogre scene manager position based on the physics objects
			  return true;
		  }
		};
	
		bool dotest()
		{
			bool success = true;

			InputTestApplication app;

			using namespace AABSEngine::Input;
			/* register functions */
			app.go();

			/* perform tests */
			int numseconds = 20;
			int sleeptime = 50;
			while (numseconds)
			{
				int innercount = 0;
				while (innercount < 1000 / 50)
				{
					Sleep(sleeptime);
			app.GetInputManager()->Update();
					innercount++;
			std::cout<<"!";
				}
				numseconds--;
			}
			app.exitapp();

			std::cout << "#################################################" << std::endl;
			std::cout << "##                 Input Tests                 ##" << std::endl;
			std::cout << "#################################################" << std::endl;
			std::cout << std::endl;
			/* key pressed down test */
			std::cout << "Test 1: Key pressed down test" << std::endl;
			print_individual_success(app.keypresseddowntest);
			success = success && app.keypresseddowntest;
			/* key held down test */
			std::cout << "Test 2: Key held down test" << std::endl;
			print_individual_success(app.keyhelddowntest);
		success = success && app.keyhelddowntest;
			/* key pressed up test */
			std::cout << "Test 3: Key pressed up test" << std::endl;
			print_individual_success(app.keypresseduptest);
		success = success && app.keypresseduptest;
			/* key held up test */
			std::cout << "Test 4: Key held up test" << std::endl;
			print_individual_success(app.keyhelduptest);
		success = success && app.keyhelduptest;
			/* mouse button pressed down test */
			std::cout << "Test 5: Mouse pressed down test" << std::endl;
			print_individual_success(app.mousepresseddowntest);
		success = success && app.mousepresseddowntest;
			/* mouse button held down test */
			std::cout << "Test 6: Mouse held down test" << std::endl;
			print_individual_success(app.mousehelddowntest);
		success = success && app.mousehelddowntest;
			/* mouse button pressed up test */
			std::cout << "Test 7: Mouse pressed up test" << std::endl;
			print_individual_success(app.mousepresseduptest);
		success = success && app.mousepresseduptest;
			/* mouse button held up test */
			std::cout << "Test 8: Mouse held up test" << std::endl;
			print_individual_success(app.mousehelduptest);
		success = success && app.mousepresseddowntest;
			/* mouse button moved test */
			std::cout << "Test 9: Mouse moved test" << std::endl;
			print_individual_success(app.mousemovetest);
		success = success && app.mousemovetest;

		return success;
	}
}