#pragma once

#include "State.h"
#include "Need.h"
#include "NeedComposition.h" 

#include <map>

namespace AABSEngine
{
	namespace AI
	{
		/**
		* @struct Emotion
		* @brief Emotion associated with action
		*/
		typedef struct 
		{
			float percentage;
			float duration;
			Ogre::ColourValue colour;
		}Emotion;

		class Agent;

		/**
		* @class Action
		* 
		* @brief An action able to be taken by an agent, can affect interactable objects
		*
		* @author AABS
		* @version X
		* @date October 2013
		*
		*/
		class Action
		{
		private:
			std::string m_name;
			State<Agent>* m_action;
			std::map<std::string, int> m_localNeedModifiers; 
			std::map<std::string, int> m_targetNeedModifiers;
			std::map<std::string, Emotion> m_localEmotionModifiers;
			std::map<std::string, Emotion> m_targetEmotionModifiers;
		protected:
		public:
			Action();
			Action(Action& act);

			/**
			* @brief Set the name of this action to specified string
			* @param name Name of the action (string)
			* @return void
			*/
			void SetName(std::string name) { m_name = name; }

			/**
			* @brief Returns the name of this action
			* @return std::string
			*/
			std::string GetName() { return m_name; }

			/**
			* @brief Set the action 'state' for this action
			* @param action (State<Agent>*)
			* @return void
			*/
			void SetAction(State<Agent>* action);

			/**
			* @brief Returns the action 'state' for this action
			* @return State<Agent>*
			*/
			State<Agent>* GetAction();

			/**
			* @brief Add local need modifier to map
			* @param need the name of the local need modifier (std::string)
			* @param percentage Value of the modifier (int)
			* @return void
			*/
			void AddLocalNeedModifier(std::string need, int percentage);

			/**
			* @brief Add target need modifier to map
			* @param need the name of the target need modifier (std::string)
			* @param percentage Value of the modifier (int)
			* @return void
			*/
			void AddTargetNeedModifier(std::string need, int percentage);

			/**
			* @brief Add local emotion modifier to map
			* @param name the name of the local emotion modifier (std::string)
			* @param emotion Emotion data associated (Emotion)
			* @return void
			*/
			void AddLocalEmotionModifier(std::string name, Emotion emotion);

			/**
			* @brief Add target emotion modifier to map
			* @param name the name of the target emotion modifier (std::string)
			* @param emotion Emotion data associated (Emotion)
			* @return void
			*/
			void AddTargetEmotionModifier(std::string name, Emotion emotion);

			/**
			* @brief Resolve modifiers for needs
			* @param needs (NeedComposition*)
			* @return void
			*/
			void ResolveModifiers(NeedComposition* needs); // TODO Emotions* emotions

			/**
			* @brief Returns local emotion modifiers map
			* @return std::map*
			*/
			std::map<std::string, Emotion> *GetLocalEmotionModifiers(){return &m_localEmotionModifiers;}
		};
	}
}