#include "StdAfx.h"
#include "Action.h"
#include "NeedComposition.h"
#include <cmath>
 /* program flow */
 /* create action */
 /* Action patrondrink = new Action() */
 /* patrondrink.SetAction(Singleton<PatronDrink>::Instance()); // type State<Patron> */
 /* patrondrink.AddLocalNeedModifier("thirst", 20); // need by name, percentage shift */
 // for security 
    /* securityPatronCalm.AddTargetNeedModifier("anger", "100"); // ??? */
using namespace AABSEngine::AI;

Action::Action()
{
  m_action = NULL;
}

Action::Action(Action& act)
{
  this->m_action = act.m_action;
  this->m_localNeedModifiers = act.m_localNeedModifiers;
  this->m_name = act.m_name;
  this->m_targetNeedModifiers = act.m_targetNeedModifiers;
}

void Action::SetAction(State<Agent>* action)
{
  m_action = action;
}

State<Agent>* Action::GetAction()
{
  return m_action;
}

void Action::AddLocalNeedModifier(std::string need, int percentage)
{
  m_localNeedModifiers[need] = percentage;
}

void Action::AddTargetNeedModifier(std::string need, int percentage)
{
  m_targetNeedModifiers[need] = percentage;
}

void Action::AddLocalEmotionModifier(std::string name, Emotion emotion)
{
  m_localEmotionModifiers[name] = emotion;
}

void Action::AddTargetEmotionModifier(std::string name, Emotion emotion)
{
  m_targetEmotionModifiers[name] = emotion;
}

void Action::ResolveModifiers(NeedComposition* needs)
{
  for(std::map<std::string, int>::iterator it = m_localNeedModifiers.begin(); it != m_localNeedModifiers.end(); it++)
  {
    Need* need;
    if (need = needs->Access(it->first))
    {
      Decimal change = (it->second / need->GetRange())*100;
      need->SetBase(need->GetBase() + change);
    }
  }
  for (std::map<std::string, int>::iterator it = m_targetNeedModifiers.begin(); it != m_targetNeedModifiers.end(); it++)
  {
    //Agent* target;
    //if (target = dynamic_cast<Agent*>(agent->GetTarget())) // TODO
    {
      Need* need;
      if (need = needs->Access(it->first))
      {
        Decimal change = (it->second / need->GetRange())*100;
        need->SetBase(need->GetBase() + change);
      }
    }
  }
}