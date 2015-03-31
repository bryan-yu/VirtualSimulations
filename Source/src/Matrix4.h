#ifndef Matrix4_h
#define Matrix4_h

#include "OgreMatrix4.h"
#include "Vector3.h"
#include "Point3.h"
#include "types.h"

namespace AABSEngine
{
	namespace Core
	{
		class Matrix3;

		class Quaternion;

		/**
		** @class Matrix4
		** @brief Column major 4x4 matrix in right handed space
		**/
		class Matrix4
		{
		public:
			Matrix4();

			Matrix4(const Matrix4& mat);

			Matrix4& operator=(const Matrix4& mat);

			bool operator==(const Matrix4& mat)const;

			const Decimal* operator[](unsigned int row)const;

			Decimal* operator[](unsigned int row);

			Matrix4 operator*(const Matrix4& mtx)const;
		
			Matrix4& operator*=(const Matrix4& mtx);

			Vector3 operator*(const Vector3& v)const;

			Point3 operator*(const Point3& p)const;

			/**
			** @brief Return an inverse of this matrix 
			** @return inverse of this matrix by value
			**/
			Matrix4 Inverse()const;
		
			/**
			** @brief Perform inversion of this matrix and apply changes
			**/
			void Inversed();

			/**
			** @brief Create a matrix that is a transpose of this
			** @return a transposed matrix
			**/
			Matrix4 Transpose()const;
		
			/**
			** @brief Perform transposition on this matrix
			**/
			void Transposed();
		
			/**
			** @brief Swap this and another matrix's values
			** @param other matrix
			**/
			void Swap(Matrix4& other);

			/**
			** @brief Reset this to an identity matrix
			**/
			void Identity();

			/**
			** @brief Simply copy over rotational values from a 3x3 matrix
			** @param Matrix3 object
			**/
			void SetupFrom3x3(const Matrix3& mat);

			/**
			** @brief Retrieve underlying matrix
			** @return ogre matrix 4x4 by reference
			**/
			Ogre::Matrix4& Get() { return m_mat; }

			/**
			** @brief Set origin/translation portion of the matrix
			** @param the position
			**/
			void SetOrigin(const Vector3& origin); 
			
			/**
			** @brief Return the origin of the matrix
			** @return position
			**/
			Vector3 GetOrigin();//insert sams vector here

			/**
			** @brief Perform a rotation about an arbitary axis and angle by post-multiplying this matrix
			** with the one representing the axis-angle rotation
			** @param arbitary axis
			** @param degrees
			**/
			void RotateArbitaryAxis(const Vector3& axis, Decimal degree);

			/**
			** @brief Rotate current matrix by yaw pitch and roll angles with a specified concatenation order
			** @param order is the order of concatenation
			** @param yaw (y axis)
			** @param pitch (x axis)
			** @param roll (z axis)
			**/
			void RotateEuler(Concatenation order, Decimal yaw, Decimal pitch, Decimal roll);

			/**
			** @brief Perform a euler rotation about fixed x,y or z axis
			** @param axis(x,y or z)
			** @param degree rotation about the axis
			**/
			void RotateEuler(Axis axis, Decimal degree);

			/**
			** @brief Setup this matrix to contain rotational values of a specified axis-angle rotation. Translation is left untouched
			** @param arbitary axis
			** @param degrees
			**/
			void SetArbitaryAxis(const Vector3& axis, Decimal degree);

			/**
			** @brief Set values of this column matrix
			** @param x values for column 1 of the matrix
			** @param y values for column 2 of the matrix
			** @param z values for column 3 of the matrix
			** @param p values for column 4 of the matrix(position)
			**/
			void SetValue(const Vector3& x, const Vector3& y, const Vector3& z, const Point3& p); //insert sams vector here

			/**
			** @brief Set this matrix to be a concatenation of yaw pitch and roll of specified order
			** @param order of concatenation
			** @param yaw in degrees
			** @param pitch in degrees
			** @param roll in degrees
			**/
			void SetEuler(Concatenation order, Decimal yaw, Decimal pitch, Decimal roll);

			/**
			** @brief Set this matrix to contain values of a rotation about a fixed(x,y or z) axis by a specified angle
			** @param axis (x,y or z)
			** @param degrees rotation
			**/
			void SetEuler(Axis axis, Decimal degree);
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
			** @brief Given a quaternion and point, we normalise the quaternion and then build the matrix4x4
			** @param quaternion representing orientation, does not need to be normalized
			** @param position 
			**/
			void ExtractTransform(const Quaternion& quat, const Point3& pos);

			/**
			** @brief Extract quaternion from this roation matrix's current values
			** @param quat to store extracted values
			**/
			void ExtractQuaternion(AABSEngine::Core::Quaternion& quat);

		private:
			Ogre::Matrix4 m_mat;
		};
	}
}

#endif