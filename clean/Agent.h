#pragma once

#include <string>

#include "StateMachine.h"
#include "NeedComposition.h"
#include "InteractiveObject.h"
#include "Action.h"
#include "Personality.h"


namespace AABSEngine
{
  namespace AI
  {
	/**
	 * @class Agent
	 * 
	 * @brief Artificial Intelligence entity utilising emotions, and needs...
	 *
	 * @author AABS
	 * @version X
	 * @date October 2013
	 *
	 */

    class Agent: public AABSEngine::Core::InteractiveObject
    {
    public:
		Agent();
		~Agent();
		
		/**
		 * @brief Add a need to the agent's system
		 */
		void AddNeed(std::string need);

		/**
		 * @brief Return the agent's needs
		 */
		NeedComposition* GetNeeds();

		/**
		 * @brief Set the agent's current need
		 */
		void SetCurrentNeed(Need* need);

		/**
		 * @brief Returns the agent's current need
		 */
		Need* GetCurrentNeed();

		/**
		 * @brief Returns the agent's state machine
		 */
		StateMachine<Agent>* GetStateMachine();

		/**
		 * @brief Returns the agent's current interactive object target
		 */
		InteractiveObject* GetTarget();

		/**
		 * @brief Sets the agent's target to the specified interactive object
		 */
		void SetTarget(InteractiveObject* target);

		/**
		 * @brief Returns the agent's current action
		 */
		Action* GetCurrentAction();

		/**
		 * @brief Sets the agent's current action
		 */
		void SetCurrentAction(Action* action);

		/**
		 * @brief Sets the agent's previous action
		 */
		void SetPreviousAction(std::string action);

		/**
		 * @brief Returns the agent's previous action
		 */
		std::string GetPreviousAction(){return m_previousAction;}

		/**
		 * @brief Add affordance pairs to agent's affordance map
		 */
		void AddAffordanceActionPair(std::string affordance, std::string action);

		/**
		 * @brief Return the action for a specified affordance
		 */
		std::string GetActionFromAffordance(std::string affordance);

		/**
		 * @brief Sets the agent's 'awareness' radius
		 */
		void SetAwarenessRadius(float radius);

		/**
		 * @brief Returns the emotion currently affecting the agent
		 */
		std::string GetEmotion(){return m_EmoName;}

		/**
		 * @brief Returns the agent's mood
		 */
		std::string GetMood(){return m_MoodName;}


		/**
		 * @brief Initialises majority of agent's initial data
		 */
		void InitialiseAgent();

		/**
		 * @brief Handles agent animations
		 */
		void AnimationUpdate(float dt);

		/**
		 * @brief Handles agent emotion and mood colour
		 */
		void UpdateEmotionColour(float dt);

		/**
		 * @brief Set new animation for the agent to play
		 */
		void SetNewAnimation(std::string name);


		/**
		 * @brief Set delta time
		 */
		void SetDeltaTime(float dt);

		/**
		 * @brief Boolean state for whether current action has completed or not
		 */
		bool IsActionDone();

		/**
		 * @brief Trigger an emotion in the agent
		 */
		void TriggerEmotion(float value, float duration, float rate, std::string name, Ogre::ColourValue RGB);

		/**
		 * @brief Returns a pointer to the agent's material
		 */
		Ogre::MaterialPtr GetMaterial(){return m_Material;}

		/**
		 * @brief Returns the agent's current colour
		 */
		Ogre::ColourValue GetCurrentColour(){return m_Current;}

		/** 
		* @brief Returns a vecotr of nearby game objects with the given type.
		* MAKE SURE YOU DELETE THE RESULT RETURNED FROM THIS FUNCTION 
		*/
		const std::vector<InteractiveObject*>* FindNearbyObjectsByType(std::string type);
		const std::vector<InteractiveObject*>* FindNearbyObjectsByTypes(const std::vector<std::string>* types);

		/**
		 * @brief Adds a trait to the agent for its' personality
		 */
		void AddTrait(std::string name);

		/**
		 * @brief Returns an agent's trait
		 */
        Trait* GetTrait(std::string name);

		/**
		 * @brief Return triat associated with specified need
		 */
        Trait* GetTraitFromNeed(std::string need);

		/**
		 * @brief Agent's state machine update
		 */
		void Update(); /* TODO duration ??? */

		/**
		 * @brief Returns the agent type identifier.
		 */
		std::string GetAgentType() { return m_agenttype; }
		/** 
		 * @brief Sets the agent type identifier.
		 */
		void SetAgentType(std::string type) { m_agenttype = type; }
		/**
		 * @brief Returns the agent name
		 */
		std::string GetAgentName() { return m_agentname; }
		/** 
		 * @brief Sets the agent name.
		 */
		void SetAgentName(std::string name) { m_agentname = name; }

		/**
		 * @brief Overrides the mood value 
		 */
		void SetMood(Decimal val) { m_MoodValue = val; SetMoodName(); };

		/**
		 * @brief get the mood value
		 */
		float GetMoodValue() { return m_MoodValue; }

		/**
		 * @brief get personality
		 */
		Personality* GetPersonality() const { return m_personality; }

    protected:
    private:
		NeedComposition* m_Needs;
		Need* m_currentNeed;

		InteractiveObject* m_Target; // TODO GameObject* ???
		Action* m_currentAction;
		std::string m_previousAction;
		StateMachine<Agent>* m_stateMachine;
		std::map<std::string, std::string> m_affordanceActionMap;

		Personality* m_personality;
	  
		float m_actionDuration;
		float m_actionCounter;

		std::string m_MoodName;
		float m_MoodValue;
		std::string m_EmoName;
		float m_EmoValue;
		float m_EmoDuration;
		float m_ChangeRate;

		float m_deltaTime;
		float m_radiusOfAwareness;

		Ogre::ColourValue m_Emo;
		Ogre::ColourValue m_Mood;
		Ogre::ColourValue m_GoodMood;
		Ogre::ColourValue m_BadMood;
		Ogre::ColourValue m_Current;

		float m_MoodTimer;

		bool b_MoodColourChange;
		bool b_EmotionColourChange;
		bool b_animationSet;

		bool b_hasDrink;//not used yet

		std::string m_previousAnimation;
		Ogre::Entity *ent;
		Ogre::AnimationState *m_AnimationState;
	  	Ogre::MaterialPtr m_Material;

		std::string m_agenttype;
		std::string m_agentname;

		/**
		 * @brief Sets mood name to the appropriate string based on m_MoodValue.
		 */
		void SetMoodName();
    };
  }
}