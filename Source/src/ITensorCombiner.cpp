#include "StdAfx.h"
#include "ITensorCombiner.h"


void AABSEngine::Utility::ITensorCombiner::AddData(AABSEngine::Core::Matrix3& iTensor, AABSEngine::Core::Point3& partCOG, Decimal mass)
{
	m_iTensors.push_back(iTensor);
	m_partCOG.push_back(partCOG);
	m_masses.push_back(mass);
}

void AABSEngine::Utility::ITensorCombiner::SetFinalCOG(const AABSEngine::Core::Point3& cog)
{
	m_finalCOG = cog;
}

void AABSEngine::Utility::ITensorCombiner::ClearITensors()
{
	m_iTensors.clear();
	m_partCOG.clear();
	m_masses.clear();
	m_finalCOG.xyz(0,0,0);
}

void AABSEngine::Utility::ITensorCombiner::CombineITensors()
{
	CalculateCombinedCOG();

	int size = m_iTensors.size(); 

	AABSEngine::Core::Vector3 sumOfI(0,0,0);

	for(int i=0; i<size; i++)
	{
		AABSEngine::Core::Vector3 vSqr;

		Decimal vx = m_partCOG[i].X() - m_finalCOG.X();
		Decimal vy = m_partCOG[i].Y() - m_finalCOG.Y();
		Decimal vz = m_partCOG[i].Z() - m_finalCOG.Z();

		vSqr[0] = vx * vx;
		vSqr[1] = vy * vy;
		vSqr[2] = vz * vz;

		Decimal iX = m_iTensors[i][0][0] + m_masses[i] * (vSqr.Y() + vSqr.Z());
		Decimal iY = m_iTensors[i][1][1] + m_masses[i] * (vSqr.X() + vSqr.Z());
		Decimal iZ = m_iTensors[i][2][2] + m_masses[i] * (vSqr.X() + vSqr.Y());
	
		sumOfI[0] += iX;
		sumOfI[1] += iY;
		sumOfI[2] += iZ;
	}

	m_finalITensor.SetInertiaTensor(sumOfI.X(), sumOfI.Y(), sumOfI.Z(), 0, 0, 0);
}

void AABSEngine::Utility::ITensorCombiner::CalculateCombinedCOG()
{
	//initialize variables
	Core::Vector3 totalCOG(0,0,0);
	for(int i=0; i<m_partCOG.size(); i++)
	{
		//convert the position to vector
		Core::Vector3 temp(m_partCOG[i].X(), m_partCOG[i].Y(), m_partCOG[i].Z());
		totalCOG += temp;
	}

	//work with vector3
	//Core::Vector3 finalCOG = totalCOG / CalculateTotalMass();
	Core::Vector3 finalCOG = totalCOG / m_partCOG.size();

	//convert vector3 to point3
	m_finalCOG.xyz(finalCOG.X(), finalCOG.Y(), finalCOG.Z());
}

float AABSEngine::Utility::ITensorCombiner::CalculateTotalMass()
{
	float totalMass = 0.0f;
	for(int i=0; i<m_masses.size(); i++)
	{
		//convert the position to vector
		totalMass += m_masses[i];
	}

	return totalMass;
}