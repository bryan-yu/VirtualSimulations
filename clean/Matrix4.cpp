#include "StdAfx.h"
#include "Matrix4.h"
#include "Matrix3.h"

#include "Quaternion.h"

AABSEngine::Core::Matrix4::Matrix4()
{
	Identity();
}

AABSEngine::Core::Matrix4::Matrix4(const Matrix4& mat)
{
	m_mat = mat.m_mat;
}

void AABSEngine::Core::Matrix4::ExtractQuaternion(AABSEngine::Core::Quaternion& quat)
{
	Decimal w,x,y,z;

	Decimal largest = -std::numeric_limits<Decimal>::max();

	Decimal fourW2 = m_mat[0][0] + m_mat[1][1] + m_mat[2][2];
	Decimal fourX2 = m_mat[0][0] - m_mat[1][1] - m_mat[2][2];
	Decimal fourY2 = -m_mat[0][0] + m_mat[1][1] - m_mat[2][2];
	Decimal fourZ2 = -m_mat[0][0] - m_mat[1][1] + m_mat[2][2];         

	largest = std::max(fourW2, largest);
	largest = std::max(fourX2, largest);
	largest = std::max(fourY2, largest);
	largest = std::max(fourZ2, largest);

	if(largest == fourW2)
	{
		w = sqrt(largest + 1) * 0.5;
		Decimal inv4MultW = 1.0 / (4.0 * w);

		x = (m_mat[2][1] - m_mat[1][2]) * inv4MultW;
		y = (m_mat[0][2] - m_mat[2][0]) * inv4MultW;
		z = (m_mat[1][0] - m_mat[0][1]) * inv4MultW;
	}
	else if(largest == fourX2)
	{
		x = sqrt(largest + 1) * 0.5;
		Decimal inv4MultX = 1.0 / (4.0 * x);

		w = (m_mat[2][1] - m_mat[1][2]) * inv4MultX;
		y = (m_mat[1][0] + m_mat[0][1]) * inv4MultX;
		z = (m_mat[0][2] + m_mat[2][0]) * inv4MultX;
	}
	else if(largest == fourY2)
	{
		y = sqrt(largest + 1) * 0.5;
		Decimal inv4MultY = 1.0 / (4.0 * y);

		w = (m_mat[0][2] - m_mat[2][0]) * inv4MultY;
		x = (m_mat[1][0] + m_mat[0][1]) * inv4MultY;
		z = (m_mat[2][1] + m_mat[1][2]) * inv4MultY;
	}
	else
	{
		z = sqrt(largest + 1) * 0.5;
		Decimal inv4MultZ = 1.0 / (4.0 * z);

		w = (m_mat[1][0] - m_mat[0][1]) * inv4MultZ;
		x = (m_mat[0][2] + m_mat[2][0]) * inv4MultZ;
		y = (m_mat[2][1] + m_mat[1][2]) * inv4MultZ;
	}

	quat.WXYZ(Ogre::Radian(w).valueDegrees(),x,y,z);
}

AABSEngine::Core::Matrix4& AABSEngine::Core::Matrix4::operator=(const Matrix4& mat)
{
	if(this != & mat)
	{
		m_mat = mat.m_mat;
	}
	return *this;
}

bool AABSEngine::Core::Matrix4::operator==(const Matrix4& mat)const
{
	return  Ogre::Math::Abs(m_mat[0][0] - mat[0][0]) <= EPSILON && //close to 1
			Ogre::Math::Abs(m_mat[1][0] - mat[1][0]) <= EPSILON && //close to 0
			Ogre::Math::Abs(m_mat[2][0] - mat[2][0]) <= EPSILON && //close to 0
			Ogre::Math::Abs(m_mat[3][0] - mat[3][0]) <= EPSILON &&
			Ogre::Math::Abs(m_mat[0][1] - mat[0][1]) <= EPSILON && //close to 0 
			Ogre::Math::Abs(m_mat[1][1] - mat[1][1]) <= EPSILON && //close to 1
			Ogre::Math::Abs(m_mat[2][1] - mat[2][1]) <= EPSILON && //close to 0
			Ogre::Math::Abs(m_mat[3][1] - mat[3][1]) <= EPSILON &&
			Ogre::Math::Abs(m_mat[0][2] - mat[0][2]) <= EPSILON && //close to 0
			Ogre::Math::Abs(m_mat[1][2] - mat[1][2]) <= EPSILON && //close to 0
			Ogre::Math::Abs(m_mat[2][2] - mat[2][2]) <= EPSILON && //close to 0
			Ogre::Math::Abs(m_mat[3][2] - mat[3][2]) <= EPSILON &&
			Ogre::Math::Abs(m_mat[0][3] - mat[0][3]) <= EPSILON && //close to 0
			Ogre::Math::Abs(m_mat[1][3] - mat[1][3]) <= EPSILON && //close to 0
			Ogre::Math::Abs(m_mat[2][3] - mat[2][3]) <= EPSILON && //close to 0
			Ogre::Math::Abs(m_mat[3][3] - mat[3][3]) <= EPSILON;
}

