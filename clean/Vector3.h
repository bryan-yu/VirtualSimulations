#pragma once

#include "types.h"
#include "OgreVector3.h"

namespace AABSEngine
{
	namespace Core
	{
		class Point3;

		/**
		 * @class Vector3
		 *
		 * @brief 
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class Vector3
		{
		private:
			Ogre::Vector3* vec;
			void copy(const Vector3 &rvec);
		protected:
		public:
			Vector3();
 			Vector3(const Decimal fX, const Decimal fY, const Decimal fZ);
			Vector3(const Vector3& rvec);
			Vector3(const Point3& rvec);
			~Vector3();

			Decimal X() const;
			Decimal Y() const;
			Decimal Z() const;

			const Ogre::Vector3 get() const;
			Decimal operator[] (const size_t i) const;
			Decimal & operator[] (const size_t i);

			Vector3 & operator= (const Vector3 &rvec);
			bool operator== (const Vector3 &rvec) const;
			bool operator!= (const Vector3 &rvec) const;

			Vector3 operator+ (const Vector3 &rvec) const;
			Vector3 operator- (const Vector3 &rvec) const;
			Vector3 operator* (const Decimal fScalar) const;
			Vector3 operator* (const Vector3 &rhs) const;
			Vector3 operator/ (const Decimal fScalar) const;
			Vector3 operator/ (const Vector3 &rhs) const;

			Vector3 & operator+= (const Vector3 &rvec);
			Vector3 & operator+= (const Decimal fScalar);
			Vector3 & operator-= (const Vector3 &rvec);
			Vector3 & operator-= (const Decimal fScalar);
			Vector3 & operator*= (const Decimal fScalar);
			Vector3 & operator*= (const Vector3 &rvec);
			Vector3 & operator/= (const Decimal fScalar);
			Vector3 & operator/= (const Vector3 &rvec);

			Decimal magnitude() const;
			Decimal squaredMagnitude() const;
			Decimal distance(const Vector3 &rhs) const;
			Decimal squaredDistance(const Vector3 &rhs) const;
			Decimal dotProduct(const Vector3 &vec) const;
			Decimal absDotProduct(const Vector3 &vec) const;
			Decimal normalise();


			Vector3 normalised()const;
			Vector3 reflect(const Vector3& norm)const;
			Vector3 crossProduct(const Vector3 &rvec) const;

			void addScaledVector(const Vector3 &rvec, Decimal t);
			void negate();
		
			void xyz(Decimal x, Decimal y, Decimal z);

      static Vector3 ToVec3(Ogre::Vector3 vec) { return Vector3(vec[0], vec[1], vec[2]); }
		};
	}
}