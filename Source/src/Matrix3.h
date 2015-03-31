#pragma once

#include "Vector3.h"
#include "Point3.h"
#include "OgreMatrix3.h"
#include "types.h"
#include <limits>

namespace AABSEngine
{
	namespace Core
	{
		class Quaternion;

		/**
		** @class Matrix3
		** @brief Column major 3x3 matrix in right handed space
		**/
		class Matrix3
		{
		public:
			Matrix3();

			Matrix3(const Matrix3&);

			Matrix3& operator=(const Matrix3&);

			bool operator==(const Matrix3&)const;

			const Decimal* operator[](unsigned int row)const;
			Decimal* operator[](unsigned int row);

			Matrix3 operator*(const Matrix3& mtx)const;
			Matrix3& operator*=(const Matrix3& mtx);
		
			Vector3 operator*(const Vector3& v)const;
			Point3 operator*(const Point3& p)const;

			Matrix3 operator*(const Decimal s)const;
			Matrix3 operator*=(const Decimal s);

			/**
			** @brief Retrieve underlying matrix
			** @return ogre matrix 3x3 by reference
			**/
			Ogre::Matrix3& Get() { return m_mat; }


			/**
			** @brief Retrieve underlying matrix
			** @return ogre matrix 3x3 by const reference
			**/
			const Ogre::Matrix3& Get()const { return m_mat; }

			/**
			** @brief Extract rotation from quaternion
			** @param quaternion
			**/
			void ExtractTransform(const Quaternion& quat);

			/**
			** @brief Return an inverse of this matrix 
			** @return inverse of this matrix by value
			**/
			Matrix3 Inverse()const;
		
			/**
			** @brief Perform inversion of this matrix and apply changes
			**/
			void Inversed();

			/**
			** @brief Create a matrix that is a transpose of this
			** @return a transposed matrix
			**/
			Matrix3 Transpose()const;
		
			/**
			** @brief Perform transposition on this matrix
			**/
			void Transposed();

			/**
			** @brief Swap this and another matrix's values
			** @param other matrix
			**/
			void Swap(Matrix3& other);

			/**
			** @brief Set values of this column matrix
			** @param x values for column 1 of the matrix
			** @param y values for column 2 of the matrix
			** @param z values for column 3 of the matrix
			**/
			void SetValue(const Vector3& x, const Vector3& y, const Vector3& z); //insert sams vector here

			/**
			** @brief Set this matrix to contain the values of a purely yaw, pitch or roll by a specific angle
			** @param axis should be RtAxis::X, RtAxis::Y or RtAxis::Z
			** @param degrees rotation
			**/
			void SetEuler(Axis axis, Decimal degree);
		
			/**
			** @brief Rotate via yaw, pitch or roll about a fixed axis and degrees
			** @param axis should be RtAxis::X, RtAxis::Y or RtAxis::Z
			** @param degrees rotation
			**/
			void RotateEuler(Axis axis, Decimal degree);

			/**
			** @brief Set this matrix's values to be result of a yaw, pitch and roll with any specific concatenation order
			** @param order of concatenation i.e ConcatOrder::XYZ...
			** @param degrees for pitch
			** @param degrees for yaw
			** @param degrees for roll
			**/
			void SetEuler(Concatenation order, Decimal yaw, Decimal pitch, Decimal roll);

			/**
			** @brief Set this matrix's values to be result of a yaw, pitch and roll with any specific concatenation order
			** @param order of concatenation i.e ConcatOrder::XYZ...
			** @param degrees for pitch
			** @param degrees for yaw
			** @param degrees for roll
			**/
			void RotateEuler(Concatenation order, Decimal yaw, Decimal pitch, Decimal roll);

			/**
			** @brief Set matrix's values to be an arbitary rotation about an angle
			** @param arbitary axis
			** @param degrees
			**/
			void SetByAxisAngle(const Vector3& axis, Decimal degree); //insert sams vector

			/**
			** @brief Perform rotation on this rotation about an arbitary axis by an angle in degrees
			** @parama arbitary axis
			** @param degrees
			**/
			void RotateByAxisAngle(const Vector3& axis, Decimal degree); //insert sams vector

			/**
			** @brief Reset this to an identity matrix
			**/
			void Identity();

			/**
			** @brief Transform vector from object to world coordinates
			** @param vector for transformation
			** @return rotated vector from object -> world
			**/
			Vector3 ObjectToWorld(const Vector3& v)const;

			/**
			** @brief Transform vector from world to object coordinates
			** @param vector for transformation
			** @return rotated vector from world -> object
			**/
			Vector3 WorldToObject(const Vector3& v)const;

			/**
			** @brief Transform point from world to object coordinates
			** @param point for transformation
			** @return rotated point from object -> world
			**/
			Point3 ObjectToWorld(const Point3& p)const;

			/**
			** @brief Transform point from world to object coordinates
			** @param point for transformation
			** @return rotated point from world -> object
			**/
			Point3 WorldToObject(const Point3& p)const;


			/**
			** @brief Set this matrix from inertial values, side values
			** do not need to be negated as this function performs that before storing the data
			** @param diagonals are the moments of inertia(xx,yy,zz)
			** @param non-diagonals are products of inertia
			**/
			void SetInertiaTensor(Decimal Ixx, Decimal Iyy, Decimal Izz, Decimal Ixy, Decimal Ixz, Decimal Iyz);

			/**
			** @brief Extract quaternion from this roation matrix's current values
			** @param quat to store extracted values
			**/
			void ExtractQuaternion(AABSEngine::Core::Quaternion& quat);

		protected:
			Ogre::Matrix3 m_mat;
		};

	}
}


