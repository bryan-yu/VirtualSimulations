#include "StdAfx.h"
#include "Manifold.h"
#include "Object.h"

AABSEngine::Physics::Manifold::Manifold(AABSEngine::Core::GameObject* o1, AABSEngine::Core::GameObject* o2,
	const AABSEngine::Core::Vector3& nB, Decimal pB, const AABSEngine::Core::Point3& worldOnA, const AABSEngine::Core::Point3& worldOnB)
{
	m_ob[0] = o1;
	m_ob[1] = o2;

	m_worldCP[0] = worldOnA;
	m_worldCP[1] = worldOnB;

	m_nB = nB;
	m_pB = pB;

	m_linear[0].xyz(0,0,0);
	m_linear[1].xyz(0,0,0);
}

AABSEngine::Physics::Manifold::Manifold()
{
	for(int i=0; i<2; i++)
	{
		m_ob[i] = 0;
		m_linear[i].xyz(0,0,0);
	}
	m_pB = EPSILON;
	m_nB.xyz(0,0,0);
}