const Decimal* AABSEngine::Core::Matrix4::operator[](unsigned int row)const
{
	return m_mat[row];
}

Decimal* AABSEngine::Core::Matrix4::operator[](unsigned int row)
{
	return m_mat[row];
}

AABSEngine::Core::Matrix4 AABSEngine::Core::Matrix4::operator*(const Matrix4& mtx)const
{
	Matrix4 out;
	out.Get() = m_mat * mtx.m_mat;

	return out;
}
		
AABSEngine::Core::Matrix4& AABSEngine::Core::Matrix4::operator*=(const Matrix4& mtx)
{
	m_mat = m_mat * mtx.m_mat;
	return *this;
}

AABSEngine::Core::Matrix4 AABSEngine::Core::Matrix4::Inverse()const
{
	Matrix4 out;
	out.Get() = m_mat.inverse();
	return out;
}
		
void AABSEngine::Core::Matrix4::Inversed()
{
	m_mat = m_mat.inverse();
}


AABSEngine::Core::Matrix4 AABSEngine::Core::Matrix4::Transpose()const
{
	Matrix4 out;
	out.Get() = m_mat.transpose();
	return out;
}
		

void AABSEngine::Core::Matrix4::Transposed()
{
	m_mat = m_mat.transpose();
}
		
void AABSEngine::Core::Matrix4::Swap(Matrix4& other)
{
	m_mat.swap(other.m_mat);
}

void AABSEngine::Core::Matrix4::Identity()
{
	m_mat = Ogre::Matrix4::IDENTITY;
}


void AABSEngine::Core::Matrix4::SetupFrom3x3(const Matrix3& mat3x3)
{
	for(int row=0; row<3; row++)
	{
		for(int col=0; col<3; col++)
		{
			m_mat[row][col] = mat3x3[row][col];
		}
	}
	//leave translation portion as normal
}

void AABSEngine::Core::Matrix4::SetOrigin(const Vector3& origin) //insert sams vector here
{
	m_mat[0][3] = origin.X();
	m_mat[1][3] = origin.Y();
	m_mat[2][3] = origin.Z();
}
			

AABSEngine::Core::Vector3 AABSEngine::Core::Matrix4::GetOrigin() //insert sams vector here
{
	return Vector3(m_mat[0][3],m_mat[1][3],m_mat[2][3]);
}

void AABSEngine::Core::Matrix4::RotateArbitaryAxis(const Vector3& axis, Decimal degree)
{
	Matrix4 temp;

	temp.SetArbitaryAxis(axis,degree);

	m_mat = m_mat * temp.m_mat;
}

void AABSEngine::Core::Matrix4::SetArbitaryAxis(const Vector3& axis, Decimal degree)
{
	Decimal sineT = Ogre::Math::Sin(Ogre::Degree(degree));
	Decimal cosT = Ogre::Math::Cos(Ogre::Degree(degree)); 
			
	Decimal oneNegCosT = 1.0 - cosT;
			
	Decimal n_xMulty = axis.X() * axis.Y();
	Decimal n_xMultz = axis.X() * axis.Z();
	Decimal n_yMultz = axis.Y() * axis.Z();
			
	Decimal n_xSineT = axis.X() * sineT;
	Decimal n_ySineT = axis.Y() * sineT;
	Decimal n_zSineT = axis.Z() * sineT;

	//column 1
	m_mat[0][0] = (axis.X() * axis.X()) * oneNegCosT + cosT; 
	m_mat[1][0] = (n_xMulty) * oneNegCosT + (n_zSineT);
	m_mat[2][0] = (n_xMultz) * oneNegCosT - (n_ySineT);

	//column 2
	m_mat[0][1] = (n_xMulty) * oneNegCosT - (n_zSineT);
	m_mat[1][1] = (axis.Y() * axis.Y()) * oneNegCosT + cosT;
	m_mat[2][1] = (n_yMultz) * oneNegCosT + (n_xSineT);
		
	//column 3
	m_mat[0][2] = (n_xMultz) * oneNegCosT + (n_ySineT);
	m_mat[1][2] = (n_yMultz) * oneNegCosT - (n_xSineT);
	m_mat[2][2] = (axis.Z() * axis.Z()) * oneNegCosT + cosT;
}

void AABSEngine::Core::Matrix4::RotateEuler(Axis axis, Decimal degree)
{
	Matrix4 temp;
	
	temp.SetEuler(axis,degree);

	m_mat = m_mat * temp.m_mat;
}


void AABSEngine::Core::Matrix4::RotateEuler(Concatenation order, Decimal yaw, Decimal pitch, Decimal roll)
{
	Matrix3 _3x3;
	_3x3.SetEuler(order,yaw,pitch,roll);
	
	Matrix4 temp;
	temp.SetupFrom3x3(_3x3);

	m_mat = m_mat * temp.m_mat;
}

