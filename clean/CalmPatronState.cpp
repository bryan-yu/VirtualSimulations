#include "StdAfx.h"

#include "CalmPatronState.h"
#include "Singleton.h"
#include "PatronActionEvaluatorState.h"

using namespace AABSEngine::AI;

void CalmPatronState::Enter(Agent* agent)
{
  std::cout << "Agent " << agent->GetAgentName() << ": Entering Calm Patron State" << std::endl;
}

void CalmPatronState::Execute(Agent* agent)
{
  std::cout << "Agent " << agent->GetAgentName() << ": Executing Calm Patron State" << std::endl;
  if (agent->GetTarget())
  {
    if (dynamic_cast<Agent*>(agent->GetTarget()))
    {
      ((Agent*)agent->GetTarget())->SetMood(0.0); /* clear mood */
    }
  }
  agent->GetStateMachine()->ChangeState(AABSEngine::Core::Singleton<PatronActionEvaluatorState>::Instance());
}

void CalmPatronState::Exit(Agent* agent)
{
  std::cout << "Agent " << agent->GetAgentName() << ": Exiting Calm Patron State" << std::endl;
}
