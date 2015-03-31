#include "StdAfx.h"
#include"TraitManager.h"

using namespace AABSEngine::AI;

TraitManager::TraitManager()
{

}

bool TraitManager::Initialise()
{
bool success = true;
 
  pugi::xml_document xDoc;
	if(!xDoc.load_file("../resources/scripts/Traits.xml"))
	{
		return false;
	}

	pugi::xml_node objectNodes = xDoc.child("Traits");
	for (pugi::xml_node obj = objectNodes.first_child(); obj; obj = obj.next_sibling())
	{
    TraitDefinition def;
    std::string name = obj.attribute("Name").value();
    std::string need = obj.attribute("Need").value();
    float modifier = abs(atof(obj.attribute("Multiplier").value()));
    modifier = modifier > 2.0 ? 2.0 : modifier; 
    modifier = modifier < 0 ? 0.0 : modifier;// clamp to 0..2.0 range - gives an effective range of 0..2*needmaximum
    modifier = 2.0 - modifier;                       // invert around midpoint. For clarity of expression trait in script uses numbers > to effect
                                                     // more frequent update of need. Actual implementation requires < 1. TODO check if this is clear

    if (name == "" || need == "")
      return false;

    if (m_traitDefinitions.count(def.name) > 0)
      return false;

    def.name = name;
    def.need = need;
    def.bias = modifier;

    m_traitDefinitions[def.name] = def;
	}

  return success;
}

void TraitManager::AddTraitDefinition(TraitDefinition def)
{
  if (m_traitDefinitions.count(def.name) < 1)
    m_traitDefinitions[def.name] = def;
}

TraitDefinition TraitManager::GetTraitDefinition(std::string name)
{
  if (m_traitDefinitions.count(name) > 0)
    return m_traitDefinitions[name];
  return TraitDefinition();
}

