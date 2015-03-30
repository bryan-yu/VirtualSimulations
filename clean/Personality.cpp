#include "StdAfx.h"
#include "Trait.h"
#include "Personality.h"

const AABSEngine::AI::Trait* AABSEngine::AI::Personality::Access(std::string name)const
{
	std::vector<Trait*>::const_iterator itr = m_traits.begin();

	while(itr != m_traits.end())
	{
		const Trait* trait = *itr;

		if(trait->GetName() == name)
		{
			return trait;
		}
		++itr;
	}
	return 0;
}

AABSEngine::AI::Trait* AABSEngine::AI::Personality::Access(std::string name)
{
	std::vector<Trait*>::iterator itr = m_traits.begin();

	while(itr != m_traits.end())
	{
		Trait* trait = *itr;

		if(trait->GetName() == name)
		{
			return trait;
		}
		++itr;
	}
	return 0;
}

AABSEngine::AI::Trait* AABSEngine::AI::Personality::AccessByNeed(std::string name)
{
  std::vector<Trait*>::iterator itr = m_traits.begin();

	while(itr != m_traits.end())
	{
		Trait* trait = *itr;

		if(trait->GetNeed() == name)
		{
			return trait;
		}
		++itr;
	}
	return NULL;
}

void AABSEngine::AI::Personality::Clear()
{
	std::vector<Trait*>::iterator itr = m_traits.begin();

	while(itr != m_traits.end())
	{
		delete *itr;

		itr = m_traits.erase(itr);
	}
}

bool AABSEngine::AI::Personality::Remove(std::string name)
{
	std::vector<Trait*>::iterator itr = m_traits.begin();

	while(itr != m_traits.end())
	{
		Trait* trait = *itr;

		if(trait->GetName() == name)
		{
			delete trait;

			m_traits.erase(itr);
		
			return true;
		}
		++itr;
	}
	return false;	
}