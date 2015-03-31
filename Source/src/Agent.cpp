#include "StdAfx.h"
#include "Agent.h"

#include "Singleton.h"
#include "GameObjectManager.h"
#include "NeedManager.h"
#include "PatronActionEvaluatorState.h"
#include "TraitManager.h"
#include "Trait.h"
#include "ActionBlackboard.h"

using namespace AABSEngine::AI;

Agent::Agent()
{
	m_Needs = new AABSEngine::AI::NeedComposition();
	m_Target = NULL;
	m_currentAction = NULL;
	m_stateMachine = new StateMachine<Agent>(this);
	m_stateMachine->SetCurrentState(AABSEngine::Core::Singleton<PatronActionEvaluatorState>::Instance());
	m_actionDuration = 1.0;
	m_actionCounter = 0.0;
	m_previousAnimation = "";
	m_currentNeed = NULL;
	m_personality = NULL;
}

Agent::~Agent()
{
  delete m_Needs;
  delete m_stateMachine;
  delete m_currentAction;
  delete m_personality;
}

void Agent::AddNeed(std::string need)
{
  m_Needs->AddNeed(need);
}

NeedComposition* Agent::GetNeeds()
{
  return m_Needs;
}

void Agent::SetCurrentNeed(Need* need)
{
  m_currentNeed = need;
}

Need* Agent::GetCurrentNeed()
{
  return m_currentNeed;
}

StateMachine<Agent>* Agent::GetStateMachine() 
{
  return m_stateMachine;
}

AABSEngine::Core::InteractiveObject* Agent::GetTarget() 
{
  return m_Target;
}

void Agent::SetTarget(AABSEngine::Core::InteractiveObject* target)
{
  m_Target = target;
}

Action* Agent::GetCurrentAction()
{
  return m_currentAction;
}

void Agent::SetCurrentAction(Action* action)
{
  m_currentAction = action;
}

void Agent::SetPreviousAction(std::string action)
{
  m_previousAction = action;
}

void Agent::SetDeltaTime(float dt)
{
	m_deltaTime=dt;
}

bool Agent::IsActionDone()
{
	m_actionCounter += m_deltaTime;
	if(m_actionCounter>=m_actionDuration)
	{
		m_actionCounter = 0;
		return true;
	}

	return false;
}


//currently hard coded and repetitive :( todo: redo...
void Agent::SetNewAnimation(std::string name)
{
	//TODO: should be using xml to load in data for this instead...
	if(b_animationSet)
	{
		if(m_previousAnimation!="")
		{
			ent->getAnimationState(m_previousAnimation)->setEnabled(false);
		}
		if(name=="Drink")
		{
			m_AnimationState = ent->getAnimationState("StandDrinkDrink");
			m_previousAnimation = "StandDrinkDrink";
			m_AnimationState->setLoop( true );
			m_AnimationState->setEnabled( true );
		}
		else if(name=="Urinate")
		{
			m_AnimationState = ent->getAnimationState("Sit");
			m_previousAnimation = "Sit";
			m_AnimationState->setLoop( true );
			m_AnimationState->setEnabled( true );
		}
		else if(name=="Socialise")
		{
			m_AnimationState = ent->getAnimationState("StandConverse");
			m_previousAnimation = "StandConverse";
			m_AnimationState->setLoop( true );
			m_AnimationState->setEnabled( true );
		}
	}
}

const std::vector<AABSEngine::Core::InteractiveObject*>* Agent::FindNearbyObjectsByType(std::string type)
{
  std::vector<InteractiveObject*>* objs = new std::vector<InteractiveObject*>();
  std::vector<GameObject*>* vec = AABSEngine::Core::Singleton<AABSEngine::Core::GameObjectManager>::Instance()->GetObjectList();

  for (std::vector<GameObject*>::iterator it = vec->begin(); it != vec->end(); it++)
  {
    if ((*it)->GetType() == type)
    {
      AABSEngine::Core::Vector3 me, him;
      me = AABSEngine::Core::Vector3::ToVec3(this->GetSceneNode()->getPosition());
      him = AABSEngine::Core::Vector3::ToVec3((*it)->GetSceneNode()->getPosition());
      if (AABSEngine::Core::Vector3(him - me).magnitude() < m_radiusOfAwareness)
      {
          objs->push_back((InteractiveObject*)*it);
      }
    }
  }

  if (objs->size() < 1)
  {
    delete objs;
    objs = NULL;
  }
  return objs;
}

