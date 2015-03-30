#include "StdAfx.h"
#include "NeedComposition.h"
#include "Need.h"

#include "Singleton.h"
#include "NeedManager.h"

bool AABSEngine::AI::OrderByNeed::operator()(const Need* n1, const Need* n2)
{
	return n1->GetBase() > n2->GetBase();
}

AABSEngine::AI::NeedComposition::~NeedComposition()
{
	Clear();
}

const AABSEngine::AI::Need* AABSEngine::AI::NeedComposition::Access(std::string name)const
{
	AABSEngine::AI::NeedVector::const_iterator itr = m_needs.begin();

	while(itr != m_needs.end())
	{
		if((*itr)->GetName() == name)
		{
			return *itr;
		}
		++itr;
	}
	return 0;
}

AABSEngine::AI::Need* AABSEngine::AI::NeedComposition::Access(std::string name)
{
	AABSEngine::AI::NeedVector::iterator itr = m_needs.begin();

	while(itr != m_needs.end())
	{
		if((*itr)->GetName() == name)
		{
			return *itr;
		}
		++itr;
	}
	return 0;
}

void AABSEngine::AI::NeedComposition::Update(Decimal t)
{
	NeedVector::iterator itr = m_needs.begin();

	while(itr != m_needs.end())
	{
		(*itr)->Evaluate(t);
		
		++itr;
	}
}

void AABSEngine::AI::NeedComposition::Access(PrioritizedNeeds& needs, size_t x)
{
	size_t count = 0;
	NeedVector::const_iterator itr = m_needs.begin();

	while(itr != m_needs.end() && count < x)
	{
		needs.push(*itr);
		
		++count;
		
		++itr;
	}
}

AABSEngine::AI::NeedVector::iterator AABSEngine::AI::NeedComposition::Find(std::string name)
{
	NeedVector::iterator itr = m_needs.begin();

	while(itr != m_needs.end())
	{
		if((*itr)->GetName() == name)
		{
			break;
		}
		++itr;
	}	
	return itr;
}

const AABSEngine::AI::NeedVector::const_iterator AABSEngine::AI::NeedComposition::Find(std::string name)const
{
	NeedVector::const_iterator itr = m_needs.begin();

	while(itr != m_needs.end())
	{
		if((*itr)->GetName() == name)
		{
			break;
		}
		++itr;
	}	
	return itr;
}

bool AABSEngine::AI::NeedComposition::Remove(std::string name)
{
	NeedVector::iterator itr = Find(name);

	if(itr != m_needs.end())
	{
		delete *itr;

		m_needs.erase(itr);

		return true;
	}
	return false;
}

void AABSEngine::AI::NeedComposition::Clear()
{
	NeedVector::iterator itr = m_needs.begin();

	while(itr != m_needs.end())
	{
		Need* need = *itr;

		if(need)
		{
			delete need;
		}

		itr = m_needs.erase(itr);
	}
}

void AABSEngine::AI::NeedComposition::AddNeed(std::string name)
{
  if (this->Find(name) == m_needs.end())
    m_needs.push_back(AABSEngine::Core::Singleton<NeedManager>::Instance()->GetNeed(name));
}