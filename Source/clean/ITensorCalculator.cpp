#include "StdAfx.h"
#include "ITensorCalculator.h"

void AABSEngine::Utility::ITensorCalculator::SetVertices(Vertices& vtx)
{
	m_vertices = vtx;
}

void AABSEngine::Utility::ITensorCalculator::SetBodyMass(Decimal bodyMass)
{
	m_bodyMass = bodyMass;
}

AABSEngine::Core::Matrix3& AABSEngine::Utility::ITensorCalculator::GetBodyITensor() 
{ 
	return m_iTensor;
}

AABSEngine::Core::Point3& AABSEngine::Utility::ITensorCalculator::GetBodyCOM() 
{ 
	return m_centerOfMass;
}

AABSEngine::Core::Vector3& AABSEngine::Utility::ITensorCalculator::GetFirstMomentInertia() 
{ 
	return m_firstMomentInertia;
}

void AABSEngine::Utility::ITensorCalculator::CalculateCOM()
{
	if(m_bodyMass == 0 || m_vertices.size() == 0)
	{ 
		return;
	}

	//get the point mass
	m_pointMass = m_bodyMass / m_vertices.size();
	m_firstMomentInertia.xyz(0,0,0);

	for(int i=0; i<m_vertices.size(); i++)
	{
		m_firstMomentInertia += m_vertices[i] * m_pointMass;
	}

	m_centerOfMass[0] = (Decimal)m_firstMomentInertia.X() / m_bodyMass;
	m_centerOfMass[1] = (Decimal)m_firstMomentInertia.Y() / m_bodyMass;
	m_centerOfMass[2] = (Decimal)m_firstMomentInertia.Z() / m_bodyMass;
}

void AABSEngine::Utility::ITensorCalculator::CalculateITensor()
{
	CalculateCOM();

	Decimal sumDistPtMass2_X = 0, sumDistPtMass2_Y = 0, sumDistPtMass2_Z = 0;

	Decimal prodDistPtMass_XZ = 0, prodDistPtMass_XY = 0, prodDistPtMass_YZ = 0;

	for(int i=0; i<m_vertices.size(); i++)
	{
		Decimal lenX = (m_centerOfMass.X() - m_vertices[i].X());
		Decimal lenY = (m_centerOfMass.Y() - m_vertices[i].Y());
		Decimal lenZ = (m_centerOfMass.Z() - m_vertices[i].Z());

		Decimal lenXSqr = lenX*lenX;
		Decimal lenYSqr = lenY*lenY;
		Decimal lenZSqr = lenZ*lenZ;

		sumDistPtMass2_X += (lenYSqr + lenZSqr) * m_pointMass;
		sumDistPtMass2_Y += (lenXSqr + lenZSqr) * m_pointMass;
		sumDistPtMass2_Z += (lenXSqr + lenYSqr) * m_pointMass;

		prodDistPtMass_XY += lenX * lenY * m_pointMass;
		prodDistPtMass_XZ += lenX * lenZ * m_pointMass;
		prodDistPtMass_YZ += lenY * lenZ * m_pointMass;
	}

	const Decimal oneOver3 = 1/3.0;

	m_iTensor.SetInertiaTensor(sumDistPtMass2_X  * oneOver3, sumDistPtMass2_Y  * oneOver3, sumDistPtMass2_Z  * oneOver3, 
							   prodDistPtMass_XY * oneOver3, prodDistPtMass_XZ * oneOver3, prodDistPtMass_YZ * oneOver3);
		
}

void AABSEngine::Utility::ITensorCalculator::ClearCache()
{
	m_iTensor.Identity();
	m_vertices.clear();

	m_pointMass = 0;
	m_bodyMass = 0;

	m_centerOfMass.xyz(0,0,0);
	m_firstMomentInertia.xyz(0,0,0);
}

AABSEngine::Core::Matrix3 AABSEngine::Utility::ITensorCalculator::CreateSphereITensor(Decimal radius, Decimal objectMass)
{
	AABSEngine::Core::Matrix3 tensor;

	const Decimal twoOver5 = 2/5.0;
	
	Decimal ii = twoOver5 * objectMass * radius * radius;

	tensor.SetInertiaTensor(ii,ii,ii,0,0,0);

	return tensor;
}

AABSEngine::Core::Matrix3 AABSEngine::Utility::ITensorCalculator::CreateElipsoidITensor(Decimal radiusX, Decimal radiusY, Decimal radiusZ, Decimal pointMass)
{
	AABSEngine::Core::Matrix3 tensor;

	const Decimal oneOver5 = 1/5.0;

	Decimal rXSqr = radiusX * radiusX;
	Decimal rYSqr = radiusY * radiusY;
	Decimal rZSqr = radiusZ * radiusZ;

	Decimal xx = oneOver5 * pointMass * (rYSqr + rZSqr);
	Decimal yy = oneOver5 * pointMass * (rXSqr + rZSqr);
	Decimal zz = oneOver5 * pointMass * (rXSqr + rYSqr);

	tensor.SetInertiaTensor(xx,yy,zz,0,0,0);

	return tensor;
}

AABSEngine::Core::Matrix3 AABSEngine::Utility::ITensorCalculator::CreateCylinderITensor(Decimal radius, Decimal height, Decimal objectMass)
{
	AABSEngine::Core::Matrix3 tensor;

	const Decimal oneOver12 = 1/12.0;
	const Decimal oneOver4 = 1/4.0;
	const Decimal oneOver2 = 1/2.0;
	
	Decimal ht2ProdMass = height * height * objectMass;
	Decimal rad2ProdMass = radius * radius * objectMass;

	Decimal xx = (oneOver12 * ht2ProdMass) + (oneOver4 * rad2ProdMass);
	Decimal yy = (oneOver2 * rad2ProdMass);
	Decimal zz = (oneOver12 * ht2ProdMass) + (oneOver4 * rad2ProdMass);

	tensor.SetInertiaTensor(xx,yy,zz,0,0,0);

	return tensor;
}


AABSEngine::Core::Matrix3 AABSEngine::Utility::ITensorCalculator::CreateCuboidITensor(const AABSEngine::Core::Vector3& extent, Decimal objectMass)
{
	AABSEngine::Core::Matrix3 tensor;

	const Decimal oneOver12 = 1/12.0;
	
	Decimal xSqr = extent.X() * extent.X();
	Decimal ySqr = extent.Y() * extent.Y();
	Decimal zSqr = extent.Z() * extent.Z();

	Decimal xx = oneOver12 * objectMass * (ySqr + zSqr);
	Decimal yy = oneOver12 * objectMass * (xSqr + zSqr);
	Decimal zz = oneOver12 * objectMass * (xSqr + ySqr);

	tensor.SetInertiaTensor(xx,yy,zz,0,0,0);

	return tensor;
}
