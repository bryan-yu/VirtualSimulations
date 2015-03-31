#include "StdAfx.h"
#include "Quaternion.h"
#include "Vector3.h"
#include "Matrix3.h"

const AABSEngine::Core::Quaternion AABSEngine::Core::Quaternion::QUAT_X_180 = AABSEngine::Core::Quaternion(0,1,0,0);
const AABSEngine::Core::Quaternion AABSEngine::Core::Quaternion::QUAT_Y_180 = AABSEngine::Core::Quaternion(0,0,1,0);
const AABSEngine::Core::Quaternion AABSEngine::Core::Quaternion::QUAT_Z_180 = AABSEngine::Core::Quaternion(0,0,0,1);

const AABSEngine::Core::Quaternion AABSEngine::Core::Quaternion::QUAT_X_90 = AABSEngine::Core::Quaternion(sqrt(0.5),sqrt(0.5),0,0);
const AABSEngine::Core::Quaternion AABSEngine::Core::Quaternion::QUAT_Y_90 = AABSEngine::Core::Quaternion(sqrt(0.5),0,sqrt(0.5),0);
const AABSEngine::Core::Quaternion AABSEngine::Core::Quaternion:: QUAT_Z_90 = AABSEngine::Core::Quaternion(sqrt(0.5),0,0,sqrt(0.5));

const AABSEngine::Core::Quaternion AABSEngine::Core::Quaternion::IDENTITY = AABSEngine::Core::Quaternion(1,0,0,0);

AABSEngine::Core::Quaternion::Quaternion(Decimal degree, Decimal x, Decimal y, Decimal z)
{
	//WXYZ(degree,x,y,z);
	m_quat.w=degree;
	m_quat.x=x;
	m_quat.y=y;
	m_quat.z=z;
}

void AABSEngine::Core::Quaternion::ExtractTransform(const Matrix3& mat)
{
	m_quat.FromRotationMatrix(mat.Get());
}

AABSEngine::Core::Quaternion::Quaternion(const Ogre::Quaternion &in)
{
	m_quat = in;
}

Decimal AABSEngine::Core::Quaternion::Dot(const Quaternion& other)const
{
	return m_quat.Dot(other.m_quat);
}

Decimal AABSEngine::Core::Quaternion::Magnitude()const
{
	return sqrt(m_quat.w * m_quat.w + 
		m_quat.x * m_quat.x +
		m_quat.y * m_quat.y +
		m_quat.z * m_quat.z);
}


void AABSEngine::Core::Quaternion::AddScaledVector(const Vector3& v, const Decimal t)
{
	//quat + ((a*t/2)*omega)*quat

	Quaternion qtemp(v * t, 0);

	qtemp *= *this;

	m_quat.w += qtemp.W() * 0.5;
	m_quat.x += qtemp.X() * 0.5;
	m_quat.y += qtemp.Y() * 0.5;
	m_quat.z += qtemp.Z() * 0.5;
}

AABSEngine::Core::Quaternion AABSEngine::Core::Quaternion::operator*(Decimal t)const
{
	return Quaternion(m_quat * t);
}

AABSEngine::Core::Quaternion& AABSEngine::Core::Quaternion::operator*=(Decimal t)
{
	m_quat = m_quat * t;
	return *this;
}

void AABSEngine::Core::Quaternion::Normalise()
{
	m_quat.normalise();
}

void AABSEngine::Core::Quaternion::Invert()
{
	m_quat = m_quat.Inverse();
}

void AABSEngine::Core::Quaternion::Conjugate()
{
	m_quat.x = -m_quat.x;
	m_quat.y = -m_quat.y;
	m_quat.z = -m_quat.z;
}

void AABSEngine::Core::Quaternion::WXYZ(Decimal degree, Decimal x, Decimal y, Decimal z)
{
	m_quat.FromAngleAxis(Ogre::Degree(degree), Ogre::Vector3(x,y,z));
}

void AABSEngine::Core::Quaternion::WXYZ(const Vector3& axis, Decimal degree)
{
	m_quat.FromAngleAxis(Ogre::Degree(degree), Ogre::Vector3(axis.X(),axis.Y(),axis.Z()));
}

AABSEngine::Core::Quaternion AABSEngine::Core::Quaternion::Difference(const Quaternion& other)const
{
	//ab = c
	//a` * a * b = a` * c
	//b = ` * c
	Quaternion inv;
	inv.Get() = m_quat;
	inv.Invert();

	return inv * other;
}

void AABSEngine::Core::Quaternion::Identity()
{
	m_quat = Ogre::Quaternion::IDENTITY;
}

AABSEngine::Core::Quaternion::Quaternion()
{
	Identity();
}

AABSEngine::Core::Quaternion AABSEngine::Core::Quaternion::operator*(const Quaternion& other)const
{
	Quaternion out;
	out.m_quat = m_quat * other.m_quat;

	return out;
}

AABSEngine::Core::Vector3 AABSEngine::Core::Quaternion::operator*(const Vector3& v)const
{
	Vector3 out;
	return out; 
}

AABSEngine::Core::Quaternion& AABSEngine::Core::Quaternion::operator*=(const Quaternion& other)
{
	if(this != &other)
	{
		m_quat = m_quat * other.m_quat;
	}

	return *this;
}

AABSEngine::Core::Quaternion::Quaternion(const Quaternion& other)
{
	m_quat = other.m_quat;
}
			
AABSEngine::Core::Quaternion& AABSEngine::Core::Quaternion::operator=(const Quaternion& other)
{
	if(this != &other)
	{
		m_quat = other.m_quat;
	}
	return *this;
}

AABSEngine::Core::Quaternion::Quaternion(const Vector3& axis, Decimal degree)
{
	m_quat.w = degree * Ogre::Math::PI / 180.0;
	m_quat.x = axis.X();
	m_quat.y = axis.Y();
	m_quat.z = axis.Z();
}

