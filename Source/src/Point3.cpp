#include "StdAfx.h"
#include "Point3.h"

using namespace AABSEngine::Core;

void Point3::copy(const Point3 &rvec)
{
	(*vec)[0] = rvec[0];
	(*vec)[1] = rvec[1];
	(*vec)[2] = rvec[2];
}

void Point3::xyz(Decimal x, Decimal y, Decimal z)
{
	(*vec)[0] = x;
	(*vec)[1] = y;
	(*vec)[2] = z;
}

Point3::Point3()
{
	vec = new Ogre::Vector3(0, 0, 0);
}

Point3::Point3(const Decimal fX, const Decimal fY, const Decimal fZ)
{
	vec = new Ogre::Vector3(fX, fY, fZ);
}

Point3::Point3(const Point3& rhs)
{
	vec = new Ogre::Vector3(rhs[0], rhs[1], rhs[2]);
}

Point3::Point3(const Vector3& rhs)
{
	vec = new Ogre::Vector3(rhs[0], rhs[1], rhs[2]);
}

Point3::~Point3()
{
	delete vec;
}

Decimal Point3::X()const
{
	return (*this)[0];
}

Decimal Point3::Y()const
{
	return (*this)[1];
}

Decimal Point3::Z()const
{
	return (*this)[2];
}

const Ogre::Vector3 Point3::get() const
{
	return *vec;
}

Decimal Point3::operator[] (const size_t i) const
{
	return (*vec)[i];
}

Decimal & Point3::operator[] (const size_t i)
{
	return (*vec)[i];
}

Point3 & Point3::operator= (const Point3 &rvec)
{
	copy(rvec);
	return *this;
}

bool Point3::operator== (const Point3 &rvec) const
{
	return (*vec == rvec.get());
}

bool Point3::operator!= (const Point3 &rvec) const
{
	return !(this->operator==(rvec));
}

Vector3 Point3::operator+ (const Point3 &rvec) const
{
	Ogre::Vector3 v = (*vec) + rvec.get();
	return Vector3(v[0], v[1], v[2]);
}

Vector3 Point3::operator- (const Point3 &rvec) const
{
	Ogre::Vector3 v = (*vec) - rvec.get();
	return Vector3(v[0], v[1], v[2]);
}

Point3 Point3::operator+ (const Vector3 &rvec) const
{
	Ogre::Vector3 v = (*vec) + rvec.get();
	return Point3(v[0], v[1], v[2]);
}

Point3 Point3::operator- (const Vector3 &rvec) const
{
	Ogre::Vector3 v = (*vec) - rvec.get();
	return Point3(v[0], v[1], v[2]);
}

void Point3::addScaledVector(const Vector3 &rvec, Decimal t)
{
	(*vec)[0] += rvec.X() * t;
	(*vec)[1] += rvec.Y() * t;
	(*vec)[2] += rvec.Z() * t;
}