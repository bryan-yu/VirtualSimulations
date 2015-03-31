#include "StdAfx.h"

#include "TidyState.h"
#include "Singleton.h"
#include "PatronActionEvaluatorState.h"
#include "ActionBlackboard.h"

using namespace AABSEngine::AI;

void TidyState::Enter(Agent* agent)
{
	//std::cout << "Agent " << agent->GetAgentName() << ": Entering Tidy State" << std::endl;
}

void TidyState::Execute(Agent* agent)
{
	//std::cout << "Agent " << agent->GetAgentName() << ": Executing Tidy State" << std::endl;
	if (agent->GetTarget())
	{
		agent->GetTarget()->MarkForRemoval();

		//remove from the list completely now
		ActionBlackboard* bb = AABSEngine::Core::Singleton<ActionBlackboard>::Instance();
		bb->RemoveEntry(bb->GetEntryFromActionObject(agent->GetCurrentAction()->GetName(), agent->GetTarget()));

		agent->SetTarget(NULL);
	}
	agent->GetStateMachine()->ChangeState(AABSEngine::Core::Singleton<PatronActionEvaluatorState>::Instance());
}

void TidyState::Exit(Agent* agent)
{
	//std::cout << "Agent " << agent->GetAgentName() << ": Exiting Tidy State" << std::endl;
}
