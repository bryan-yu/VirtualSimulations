#include "StdAfx.h"
#include "SocialiseState.h"
#include "Singleton.h"
#include "PatronStates.h"

void SocialiseState::Enter(Agent* agent)
{
  //std::cout << "[Agent " << agent->ID() << "] Entering Socialise State" << std::endl;
}

void SocialiseState::Execute(Agent* agent)
{
	//if(agent->IsActionDone())
	//{
		agent->GetCurrentAction()->ResolveModifiers(agent->GetNeeds()); /* resolve needs modifiers for this state */
		//std:: cout << " [Agent " << agent->ID() << "] Socialising with Agent " << agent->GetTarget()->ID() << std::endl;
		Need* need = agent->GetCurrentNeed();
		if (need->GetBase() > ((need->GetHighWaterMark() / need->GetRange()) * 100))
			agent->GetStateMachine()->ChangeState(AABSEngine::Core::Singleton<PatronActionEvaluatorState>::Instance());
	//}
}

void SocialiseState::Exit(Agent* agent)
{
  //std::cout << "[Agent " << agent->ID() << "] Leaving Socialise State" << std::endl;
}