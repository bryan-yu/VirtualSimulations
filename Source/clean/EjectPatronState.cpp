#include "StdAfx.h"

#include "EjectPatronState.h"
#include "Singleton.h"
#include "PatronActionEvaluatorState.h"

using namespace AABSEngine::AI;

void EjectPatronState::Enter(Agent* agent)
{
  std::cout << "Agent " << agent->GetAgentName() << ": Entering Eject Patron State" << std::endl;
}

void EjectPatronState::Execute(Agent* agent)
{
  std::cout << "Agent " << agent->GetAgentName() << ": Executing Eject Patron State" << std::endl;
  if (agent->GetTarget())
  {
    /* TODO eject patron */
  }
  agent->GetStateMachine()->ChangeState(AABSEngine::Core::Singleton<PatronActionEvaluatorState>::Instance());
}

void EjectPatronState::Exit(Agent* agent)
{
  std::cout << "Agent " << agent->GetAgentName() << ": Exiting Eject Patron State" << std::endl;
}
