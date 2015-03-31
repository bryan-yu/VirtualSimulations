#pragma once

#ifndef Quaternion_h
#define Quaternion_h

#include "OgreQuaternion.h"
#include "types.h"
#include "Vector3.h"
#include "OgrePrerequisites.h"


namespace AABSEngine
{
	namespace Core
	{
		class Matrix3;

		/**
		 * @class Quaternion
		 *
		 * @brief 
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class Quaternion
		{
		public:
			Quaternion();

			Quaternion(const Quaternion&);

			Quaternion(const Ogre::Quaternion&);
			
			Quaternion& operator=(const Quaternion&);

			Quaternion(const Vector3& axis, Decimal degree);

			Quaternion(Decimal degree, Decimal x, Decimal y, Decimal z);

			Quaternion operator*(const Quaternion& )const;

			Quaternion operator*(Decimal t)const;

			Vector3 operator*(const Vector3& )const;

			Quaternion& operator*=(const Quaternion& );

			Quaternion& operator*=(Decimal t);

			/**
			** @brief Return W component of the quaternion which is the rotation in radians
			** @return m_quat.w
			**/
			Decimal W()const { return m_quat.w; }

			/**
			** @brief Return x axis component
			** @return m_quat.x
			**/
			Decimal X()const { return m_quat.x; }

			/**
			** @brief Return y axis component
			** @return m_quat.y
			**/
			Decimal Y()const { return m_quat.y; }

			/**
			** @brief Return z axis component
			** @return m_quat.z
			**/
			Decimal Z()const { return m_quat.z; }

			/**
			** @brief Return underlying quaternion
			** @return ogre quaternion by reference
			**/
			Ogre::Quaternion& Get() { return m_quat; }
			
			/**
			** @brief Return underlying quaternion
			** @return ogre quaternion by const reference
			**/
			const Ogre::Quaternion& Get()const { return m_quat;}

			/**
			** @brief Set quaternion values with an angle and rotation axis
			** @param degrees
			** @param x axis component
			** @param y axis component
			** @param z axis component
			**/
			void WXYZ(Decimal degree, Decimal x, Decimal y, Decimal z);


			/**
			** @brief Set quaternion values with an angle and rotation axis
			** @param degrees
			** @param axis of rotation
			**/
			void WXYZ(const Vector3& axis, Decimal degree);

			/**
			** @brief Normalise this quaternion
			**/
			void Normalise();

			/**
			** @brief Invert this quaternion
			**/
			void Invert();

			/**
			** @brief Set to quaternion identity
			**/
			void Identity();

			/**
			** @brief Make this quaternion a conjugate(negated axis component) 
			**/
			void Conjugate();

			/**
			** @brief Calculate magnitude of this quaternion
			** @return magnitude
			**/
			Decimal Magnitude()const;

			/**
			** @brief Find displacement between current and target quaternion, such that invCurrent * target == current
			** @param target 
			**/
			Quaternion Difference(const Quaternion& other)const;

			/**
			** @brief Perform dot product of this and another quaternion
			** @param other quaternion
			** @return magnitude ^ 2
			**/
			Decimal Dot(const Quaternion& other)const;

			/**
			** @brief add scaled vector to this quaternion which also updates its orientation
			** @param vector
			** @param t is the scale or time 
			**/
			void AddScaledVector(const Vector3& v, const Decimal t);

			/**
			** @brief Extract data from rotation matrix to quaternion 
			** @param 3x3 rotation matrix
			**/
			void ExtractTransform(const Matrix3& mat);

			static const AABSEngine::Core::Quaternion IDENTITY;


		private:
			static const Quaternion QUAT_X_180;
			static const Quaternion QUAT_Y_180;
			static const Quaternion QUAT_Z_180;

			static const Quaternion QUAT_X_90;
			static const Quaternion QUAT_Y_90;
			static const Quaternion QUAT_Z_90;

			
			
			Ogre::Quaternion m_quat;
		};
	}
}

#endif