const std::vector<AABSEngine::Core::InteractiveObject*>* Agent::FindNearbyObjectsByTypes(const std::vector<std::string>* types)
{
  std::vector<InteractiveObject*>* objs = new std::vector<InteractiveObject*>();
  std::vector<GameObject*>* vec = AABSEngine::Core::Singleton<AABSEngine::Core::GameObjectManager>::Instance()->GetObjectList();

  for (std::vector<GameObject*>::iterator it = vec->begin(); it != vec->end(); it++)
  {
    for (std::vector<std::string>::const_iterator typeit = types->begin(); typeit != types->end(); typeit++)
    {
      std::string type = *typeit;
      if ((*it)->GetType() == type)
      {
        AABSEngine::Core::Vector3 me, him;
        me = AABSEngine::Core::Vector3::ToVec3(this->GetSceneNode()->getPosition());
        him = AABSEngine::Core::Vector3::ToVec3((*it)->GetSceneNode()->getPosition());
        if (AABSEngine::Core::Vector3(him - me).magnitude() < m_radiusOfAwareness)
        {
          objs->push_back((InteractiveObject*)*it);
        }
      }
    }
  }

  if (objs->size() < 1)
  {
    delete objs;
    objs = NULL;
  }
  return objs;
}

void Agent::AddAffordanceActionPair(std::string affordance, std::string action)
{
  if (m_affordanceActionMap.count(affordance) < 1)
    m_affordanceActionMap.insert(std::make_pair(affordance, action));
}

std::string Agent::GetActionFromAffordance(std::string affordance)
{
  if (m_affordanceActionMap.count(affordance) > 0)
    return m_affordanceActionMap[affordance];
  return "";
}

void Agent::AddTrait(std::string name)
{
  if (m_personality == NULL)
    m_personality = new Personality();
  if (!m_personality->Access(name))
  {
    m_personality->Create<Trait>((AABSEngine::Core::Singleton<TraitManager>::Instance()->GetTraitDefinition(name)));
  }
}

Trait* Agent::GetTrait(std::string name)
{
  return m_personality->Access(name);
}

Trait* Agent::GetTraitFromNeed(std::string need)
{
	if(m_personality != NULL)
		return m_personality->AccessByNeed(need);
	else
		return NULL;
}

void Agent::SetAwarenessRadius(float radius)
{
  m_radiusOfAwareness = radius;
}

void Agent::Update()
{
  /* apply needs periodic updates */
  NeedVector needs = m_Needs->GetNeeds();
  for (NeedVector::iterator it = needs.begin(); it != needs.end(); it++)
  {
    (*it)->Evaluate(0.0);
  }
  /* update state machine */
  m_stateMachine->Update();
}

void Agent::InitialiseAgent()
{
	Ogre::SceneNode *scn = (Ogre::SceneNode*)GetSceneNode()->getChild(0);
	ent = (Ogre::Entity*)scn->getAttachedObject(0);
	m_AnimationState = ent->getAnimationState("StandIdle");
	m_previousAnimation = "StandIdle";
    m_AnimationState->setLoop( true );
    m_AnimationState->setEnabled( true );
	b_animationSet=true;

	b_MoodColourChange = true;
	b_EmotionColourChange = false;

	m_MoodName = "NEUTRAL";
	m_MoodValue = 0.0;
	m_EmoName = "";
	m_EmoValue = 0.0;
	m_ChangeRate = 1.0;

	m_MoodTimer = 0.0;

	m_Mood.r = 1.0;
	m_Mood.g = 0.5;
	m_Mood.b = 1.0;
	m_Mood.a = 1.0;

	m_GoodMood.r = 1.0;
	m_GoodMood.g = 0.82;
	m_GoodMood.b = 0.0;
	m_GoodMood.a = 1.0;

	m_BadMood.r = 0.0;
	m_BadMood.g = 0.0;
	m_BadMood.b = 1.0;
	m_BadMood.a = 1.0;

	m_Emo.r = 0.0;
	m_Emo.g = 0.0;
	m_Emo.b = 0.0;
	m_Emo.a = 1.0;

	m_Current.r = m_Mood.r;
	m_Current.g = m_Mood.g;
	m_Current.b = m_Mood.b;
	m_Current.a = m_Mood.a;

	m_Material = ent->getSubEntity(0)->getMaterial();
	m_Material->setAmbient(Ogre::ColourValue(m_Current.r,m_Current.g,m_Current.b));
	m_Material->setDiffuse(Ogre::ColourValue(m_Current.r,m_Current.g,m_Current.b,1.0));
}

