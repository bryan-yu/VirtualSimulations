#include "StdAfx.h"
#include "NeedManager.h"

using namespace AABSEngine::AI;

NeedManager::NeedManager()
{

}

bool NeedManager::Initialise()
{
  bool success = true;
 
  pugi::xml_document xDoc;
	if(!xDoc.load_file("../resources/scripts/Needs.xml"))
	{
		return false;
	}

  NeedDefinition need;

	pugi::xml_node objectNodes = xDoc.child("Needs");
	for (pugi::xml_node obj = objectNodes.first_child(); obj; obj = obj.next_sibling())
	{
    std::string name = obj.child_value("Name");
    if (name == "")
      continue;

    int max = atof(obj.child_value("Max")); // ~~~ TODO error checking
    int min = atof(obj.child_value("Min")); // ~~~ TODO error checking
    int base = atof(obj.child_value("Base")); // ~~~ TODO error checking
    if (max <= min)
      continue;
    if (base < min || base > max)
      continue;

    std::string evaluator = obj.child("Evaluator").attribute("Type").value();
    int rate = atoi(obj.child("Evaluator").attribute("Rate").value());
    std::string affordance = obj.child_value("Affordance");
    int lowwater = atoi(obj.child_value("LowWaterMark"));
    int highwater = atoi(obj.child_value("HighWaterMark"));
    if (affordance == "")
      continue;

    need.name = name;
    need.max = max;
    need.min = min;
    need.base = base;
    need.evaluatorFunction = evaluator;
    need.evaluatorFunctionParam = rate;
    need.affordance = affordance;
    need.lowWaterMark = lowwater;
    need.highWaterMark = highwater;
    
    if (m_needDefinitions.count(need.name) < 1)
      m_needDefinitions[need.name] = need;
	}

  return success;
}

void NeedManager::AddNeed(NeedDefinition needdef)
{
  if (m_needDefinitions.count(needdef.name) < 1)
    m_needDefinitions[needdef.name] = needdef;
  return;
}

Need* NeedManager::GetNeed(std::string name)
{
  if (m_needDefinitions.count(name) > 0)
    return new Need(m_needDefinitions[name]);
  return NULL;
}