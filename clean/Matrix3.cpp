#include "StdAfx.h"
#include "Matrix3.h"
#include "Quaternion.h"

#include <cassert>


AABSEngine::Core::Matrix3::Matrix3()
{
	Identity();
}

void AABSEngine::Core::Matrix3::ExtractQuaternion(AABSEngine::Core::Quaternion& quat)
{
	quat.Get().FromRotationMatrix(m_mat);
}

AABSEngine::Core::Matrix3 AABSEngine::Core::Matrix3::operator*(const Decimal s)const
{
	Matrix3 out;
	
	out.Get() = m_mat * s;

	return out;
}

AABSEngine::Core::Matrix3 AABSEngine::Core::Matrix3::operator*=(const Decimal s)
{
	m_mat = m_mat * s;

	return *this;
}

void AABSEngine::Core::Matrix3::ExtractTransform(const Quaternion& quat)
{
	Quaternion qtemp = quat;
	qtemp.Normalise();

	float qX2 = 2 * qtemp.X() * qtemp.X();
	float qY2 = 2 * qtemp.Y() * qtemp.Y();
	float qZ2 = 2 * qtemp.Z() * qtemp.Z();

	float qXY2 = 2 * qtemp.X() * qtemp.Y();
	float qXZ2 = 2 * qtemp.X() * qtemp.Z();
	float qYZ2 = 2 * qtemp.Y() * qtemp.Z();

	float qWX2 = 2 * qtemp.W() * qtemp.X();
	float qWY2 = 2 * qtemp.W() * qtemp.Y();
	float qWZ2 = 2 * qtemp.W() * qtemp.Z();

	m_mat[0][0] = 1 - qY2 - qZ2;
	m_mat[0][1] = qXY2 - qWZ2;
	m_mat[0][2] = qXZ2 + qWY2;
	
	m_mat[1][0] = qXY2 + qWZ2;
	m_mat[1][1] = 1 - qX2 - qZ2;
	m_mat[1][2] = qYZ2 - qWX2;
	
	m_mat[2][0] = qXZ2 - qWY2;
	m_mat[2][1] = qYZ2 + qWX2;
	m_mat[2][2] = 1 - qX2 - qY2;
}


AABSEngine::Core::Matrix3::Matrix3(const Matrix3& mat)
{
	m_mat = mat.m_mat;
}

void AABSEngine::Core::Matrix3::SetInertiaTensor(Decimal Ixx, Decimal Iyy, Decimal Izz, Decimal Ixy, Decimal Ixz, Decimal Iyz)
{
	m_mat[0][0] =  Ixx;	 m_mat[0][1] = -Ixy;  m_mat[0][2] = -Ixz;
	m_mat[1][0] = -Ixy;	 m_mat[1][1] =  Iyy;  m_mat[1][2] = -Iyz;
	m_mat[2][0] = -Ixz;  m_mat[2][1] = -Iyz;  m_mat[2][2] =  Izz;
}

AABSEngine::Core::Matrix3& AABSEngine::Core::Matrix3::operator=(const Matrix3& mat)
{
	if(this != &mat)
	{
		m_mat = mat.m_mat;
	}
	return *this;
}

AABSEngine::Core::Matrix3 AABSEngine::Core::Matrix3::Inverse()const
{
	Matrix3 out;
	out.Get() = m_mat.Inverse(EPSILON);
	return out;
}

void AABSEngine::Core::Matrix3::Inversed()
{
	m_mat = m_mat.Inverse(EPSILON);
}

void AABSEngine::Core::Matrix3::Swap(Matrix3& other)
{
	m_mat.swap(other.m_mat);
}

