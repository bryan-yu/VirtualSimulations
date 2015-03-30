#include "StdAfx.h"
#include "Vector3.h"
#include "Point3.h"

using namespace AABSEngine::Core;

Vector3::Vector3()
{
	vec = new Ogre::Vector3(0, 0, 0);
}

Vector3::Vector3(const Decimal fX, const Decimal fY, const Decimal fZ)
{
	vec = new Ogre::Vector3(fX, fY, fZ);
}

Vector3::Vector3(const Vector3& rvec)
{
	vec = new Ogre::Vector3(rvec[0], rvec[1], rvec[2]);
}

Vector3::Vector3(const Point3& rvec)
{
	vec = new Ogre::Vector3(rvec[0], rvec[1], rvec[2]);
}

Vector3::~Vector3()
{
	delete vec;
}


Decimal Vector3::X() const
{
	return (*this)[0];
}

Decimal Vector3::Y() const
{
	return (*this)[1];
}

Decimal Vector3::Z() const
{
	return (*this)[2];
}

const Ogre::Vector3 Vector3::get() const
{
	return *vec;
}

void Vector3::xyz(Decimal x, Decimal y, Decimal z)
{
	(*vec)[0] = x;
	(*vec)[1] = y;
	(*vec)[2] = z;
}

Decimal Vector3::operator[] (const size_t i) const
{
	return (*vec)[i];
}

Decimal & Vector3::operator[] (const size_t i)
{
	return (*vec)[i];
}

Vector3 & Vector3::operator= (const Vector3 &rvec)
{
	copy(rvec);
	return *this;
}

bool Vector3::operator== (const Vector3 &rvec) const
{
	return (*vec == rvec.get());
}

bool Vector3::operator!= (const Vector3 &rvec) const
{
	return !(this->operator==(rvec));
}

Vector3 Vector3::operator+ (const Vector3 &rvec) const
{
	Ogre::Vector3 v = *vec + rvec.get();
	return Vector3(v[0], v[1], v[2]);
}

Vector3 Vector3::operator- (const Vector3 &rvec) const
{
	Ogre::Vector3 v = *vec - rvec.get();
	return Vector3(v[0], v[1], v[2]);
}

Vector3 Vector3::operator* (const Decimal fScalar) const
{
	Ogre::Vector3 v = *vec * fScalar;
	return Vector3(v[0], v[1], v[2]);
}

Vector3 Vector3::operator* (const Vector3 &rvec) const
{
	Ogre::Vector3 v = *vec * rvec.get();
	return Vector3(v[0], v[1], v[2]);
}

Vector3 Vector3::operator/ (const Decimal fScalar) const
{
	Ogre::Vector3 v = *vec / fScalar;
	return Vector3(v[0], v[1], v[2]);
}

Vector3 Vector3::operator/ (const Vector3 &rvec) const
{
	Ogre::Vector3 v = *vec / rvec.get();
	return Vector3(v[0], v[1], v[2]);
}

Vector3 & Vector3::operator+= (const Vector3 &rvec)
{
	*vec += rvec.get();
	return *this;
}

Vector3 & Vector3::operator+= (const Decimal fScalar)
{
	*vec += fScalar;
	return *this;
}

Vector3 & Vector3::operator-= (const Vector3 &rvec)
{
	*vec -= rvec.get();
	return *this;
}

Vector3 & Vector3::operator-= (const Decimal fScalar)
{
	*vec -= fScalar;
	return *this;
}

Vector3 & Vector3::operator*= (const Decimal fScalar)
{
	*vec *= fScalar;
	return *this;
}

Vector3 & Vector3::operator*= (const Vector3 &rvec)
{
	*vec *= rvec.get();
	return *this;
}

Vector3 & Vector3::operator/= (const Decimal fScalar)
{
	*vec /= fScalar;
	return *this;
}

Vector3 & Vector3::operator/= (const Vector3 &rvec)
{
	*vec /= rvec.get();
	return *this;
}

Decimal Vector3::magnitude() const
{
	return vec->length();
}

Decimal Vector3::squaredMagnitude() const
{
	return vec->squaredLength();
}

Decimal Vector3::distance(const Vector3 &rhs) const
{
	const Ogre::Vector3 vect = rhs.get();
	return vec->distance(vect);
}

Decimal Vector3::squaredDistance(const Vector3 &rhs) const
{
	const Ogre::Vector3 vect = rhs.get();
	return vec->squaredDistance(vect);
}

Decimal Vector3::dotProduct(const Vector3 &rvec) const
{
	const Ogre::Vector3 vect = rvec.get();
	return vec->dotProduct(vect);
}

Decimal Vector3::absDotProduct(const Vector3 &rvec) const
{
	const Ogre::Vector3 vect = rvec.get();
	return vec->absDotProduct(vect);
}

void Vector3::addScaledVector(const Vector3& rvec, Decimal t)
{
	(*vec)[0] += rvec.X() * t;
	(*vec)[1] += rvec.Y() * t;
	(*vec)[2] += rvec.Z() * t;
}

void Vector3::negate()
{
	*vec *= -1.0;
}

Decimal Vector3::normalise()
{
	return vec->normalise();
}

Vector3 Vector3::reflect(const Vector3& norm)const
{
	Ogre::Vector3 v = vec->reflect(norm.get());
	return Vector3(v[0], v[1], v[2]);
}

Vector3 Vector3::normalised()const
{
	Vector3 n = *this;

	n.normalise();

	return n;
}

Vector3 Vector3::crossProduct(const Vector3 &rvec) const
{
	Ogre::Vector3 v = vec->crossProduct(rvec.get());
	return Vector3(v[0], v[1], v[2]);
}

void Vector3::copy(const Vector3 &rvec)
{
	(*vec)[0] = rvec[0];
	(*vec)[1] = rvec[1];
	(*vec)[2] = rvec[2];
}