#include "StdAfx.h"
#include "PatronActionEvaluatorState.h"
#include "AffordanceManager.h"
#include "DrinkAffordanceEvaluator.h"
#include "ActionManager.h"
#include "Singleton.h"
#include "ActionBlackboard.h"

using namespace AABSEngine::AI;

void PatronActionEvaluatorState::Enter(Agent* agent)
{
  //std::cout << "[Agent " << agent->ID() << "] Entering Decision State" << std::endl;
}

void PatronActionEvaluatorState::Execute(Agent* agent)
{
	//std::cout << "[Agent " << agent->GetAgentName() << "] Executing Decision State" << std::endl;
	/* Check the blackboard to see if anything relevant for us */
	ActionBlackboardEntry* actionentry; 
	ActionBlackboard* bb = AABSEngine::Core::Singleton<ActionBlackboard>::Instance();
	if (actionentry = bb->GetEntryFromActionerType(agent->GetAgentType()))
	{
		if(actionentry->m_locked == false)
		{
			Action* act = AABSEngine::Core::Singleton<ActionManager>::Instance()->GetAction(actionentry->m_action);
			if (act && agent->GetTarget() == NULL)
			{
				agent->SetTarget(actionentry->m_object);
				agent->SetCurrentAction(act);

				actionentry->m_locked = true; //lock the object so no one else can access it
			}
		}
	}
	else /* otherwise handle internal needs */
	{
		/* find highest priority need */
		PrioritizedNeeds needs;
		Need* need = NULL;
		agent->GetNeeds()->Access(needs, 3); // TODO needs.size() OR fix Access(Prioritized needs) - currently doesn't order all needs and return only n. just returns ordered n
  
		if (needs.size() > 0)
		{
			PrioritizedNeeds needs2;

			/* initialise effective need values (traits applied) */
			std::map<Need*, Decimal> rollbacks;
			for (int i = 0; i < needs.size(); )
			{
			need = const_cast<Need*>(needs.top());
			needs.pop();
			Trait* t;
				rollbacks[need] = need->GetBase();
			if (t = agent->GetTraitFromNeed(need->GetName()))
			{
					need->SetBase(need->GetBase() * t->GetBias());
			}
			std::cout<< "[Agent " << agent->GetAgentName() << " ] " << need->GetName() << " - Effective Need:  " << need->GetBase() << " - Actual Need: " << rollbacks[need] << std::endl;
			needs2.push(need); 
			}
			/* select need */
			while (needs2.size())
			{
			need = const_cast<Need*>(needs2.top());
			needs2.pop();
			if (need->GetBase() < ((need->GetLowWaterMark() / need->GetRange()) * 100))
				break;
			need = NULL;
			}
			/* roll back to actual trait values */
			for (std::map<Need*, Decimal>::iterator it = rollbacks.begin(); it != rollbacks.end(); it++)
			it->first->SetBase(it->second);
		}

		if (!need)
			return;

		agent->SetCurrentNeed(need);

		/* find types of objects that fulfill the affordance which satisfies our need */
		std::string affordance = need->GetSatisfyingAffordance();
		const std::vector<std::string>* objecttypes = AffordanceManager::Instance()->GetTypesByAffordance(affordance);
		if (objecttypes == NULL || objecttypes->size() == 0)
			return; /* no objects to fulfill affordance.. not much you can do but reevaluate */
		/* find objects which satisfies affordance */
		const std::vector<AABSEngine::Core::InteractiveObject*>* objects = agent->FindNearbyObjectsByTypes(objecttypes);
		/* find object which satisfies it best */
		AffordanceEvaluator* evaluator = AffordanceManager::Instance()->GetAffordanceEvaluator(affordance);
		if (evaluator != NULL)
		{
			int maxaff= 0; 
			AABSEngine::Core::InteractiveObject* maxaffobj = NULL;
			for (std::vector<AABSEngine::Core::InteractiveObject*>::const_iterator it = objects->begin(); it != objects->end(); it++)
			{
			if ((*it) != agent) /* TODO maybe this check should besomewhere else i.e. in affordance evaluator*/
			{
				int temp = evaluator->Evaluate(agent, *it);
				if (temp > maxaff)
				{
				maxaff = temp;
				maxaffobj = *it;
				}
			}
			}
			delete evaluator;
			/* If no object found dont change state */
			if (maxaffobj == NULL)
				return;
			/* set target */
			agent->SetTarget(maxaffobj);
		}

		/* do moods */
		if(agent->GetCurrentAction()!=NULL)
		{
			agent->SetPreviousAction(agent->GetCurrentAction()->GetName());
		}
		agent->SetCurrentAction(AABSEngine::Core::Singleton<ActionManager>::Instance()->GetAction(agent->GetActionFromAffordance(need->GetSatisfyingAffordance())));
		if(agent->GetPreviousAction()!="")
		{
			if(agent->GetCurrentAction()->GetName() != agent->GetPreviousAction())
			{
				agent->SetNewAnimation(agent->GetCurrentAction()->GetName());
				//trigger emotions associated with action beginning...
				std::map<std::string, Emotion>* emotionMap=agent->GetCurrentAction()->GetLocalEmotionModifiers();
				std::map<std::string, Emotion>::iterator it; 
				for(it=emotionMap->begin();it!=emotionMap->end();it++)
				{
					agent->TriggerEmotion(it->second.percentage,it->second.duration,1.0,it->first,it->second.colour);
				}
			}
		}
	}
	if (agent->GetCurrentAction())
	{
		agent->GetStateMachine()->ChangeState(agent->GetCurrentAction()->GetAction());
	}
}

void PatronActionEvaluatorState::Exit(Agent* agent)
{
  //std::cout << "[Agent " << agent->ID() << "] Decision Made" << std::endl;
}