bool AABSEngine::Core::Matrix3::operator==(const Matrix3& mat)const
{
	return  Ogre::Math::Abs(m_mat[0][0] - mat[0][0]) <= EPSILON && //close to 1
		    Ogre::Math::Abs(m_mat[1][0] - mat[1][0]) <= EPSILON && //close to 0
			Ogre::Math::Abs(m_mat[2][0] - mat[2][0]) <= EPSILON && //close to 0
			Ogre::Math::Abs(m_mat[0][1] - mat[0][1]) <= EPSILON && //close to 0 
			Ogre::Math::Abs(m_mat[1][1] - mat[1][1]) <= EPSILON && //close to 1
			Ogre::Math::Abs(m_mat[2][1] - mat[2][1]) <= EPSILON && //close to 0
			Ogre::Math::Abs(m_mat[0][2] - mat[0][2]) <= EPSILON && //close to 0
			Ogre::Math::Abs(m_mat[1][2] - mat[1][2]) <= EPSILON && //close to 0
			Ogre::Math::Abs(m_mat[2][2] - mat[2][2]) <= EPSILON;	  //close to 1	
}

AABSEngine::Core::Matrix3 AABSEngine::Core::Matrix3::Transpose()const
{
	Matrix3 mtx;

	mtx.m_mat = this->m_mat;
	mtx.m_mat.Transpose();

	return mtx;
}


void AABSEngine::Core::Matrix3::Transposed()
{
	m_mat = m_mat.Transpose();
}


void AABSEngine::Core::Matrix3::Identity()
{
	m_mat = Ogre::Matrix3::IDENTITY;
}

const Decimal* AABSEngine::Core::Matrix3::operator[](unsigned int row)const
{
	return m_mat[row];
}

Decimal* AABSEngine::Core::Matrix3::operator[](unsigned int row)
{
	return m_mat[row];
}

void AABSEngine::Core::Matrix3::SetValue(const Vector3& x, const Vector3& y, const Vector3& z) 
{
	m_mat.SetColumn(X,x.get());
	m_mat.SetColumn(Y,y.get());
	m_mat.SetColumn(Z,z.get());
}

		
void AABSEngine::Core::Matrix3::SetEuler(Axis axis, Decimal degree)
{
	Decimal radian = Ogre::Degree(degree).valueRadians();
	Decimal cosRad = Ogre::Math::Cos(radian);
	Decimal sinRad = Ogre::Math::Sin(radian);

	switch(axis)
	{
		case X:
		{
			m_mat[0][0] = 1.0; m_mat[0][1] = 0;      m_mat[0][2] = 0;
			m_mat[1][0] = 0;   m_mat[1][1] = cosRad; m_mat[1][2] = -sinRad;
			m_mat[2][0] = 0;   m_mat[2][1] = sinRad; m_mat[2][2] = cosRad;
		}
		break;

		case Y:
		{
			m_mat[0][0] = cosRad;  m_mat[0][1] = 0;   m_mat[0][2] = sinRad;
			m_mat[1][0] = 0;       m_mat[1][1] = 1.0; m_mat[1][2] = 0;
			m_mat[2][0] = -sinRad; m_mat[2][1] = 0;   m_mat[2][2] = cosRad;
		}
		break;

		case Z:
		{
			m_mat[0][0] = cosRad; m_mat[0][1] = -sinRad; m_mat[0][2] = 0;
			m_mat[1][0] = sinRad; m_mat[1][1] = cosRad;  m_mat[1][2] = 0;
			m_mat[2][0] = 0;      m_mat[2][1] = 0;       m_mat[2][2] = 1.0;
		}
		break;
	}
}

void AABSEngine::Core::Matrix3::RotateEuler(Axis axis, Decimal degree)
{
	Matrix3 temp;
	temp.SetEuler(axis,degree);

	m_mat = m_mat * temp.m_mat;
}

void AABSEngine::Core::Matrix3::SetEuler(Concatenation order, Decimal yaw, Decimal pitch, Decimal roll)
{
	Ogre::Degree deg_x(pitch), deg_y(yaw), deg_z(roll);

	switch(order)
	{
		case XYZ: m_mat.FromEulerAnglesXYZ(deg_y,deg_x,deg_z); break;
		case XZY: m_mat.FromEulerAnglesXZY(deg_y,deg_x,deg_z); break;

		case YXZ: m_mat.FromEulerAnglesYXZ(deg_y,deg_x,deg_z); break;
		case YZX: m_mat.FromEulerAnglesYZX(deg_y,deg_x,deg_z); break;

		case ZXY: m_mat.FromEulerAnglesZXY(deg_y,deg_x,deg_z); break;
		case ZYX: m_mat.FromEulerAnglesZYX(deg_y,deg_x,deg_z); break;
	}
}

