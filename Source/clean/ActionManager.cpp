#include "StdAfx.h"
#include "ActionManager.h"
#include "Singleton.h"
#include "StateManager.h"

using namespace AABSEngine::AI;

ActionManager::ActionManager()
{

}

bool ActionManager::Initialise()
{
  bool success = true;
 
  pugi::xml_document xDoc;
	if(!xDoc.load_file("../resources/scripts/Actions.xml"))
	{
		return false;
	}

	pugi::xml_node objectNodes = xDoc.child("Actions");
	for (pugi::xml_node obj = objectNodes.first_child(); obj; obj = obj.next_sibling())
	{
    Action* action = new Action();
    std::string name = obj.child_value("Name");
    std::string state = obj.child_value("State");

    if (name == "" || state == "")
      goto cleanup;

    action->SetName(name);
    action->SetAction(AABSEngine::Core::Singleton<StateManager>::Instance()->GetState(state));
    if (action == NULL)
      goto cleanup;

    pugi::xml_node localnode;
    localnode = obj.child("LocalNeedModifiers");
    if (localnode.name() != "")
    {
      for (pugi::xml_node localobj = localnode.first_child(); localobj; localobj = localobj.next_sibling())
      {
        std::string need = localobj.child_value("Need");
        std::string mod = localobj.child_value("Modifier");
        if (need == "" || mod == "")
          continue;
        int intmod = atof(mod.c_str());
        /* ~~~ TODO check success */
        action->AddLocalNeedModifier(need, intmod);
      }
    }
    localnode = obj.child("TargetNeedModifiers");
    if (localnode.name() != "")
    {
      for (pugi::xml_node localobj = localnode.first_child(); localobj; localobj = localobj.next_sibling())
      {
        std::string need = localobj.child_value("Need");
        std::string mod = localobj.child_value("Modifier");
        if (need == "" || mod == "")
          continue;
        int intmod = atof(mod.c_str());
        /* ~~~ TODO check success */
        action->AddLocalNeedModifier(need, intmod);
      }
    }
    localnode = obj.child("LocalEmotionModifiers");
    if (localnode.name() != "")
    {
      for (pugi::xml_node localobj = localnode.first_child(); localobj; localobj = localobj.next_sibling())
      {
        std::string name = localobj.child_value("Emotion");
		//std::cout<<name<<std::endl;
		Emotion emotion;
		emotion.percentage = localobj.child("Modifier").attribute("val").as_float();
		emotion.duration = localobj.child("Duration").attribute("val").as_float();
		emotion.colour.r = localobj.child("Colour").attribute("r").as_float();
		emotion.colour.g = localobj.child("Colour").attribute("g").as_float();
		emotion.colour.b = localobj.child("Colour").attribute("b").as_float();
		emotion.colour.a = localobj.child("Colour").attribute("a").as_float();

		if (name == "")
          continue;
        /* ~~~ TODO check success */
        action->AddLocalEmotionModifier(name, emotion);
      }
    }
    localnode = obj.child("TargetEmotionModifiers");
    if (localnode.name() != "")
    {
      for (pugi::xml_node localobj = localnode.first_child(); localobj; localobj = localobj.next_sibling())
      {
        std::string name = localobj.child_value("Emotion");
		Emotion emotion;
		emotion.percentage = localobj.child("Modifier").attribute("val").as_float();
		emotion.duration = localobj.child("Duration").attribute("val").as_float();
		emotion.colour.r = localobj.child("Colour").attribute("r").as_float();
		emotion.colour.g = localobj.child("Colour").attribute("g").as_float();
		emotion.colour.b = localobj.child("Colour").attribute("b").as_float();
		emotion.colour.a = localobj.child("Colour").attribute("a").as_float();

		if (name == "")
          continue;
        /* ~~~ TODO check success */
        action->AddTargetEmotionModifier(name, emotion);
      }
    }
    m_actions[action->GetName()] = action;
    continue;
cleanup:
    delete action;
	}

  return success;
}

Action* ActionManager::GetAction(std::string name)
{
  if (m_actions.count(name) > 0)
    return m_actions[name];
  return NULL;
}