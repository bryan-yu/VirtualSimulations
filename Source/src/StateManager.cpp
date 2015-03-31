#include "StdAfx.h"
#include "StateManager.h"

#include "Singleton.h"
#include "DrinkState.h"
#include "SocialiseState.h"
#include "UrinateState.h"
#include "TidyState.h"
#include "CalmPatronState.h"
#include "EjectPatronState.h"

using namespace AABSEngine::Core;
using namespace AABSEngine::AI;

StateManager::StateManager()
{

}

State<Agent>* StateManager::GetState(std::string state)
{
	if (state == "DrinkState")
		return Singleton<DrinkState>::Instance();
	else if (state == "SocialiseState")
		return Singleton<SocialiseState>::Instance();
	else if (state == "UrinateState")
		return Singleton<UrinateState>::Instance();
	else if (state == "TidyState")
		return Singleton<TidyState>::Instance();
	else if (state == "CalmPatronState")
		return Singleton<CalmPatronState>::Instance();
	else if (state == "EjectPatronState")
		return Singleton<EjectPatronState>::Instance();
	else return NULL;
}