void AABSEngine::Core::Matrix3::RotateEuler(Concatenation order, Decimal yaw, Decimal pitch, Decimal roll)
{
	Matrix3 temp;

	temp.SetEuler(order, yaw, pitch, roll);

	m_mat = m_mat * temp.m_mat;
}

void AABSEngine::Core::Matrix3::SetByAxisAngle(const Vector3& axis, Decimal degree)
{
	m_mat.FromAngleAxis(axis.get(),Ogre::Degree(degree));
}

void AABSEngine::Core::Matrix3::RotateByAxisAngle(const Vector3& axis, Decimal degree)
{
	Matrix3 temp;

	temp.SetByAxisAngle(axis,degree);

	m_mat = m_mat * temp.m_mat;
}


AABSEngine::Core::Matrix3 AABSEngine::Core::Matrix3::operator*(const Matrix3& mtx)const
{
	Matrix3 out;
	
	out.Get() = m_mat * mtx.m_mat;

	return out;
}

AABSEngine::Core::Matrix3& AABSEngine::Core::Matrix3::operator*=(const Matrix3& mtx)
{
	m_mat = m_mat * mtx.m_mat;

	return *this;
}

AABSEngine::Core::Vector3 AABSEngine::Core::Matrix3::operator*(const Vector3& v)const
{
	return ObjectToWorld(v);
}

AABSEngine::Core::Point3 AABSEngine::Core::Matrix3::operator*(const Point3& p)const
{
	return ObjectToWorld(p);
}

AABSEngine::Core::Vector3 AABSEngine::Core::Matrix3::ObjectToWorld(const Vector3& v)const
{
	Vector3 out;

	out[0] = v.X() * m_mat[0][0] + v.Y() * m_mat[0][1] + v.Z() * m_mat[0][2];
	out[1] = v.X() * m_mat[1][0] + v.Y() * m_mat[1][1] + v.Z() * m_mat[1][2];
	out[2] = v.X() * m_mat[2][0] + v.Y() * m_mat[2][1] + v.Z() * m_mat[2][2];

	return out;
}

AABSEngine::Core::Vector3 AABSEngine::Core::Matrix3::WorldToObject(const Vector3& v)const
{
	Vector3 out;

	out[0] = v.X() * m_mat[0][0] + v.Y() * m_mat[1][0] + v.Z() * m_mat[2][0];
	out[1] = v.X() * m_mat[0][1] + v.Y() * m_mat[1][1] + v.Z() * m_mat[2][1];
	out[2] = v.X() * m_mat[0][2] + v.Y() * m_mat[1][2] + v.Z() * m_mat[2][2];
	
	return out;	
}


AABSEngine::Core::Point3 AABSEngine::Core::Matrix3::ObjectToWorld(const Point3& p)const
{
	Point3 out;

	out[0] = p.X() * m_mat[0][0] + p.Y() * m_mat[0][1] + p.Z() * m_mat[0][2];
	out[1] = p.X() * m_mat[1][0] + p.Y() * m_mat[1][1] + p.Z() * m_mat[1][2];
	out[2] = p.X() * m_mat[2][0] + p.Y() * m_mat[2][1] + p.Z() * m_mat[2][2];

	return out;		
}

AABSEngine::Core::Point3 AABSEngine::Core::Matrix3::WorldToObject(const Point3& p)const
{
	Point3 out;

	out[0] = p.X() * m_mat[0][0] + p.Y() * m_mat[1][0] + p.Z() * m_mat[2][0];
	out[1] = p.X() * m_mat[0][1] + p.Y() * m_mat[1][1] + p.Z() * m_mat[2][1];
	out[2] = p.X() * m_mat[0][2] + p.Y() * m_mat[1][2] + p.Z() * m_mat[2][2];

	return out;		
}