void Agent::AnimationUpdate(float dt)
{
	if(b_animationSet)
		m_AnimationState->addTime(dt);

}

void Agent::UpdateEmotionColour(float dt)
{
	//std::cout<<"Emotion: "<<m_EmoName<<"\tMood: "<<m_MoodName<<" "<<m_MoodValue<<std::endl;//debug
	//update Mood...
	m_MoodTimer+=dt;
	if(m_MoodTimer>=30)
	{
		m_MoodTimer-=30;
		if(m_MoodValue>0)
		{
			m_MoodValue--;
			if(m_MoodValue<0)
				m_MoodValue=0;
		}
		else if(m_MoodValue<0)
		{
			m_MoodValue++;
			if(m_MoodValue>0)
				m_MoodValue=0;
		}
	}
	if(m_EmoDuration>0)
	{
		/*//adjust mood colour... not done yet... disregard for now
		m_Mood.r -= ((dt / m_ChangeRate)*(m_Emo.r - m_Mood.r));
		m_Mood.g -= ((dt / m_ChangeRate)*(m_Emo.g - m_Mood.g));
		m_Mood.b -= ((dt / m_ChangeRate)*(m_Emo.b - m_Mood.b));
		*/

		m_MoodValue += m_EmoValue*dt;
		if(m_MoodValue>=100)
			m_MoodValue = 100;
		else if(m_MoodValue<=-100)
			m_MoodValue = -100;

		//set mood name
		SetMoodName();

		m_EmoDuration -= dt;
		if(m_EmoDuration<=0)
		{
			m_EmoName = "";
			m_EmoDuration = 0.0;
			m_ChangeRate = 1.0;
		}
	}
	//update for emotion colours... not working?
	//if we should be changing the colour, find the colour between the emotion and current mood based on time...
	if(b_EmotionColourChange)
	{
		if(m_ChangeRate==0)
		{
			m_ChangeRate=1.0;
		}
		m_Current.r -= ((dt / m_ChangeRate)*(m_Emo.r - m_Mood.r));
		m_Current.g -= ((dt / m_ChangeRate)*(m_Emo.g - m_Mood.g));
		m_Current.b -= ((dt / m_ChangeRate)*(m_Emo.b - m_Mood.b));
	}

	//change the colour of the agent's material				THIS DOESN"T WORK HERE????!!!?!!?!??!!?!!??!?!!!??!11111//?!!?!
	GetMaterial()->setAmbient(Ogre::ColourValue(m_Current.r, m_Current.g, m_Current.b));
	GetMaterial()->setDiffuse(Ogre::ColourValue(m_Current.r, m_Current.g, m_Current.b, m_Current.a));

	if(b_EmotionColourChange)
	{

		//if colour is back to mood (or beyond), set to mood
		if(	(((m_Emo.r - m_Mood.r<=0)&&(m_Current.r - m_Mood.r>=0))||((m_Emo.r - m_Mood.r>=0)&&(m_Current.r - m_Mood.r<=0)))&&
			(((m_Emo.g - m_Mood.g<=0)&&(m_Current.g - m_Mood.g>=0))||((m_Emo.g - m_Mood.g>=0)&&(m_Current.g - m_Mood.g<=0)))&&
			(((m_Emo.b - m_Mood.b<=0)&&(m_Current.b - m_Mood.b>=0))||((m_Emo.b - m_Mood.b>=0)&&(m_Current.b - m_Mood.b<=0))))
		{
			/*//test... set back to emotion colour again instead
			m_Current.r=m_Emo.r;
			m_Current.g=m_Emo.g;
			m_Current.b=m_Emo.b;
			*/
		
			m_Current.r = m_Mood.r;
			m_Current.g = m_Mood.g;
			m_Current.b = m_Mood.b;
			m_Current.a = m_Mood.a;
			b_EmotionColourChange = false;
		}	
	}
}

void Agent::TriggerEmotion(float value, float duration, float rate, std::string name, Ogre::ColourValue RGB)
{
	m_EmoValue = value;//used to modify/increment mood
	m_EmoDuration = duration;
	m_EmoName = name;
	m_ChangeRate = rate;//pulse rate per second.
	m_Emo.r = RGB.r;
	m_Emo.g = RGB.g;
	m_Emo.b = RGB.b;
	m_Emo.a = RGB.a;
	b_EmotionColourChange = true;	
}

void Agent::SetMoodName()
{
    if(m_MoodValue>10)
		m_MoodName = "GOOD";
	else if(m_MoodValue<-10)
		m_MoodName = "BAD";
	else
		m_MoodName = "NEUTRAL";
}