void AABSEngine::Core::Matrix4::SetEuler(Concatenation order, Decimal yaw, Decimal pitch, Decimal roll)
{
	Matrix3 temp;
	temp.SetEuler(order,yaw,pitch,roll);
	SetupFrom3x3(temp);
}

void AABSEngine::Core::Matrix4::SetEuler(Axis axis, Decimal degree)
{
	Matrix3 temp;
	temp.SetEuler(axis,degree);
	SetupFrom3x3(temp);
}

AABSEngine::Core::Point3 AABSEngine::Core::Matrix4::operator*(const Point3& p)const
{
	return ObjectToWorld(p);
}

AABSEngine::Core::Vector3 AABSEngine::Core::Matrix4::operator*(const Vector3& v)const
{
	return ObjectToWorld(v);
}

void AABSEngine::Core::Matrix4::SetValue(const Vector3& x, const Vector3& y, const Vector3& z, const Point3& p)
{
	m_mat[0][0] = x.X();	m_mat[1][0] = x.Y();	m_mat[2][0] = x.Z();	m_mat[3][0] = 0;
	m_mat[0][1] = y.X();    m_mat[1][1] = y.Y();    m_mat[2][1] = y.Z();	m_mat[3][1] = 0;
	m_mat[0][2] = z.X();    m_mat[1][2] = z.Y();    m_mat[2][2] = z.Z();	m_mat[3][2] = 0;
	m_mat[0][3] = p.X();    m_mat[1][3] = p.Y();    m_mat[2][3] = p.Z();	m_mat[3][3] = 1.0;
}


AABSEngine::Core::Vector3 AABSEngine::Core::Matrix4::WorldToObject(const Vector3& v)const
{
	Vector3 out;

	out[0] = v.X() * m_mat[0][0] + v.Y() * m_mat[1][0] + v.Z() * m_mat[2][0];
	out[1] = v.X() * m_mat[0][1] + v.Y() * m_mat[1][1] + v.Z() * m_mat[2][1];
	out[2] = v.X() * m_mat[0][2] + v.Y() * m_mat[1][2] + v.Z() * m_mat[2][2];
	
	return out;	
}

AABSEngine::Core::Point3 AABSEngine::Core::Matrix4::WorldToObject(const Point3& p)const
{
	Point3 ptemp(p), out;

	ptemp[0] -= m_mat[0][3];
	ptemp[1] -= m_mat[1][3];
	ptemp[2] -= m_mat[2][3];

	out[0] = ptemp.X() * m_mat[0][0] + ptemp.Y() * m_mat[1][0] + ptemp.Z() * m_mat[2][0];
	out[1] = ptemp.X() * m_mat[0][1] + ptemp.Y() * m_mat[1][1] + ptemp.Z() * m_mat[2][1];
	out[2] = ptemp.X() * m_mat[0][2] + ptemp.Y() * m_mat[1][2] + ptemp.Z() * m_mat[2][2];


	return out;		
}

AABSEngine::Core::Point3 AABSEngine::Core::Matrix4::ObjectToWorld(const Point3& p)const
{
	Point3 out;

	out[0] = p.X() * m_mat[0][0] + p.Y() * m_mat[0][1] + p.Z() * m_mat[0][2] + m_mat[0][3];
	out[1] = p.X() * m_mat[1][0] + p.Y() * m_mat[1][1] + p.Z() * m_mat[1][2] + m_mat[1][3];
	out[2] = p.X() * m_mat[2][0] + p.Y() * m_mat[2][1] + p.Z() * m_mat[2][2] + m_mat[2][3];

	return out;		
}

AABSEngine::Core::Vector3 AABSEngine::Core::Matrix4::ObjectToWorld(const Vector3& v)const
{
	Vector3 out;

	out[0] = v.X() * m_mat[0][0] + v.Y() * m_mat[0][1] + v.Z() * m_mat[0][2];
	out[1] = v.X() * m_mat[1][0] + v.Y() * m_mat[1][1] + v.Z() * m_mat[1][2];
	out[2] = v.X() * m_mat[2][0] + v.Y() * m_mat[2][1] + v.Z() * m_mat[2][2];

	return out;
}

void AABSEngine::Core::Matrix4::ExtractTransform(const Quaternion& quat, const Point3& pos)
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
	m_mat[0][3] = pos.X();
	
	m_mat[1][0] = qXY2 + qWZ2;
	m_mat[1][1] = 1 - qX2 - qZ2;
	m_mat[1][2] = qYZ2 - qWX2;
	m_mat[1][3] = pos.Y();
	
	m_mat[2][0] = qXZ2 - qWY2;
	m_mat[2][1] = qYZ2 + qWX2;
	m_mat[2][2] = 1 - qX2 - qY2;
	m_mat[2][3] = pos.Z();
}