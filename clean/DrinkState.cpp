#include "StdAfx.h"
#include "DrinkState.h"
#include "Singleton.h"
#include "PatronStates.h"
#include "GameObjectManager.h"
#include "ActionBlackboard.h"

using namespace AABSEngine::AI;

void DrinkState::Enter(Agent* agent)
{
  //std::cout << "[Agent " << agent->ID() << "] Entering Drink State" << std::endl;
}

void DrinkState::Execute(Agent* agent)
{
  	agent->GetCurrentAction()->ResolveModifiers(agent->GetNeeds()); /* resolve needs modifiers for this state */

	Need* need = agent->GetCurrentNeed();
	if (need->GetBase() > ((need->GetHighWaterMark() / need->GetRange()) * 100))
    {
		using namespace AABSEngine::Core;
		agent->GetStateMachine()->ChangeState(AABSEngine::Core::Singleton<PatronActionEvaluatorState>::Instance());
		
		Affordance* aff = AffordanceManager::Instance()->CreateAffordance("Tidy", 100);
		Vector3 glasspos = Vector3::ToVec3(agent->GetSceneNode()->getPosition()); glasspos[0] = glasspos[0] - 1.0;

		InteractiveObject* obj = Singleton<GameObjectManager>::Instance()->CreateInteractiveObject(InteractiveObjectDefinition(GameObjectDefinition("Glass01.mesh", "Glass", glasspos,
		  agent->GetPhysicsObject()->GetOrientation(), true, true, ""), *aff)); 
		if (obj)
		{
			Singleton<GameObjectManager>::Instance()->AddPendingObject(obj, "InteractiveObject"); //add to pending list
		}
		delete aff;
	}
}

void DrinkState::Exit(Agent* agent)
{
  //std::cout << "[Agent " << agent->ID() << "] Leaving Drink State" << std::endl;

}
