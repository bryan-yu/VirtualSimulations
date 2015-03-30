#pragma once

#include "BaseFactory.h"
#include "Object.h"
#include "Agent.h"

namespace AABSEngine
{
	namespace Core
	{
		/**
		* @struct GameObjectDefinition
		*
		* @brief Game object data
		*
		*/
		struct GameObjectDefinition
		{
			GameObjectDefinition(std::string meshfile, std::string pobject, Vector3 pos, Quaternion orient, bool grav, bool vis, std::string colgroup):
			m_meshfile(meshfile), m_physicsobjectname(pobject), m_position(pos), m_orientation(orient), m_gravity(grav), m_visible(vis), m_collisiongroup(colgroup) { }
			std::string m_meshfile;
			std::string m_physicsobjectname;
			Vector3 m_position;
			Quaternion m_orientation;
			bool m_gravity;
			bool m_visible;
			std::string m_collisiongroup;
		};

		/**
		* @struct InteractiveObjectDefinition
		*
		* @brief Interactive object data
		*
		*/
		struct InteractiveObjectDefinition
		{
			InteractiveObjectDefinition(GameObjectDefinition gameobject, Affordance affordance): m_gameobject(gameobject), m_affordance(affordance) {  }
			GameObjectDefinition m_gameobject;
			Affordance m_affordance; // TODO make a vector
		};

		/**
		* @struct AgentDefinition
		*
		* @brief 
		*
		*/
		struct PendingObject
		{
			GameObject *m_gameObject;
			std::string m_type;
		};

		class GameObjectManager
		{
		/**
		* @class GameObjectManager
		* 
		* @brief Game object manager
		*
		* @author AABS
		* @version X
		* @date October 2013
		*
		*/
		private:
			std::vector<PendingObject> m_pendingObjects;
			std::vector<GameObject*> m_objectList;
			std::vector<Agent*> m_agentList;
			AABSEngine::Utility::Factory<GameObject> m_gameObjectFactory;
		protected:
		public:
			GameObjectManager();
			std::vector<GameObject*>* GetObjectList() { return &m_objectList; }
			std::vector<Agent*>* GetAgentList() { return &m_agentList; }
			/**@brief Searches the map and creates a new object via m_Itr->second() which actually calls CreateRegis<AssignedType>
			**@return  NULL if no such object is found
			**@param id is the map key used to search for the item.
			**/
			GameObject* Create(std::string id);
			InteractiveObject* CreateInteractiveObject(InteractiveObjectDefinition def);
			void AddObject(GameObject* obj, std::string type);
			void AddPendingObject(GameObject* obj, std::string type);
			void Update(float dt);
			void RemoveObject(GameObject *obj);
		};
	}
}

