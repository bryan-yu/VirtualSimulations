#include "StdAfx.h"
#include "PenetrationResolver.h"
#include "Object.h"
#include "Manifold.h"
#include <limits>


AABSEngine::Physics::PResolver::PResolver() : m_contactQ(m_contacts)
{
	m_contactQ.p_greaterComparator = Sort;
}

void AABSEngine::Physics::PResolver::AddCollision(AABSEngine::Core::GameObject* o1, AABSEngine::Core::GameObject* o2,
	AABSEngine::Core::Vector3 nB, Decimal pB, const AABSEngine::Core::Point3& worldOnA, const AABSEngine::Core::Point3& worldOnB)
{
	Manifold* mf = new Manifold(o1,o2,nB,pB,worldOnA,worldOnB);
	m_contacts.push_back(mf);
}


AABSEngine::Physics::PResolver::~PResolver()
{
	ClearCollisions();
}

bool AABSEngine::Physics::PResolver::Sort(Manifold* mf1, Manifold* mf2)
{
	return mf1->m_pB < mf2->m_pB;
}


void AABSEngine::Physics::PResolver::ApplyLinearChange(Manifold* mf)
{
	Decimal modifier = 1.0;

	//get inverse masses
	Decimal invMass_a = mf->m_ob[0]->GetPhysicsObject()->GetInverseMass();
	Decimal invMass_b = mf->m_ob[1]->GetPhysicsObject()->GetInverseMass();
	
	//find sum of inverse masses
	Decimal invSumOfInverseMass = (invMass_a + invMass_b);
	invSumOfInverseMass = abs(invSumOfInverseMass) > 0 ? (1.0 / invSumOfInverseMass) : 0;

	//set and schedule for world linear movement
	mf->m_linear[0] = (mf->m_nB * mf->m_pB * invMass_a * invSumOfInverseMass) * -1.0;
	mf->m_linear[1] = mf->m_nB * mf->m_pB * invMass_b * invSumOfInverseMass;

	//if kinematic
	if(mf->m_ob[0]->GetPhysicsObject()->IsKinematic() == false)
	{
		mf->m_ob[0]->GetPhysicsObject()->SetWorldPosition(mf->m_ob[0]->GetPhysicsObject()->GetWorldPosition() + mf->m_linear[0]);
		mf->m_worldCP[0] = mf->m_worldCP[0] + mf->m_linear[0];
	}

	//if kinematic
	if(mf->m_ob[1]->GetPhysicsObject()->IsKinematic() == false)
	{
		mf->m_ob[1]->GetPhysicsObject()->SetWorldPosition(mf->m_ob[1]->GetPhysicsObject()->GetWorldPosition() + mf->m_linear[1]);
		mf->m_worldCP[1] = mf->m_worldCP[1] + mf->m_linear[1];
	}
}

void AABSEngine::Physics::PResolver::ApplyPenetrationChange(Manifold* mf)
{
	for(int contactNumber=0; contactNumber<m_contacts.size(); contactNumber++)
	{
		//contact gameobjects should be in sync with objects a and b
		for(int objNumber = 0; objNumber < 2; objNumber++)
		{
			if(m_contacts[contactNumber]->m_ob[0] == mf->m_ob[objNumber])
			{
				Decimal moveScalar = mf->m_linear[objNumber].dotProduct(m_contacts[contactNumber]->m_nB);

				m_contacts[contactNumber]->m_pB += moveScalar; //update new penetration values

				m_contacts[contactNumber]->m_worldCP[0] = m_contacts[contactNumber]->m_worldCP[0] + mf->m_linear[objNumber].normalised() * moveScalar;

				m_contactQ.UpdateAt(contactNumber); //reshuffle contacts based on new penetrations
			}
			else if(m_contacts[contactNumber]->m_ob[1] == mf->m_ob[objNumber])
			{
				Decimal moveScalar = mf->m_linear[objNumber].dotProduct(m_contacts[contactNumber]->m_nB);

				m_contacts[contactNumber]->m_pB -= moveScalar; //update new penetration values
		
				m_contacts[contactNumber]->m_worldCP[1] = m_contacts[contactNumber]->m_worldCP[1] + mf->m_linear[objNumber].normalised() * moveScalar;

				m_contactQ.UpdateAt(contactNumber); //reshuffle contacts based on new penetrations
			}
		}//end for
	}//end for
}

void AABSEngine::Physics::PResolver::FirstPass()
{
	for(int i=0; i<m_contacts.size(); i++)
	{
		if(m_contacts[i]->m_pB < 0.0)
		{
			ApplyLinearChange(m_contacts[i]);
			ApplyPenetrationChange(m_contacts[i]);
		}
	}
}

void AABSEngine::Physics::PResolver::ResolveCollisions(int reiterations)
{
	int curIterations=0;

	FirstPass();
	
	while(curIterations != reiterations)
	{
		int index = m_contactQ.PeekIndex();

		if(index != PQ_INVALID_INDEX)
		{
			Manifold* mf = m_contacts[index];

			if(mf->m_pB < 0.0)
			{
				ApplyLinearChange(mf);			
				ApplyPenetrationChange(mf);
			}
			else
			{		
				return; //early exit when we have circulated all penetration depths < 0.0
			}
		}
		else return;

		++curIterations;
	}
}

void AABSEngine::Physics::PResolver::ClearCollisions()
{
	std::vector<Manifold*>::iterator itr = m_contacts.begin();

	while(itr != m_contacts.end())
	{
		delete *itr;
		itr = m_contacts.erase(itr);
	}
}