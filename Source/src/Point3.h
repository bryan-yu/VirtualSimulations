#pragma once

#include "types.h"
#include "OgreVector3.h"
#include "Vector3.h"

namespace AABSEngine
{
	namespace Core
	{
		class Vector3;

		/**
		 * @class Point3
		 *
		 * @brief 
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class Point3
		{
		private:
			Ogre::Vector3* vec;
			void copy(const Point3 &rvec);
		protected:
		public:
			Point3();
 			Point3(const Decimal fX, const Decimal fY, const Decimal fZ);
			Point3(const Point3& rhs);
			Point3(const Vector3& rhs);
			~Point3();

			Decimal X() const;
			Decimal Y() const;
			Decimal Z() const;

			const Ogre::Vector3 get() const;

			Decimal operator[] (const size_t i) const;
			Decimal & operator[] (const size_t i);
			Point3 & operator= (const Point3 &rvec);

			bool operator== (const Point3 &rvec) const;
			bool operator!= (const Point3 &rvec) const;
			
			Vector3 operator+ (const Point3 &rvec) const;
			Vector3 operator- (const Point3 &rvec) const;

			Point3 operator+ (const Vector3& rvec) const;
			Point3 operator- (const Vector3& rvec) const;
			
			void xyz(Decimal x, Decimal y, Decimal z);
			void addScaledVector(const Vector3& rvec, Decimal t);
		};
	}
}