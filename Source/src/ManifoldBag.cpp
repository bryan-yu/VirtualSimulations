#include "StdAfx.h"
#include "ManifoldBag.h"
#include "Manifold.h"
#include "Vector3.h"
#include "Point3.h"
#include "Object.h"

AABSEngine::Physics::Manifold* AABSEngine::Physics::ManifoldBag::operator[](int index)
{
	return m_bag1[index];
}

const AABSEngine::Physics::Manifold* AABSEngine::Physics::ManifoldBag::operator[](int index)const
{
	return m_bag1[index];
}

AABSEngine::Physics::ManifoldBag::~ManifoldBag()
{
	Empty();
}

AABSEngine::Physics::ManifoldBag::ManifoldBag(){}

void AABSEngine::Physics::ManifoldBag::Empty()
{
	//remove all items in bag
	MFContainer::iterator mfItr = m_bag1.begin();

	while(mfItr != m_bag1.end())
	{
		delete *mfItr;
		mfItr = m_bag1.erase(mfItr);
	}
}

void AABSEngine::Physics::ManifoldBag::Put(AABSEngine::Core::GameObject* o1, AABSEngine::Core::GameObject* o2, AABSEngine::Core::Vector3 nB, Decimal pB, 
			const AABSEngine::Core::Point3& worldOnA, const AABSEngine::Core::Point3& worldOnB)
{
	//put into manifold bag, first check if it exists, if found, then check if new penetration is greater
	MFContainer::iterator mfItr = FindExisting(o1,o2);

	if(mfItr != m_bag1.end())
	{
		if(abs((*mfItr)->m_pB) < abs(pB))
		{
			(*mfItr)->m_worldCP[0] = worldOnA;
			(*mfItr)->m_worldCP[1] = worldOnB;

			(*mfItr)->m_nB = nB;
			(*mfItr)->m_pB = pB;
		}
	}
	else
	{
		//create new manifold and put into bag
		Manifold* mf= new Manifold(o1,o2,nB,pB,worldOnA,worldOnB);
		
		if(mf)
		{
			m_bag1.push_back(mf);
		}
	}
}

bool AABSEngine::Physics::ManifoldBag::Discard(AABSEngine::Core::GameObject* o1, AABSEngine::Core::GameObject* o2)
{
	//find existing, if found, then delete manifold and remove from bag

	MFContainer::iterator mfItr = FindExisting(o1,o2);

	if(mfItr != m_bag1.end())
	{
		delete *mfItr;

		m_bag1.erase(mfItr);

		return true;
	}
	return false;
}

AABSEngine::Physics::ManifoldBag::MFContainer::iterator AABSEngine::Physics::ManifoldBag::FindExisting(AABSEngine::Core::GameObject* o1, AABSEngine::Core::GameObject* o2)
{
	//find existing manifold in which the game object order stored in the manifold matches the parameters
	MFContainer::iterator itr = m_bag1.begin();

	while(itr != m_bag1.end())
	{
		if( (o1->ID() == (*itr)->m_ob[0]->ID()) && 
			(o2->ID() == (*itr)->m_ob[1]->ID()) ) 
		{
			return itr;
		}
	
		++itr;
	}
	return m_bag1.end();
}