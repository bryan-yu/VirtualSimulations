#include "StdAfx.h"
#include "AABSApplication.h"
#include "PhysicsExercise.h"
#include <OgreException.h>
#include <iostream>
#include "Singleton.h"

int main(int argc, char *argv[])
{	
	AABSApplication *app = AABSEngine::Core::Singleton<AABSApplication>::Instance();
	//PhysicsExercise app;

	try
	{
		//app.go();
		app->go();
	}
	catch (Ogre::Exception &e)
	{
        std::cerr << "An exception has occured: " <<
           e.getFullDescription().c_str() << std::endl;
	}

	return 0;
}