#include "StdAfx.h"
#include "UrinateState.h"
#include "Singleton.h"
#include "PatronStates.h"

void UrinateState::Enter(Agent* agent)
{
    //std::cout << "[Agent " << agent->ID() << "] Entering Urinate State" << std::endl;
}

void UrinateState::Execute(Agent* agent)
{
    //std::cout << "[Agent " << agent->ID() << "] Takin' a wizz" << std::endl;
  
	agent->GetCurrentAction()->ResolveModifiers(agent->GetNeeds()); /* resolve needs modifiers for this state */
  
	/* see if we need to change state (need satisfied) */
	Need* need = agent->GetCurrentNeed();
	if (need->GetBase() > ((need->GetHighWaterMark() / need->GetRange()) * 100))
		agent->GetStateMachine()->ChangeState(AABSEngine::Core::Singleton<PatronActionEvaluatorState>::Instance());
}

void UrinateState::Exit(Agent* agent)
{
    //std::cout << "[Agent " << agent->ID() << "] Leaving Urinate State" << std::endl;
}