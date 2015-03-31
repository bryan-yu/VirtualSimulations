#ifndef MatrixTests_h
#define MatrixTests_h

#include <iostream>
#include "..\clean\Matrix3.h"
#include "..\clean\Matrix4.h"
#include "..\clean\Quaternion.h"
#include "..\resources\include\OGRE\OgreQuaternion.h"
#include "..\resources\include\OGRE\OgreVector3.h"

using namespace AABSEngine;
using namespace Core;

class Mat4Test
{
public:
	void PrintMatrix4(const Matrix4 &mtx)
	{
		for(int i=0; i<4; ++i)
		{
			for(int j=0; j<4; ++j)
			{
				std::cout<<"M["<<i<<","<<j<<"]"<<"="<<mtx[i][j];

				if(j < 3)
				{
					std::cout<<", ";
				}
			}
			std::cout<<'\n';
		}
	}

	void TestVectorTransforms()
	{
		Matrix4 mtx;
		mtx.SetArbitaryAxis(Vector3(0,1,0),25);
		//mtx.SetOrigin(Vector3(10,10,10));

		std::cout<<"Creating a matrix rotated around yaw by 25 degrees at translation(10,10,10)"<<std::endl<<std::endl;

		Point3 p1(2,5,10);
		Vector3 v1(2,5,10);

		std::cout<<"Performing world->object transform for a point(2,5,10) by the matrix"<<std::endl;
		Point3 p2 = mtx.WorldToObject(p1);

		std::cout<<"Resulting point: ";
		std::cout<<p2.X()<<","<<p2.Y()<<","<<p2.Z()<<std::endl;		
			
		std::cout<<"Performing object->world transform for a point(2,5,10) by the matrix"<<std::endl;
		p2 = mtx.ObjectToWorld(p1);

		std::cout<<"Resulting point: ";
		std::cout<<p2.X()<<","<<p2.Y()<<","<<p2.Z()<<std::endl;		

	
		std::cout<<std::endl<<std::endl;


		std::cout<<"Performing world->object transform for a vector(2,5,10) by the matrix"<<std::endl;
		Vector3 v2 = mtx.WorldToObject(v1);

		std::cout<<"Resulting vector: ";
		std::cout<<v2.X()<<","<<v2.Y()<<","<<v2.Z()<<std::endl;		

		std::cout<<"Performing object->world transform for a vector(2,5,10) by the matrix"<<std::endl;
		v2 = mtx.ObjectToWorld(v1);

		std::cout<<"Resulting vector: ";
		std::cout<<v2.X()<<","<<v2.Y()<<","<<v2.Z()<<std::endl;	


		std::cout<<std::endl<<std::endl;


		std::cout<<"Setting translation portion of matrix to (10,10,10)"<<std::endl;
		mtx.SetOrigin(Vector3(10,10,10));

		std::cout<<"Performing object->world transform for a point(2,5,10) by the matrix excluding translation"<<std::endl;
		v2 = mtx.WorldToObject(v1);

		std::cout<<"Resulting vector: ";
		std::cout<<v2.X()<<","<<v2.Y()<<","<<v2.Z()<<std::endl;		


		std::cout<<"Performing object->world transform for a point(2,5,10) by the matrix, factoring in translation"<<std::endl;
		p2 = mtx.WorldToObject(p1);

		std::cout<<"Resulting point: ";
		std::cout<<p2.X()<<","<<p2.Y()<<","<<p2.Z()<<std::endl;			

		std::cout<<std::endl;

		std::cout<<"Testing and comparing matrix object -> world transforms with ogre and aabs vectors set to (3,6,5)"<<std::endl;

		AABSEngine::Core::Matrix4 aabsMt;
		AABSEngine::Core::Vector3 aabsV(3,6,5);

		Ogre::Matrix4 ogreMt;
		Ogre::Vector3 ogreV(3,6,5);

		aabsMt.SetEuler(ConcatenationOrder::YXZ,270,45,90);
		ogreMt = aabsMt.Get();

		AABSEngine::Core::Vector3 temp1; 
		Ogre::Vector3 temp2;
		

		temp1 = aabsMt.ObjectToWorld(aabsV);
		temp2 = ogreMt.transformAffine(ogreV);

		std::cout<<"Printing object to world for aabsVector followed by ogreVector"<<std::endl;
		std::cout<<temp1.X()<<","<<temp1.Y()<<","<<temp1.Z()<<std::endl;
		std::cout<<temp2.x<<","<<temp2.y<<","<<temp2.z<<std::endl;

		
		temp1 = aabsMt.WorldToObject(aabsV);
		ogreMt = ogreMt.transpose();
		temp2 = ogreMt.transformAffine(ogreV);

		std::cout<<"Printing world to object for aabsVector followed by ogreVector"<<std::endl;
		std::cout<<temp1.X()<<","<<temp1.Y()<<","<<temp1.Z()<<std::endl;
		std::cout<<temp2.x<<","<<temp2.y<<","<<temp2.z<<std::endl;

	}

	void TestOperator()
	{
		std::cout<<"Testing matrix 4x4 composed of 45 degree yaw rotation and translation of (10,5,5), post multiplied by vector(2,9,5)"<<std::endl;
		std::cout<<"Testing matrix 4x4 composed of 45 degree yaw rotation and translation of (10,5,5), post multiplied by point(5,10,8)"<<std::endl;

		Matrix4 mtx;
		mtx.SetEuler(Y,45);
		mtx.SetOrigin(Vector3(10,5,5));

		Vector3 v(2,9,5);
		Point3 p(5,10,8);

		Vector3 res_v = mtx * v;
		Point3 res_p = mtx * p;

		std::cout<<"Resulting vector: ";
		std::cout<<res_v.X()<<","<<res_v.Y()<<","<<res_v.Z()<<std::endl;
	
		std::cout<<"Resulting point: ";
		std::cout<<res_p.X()<<","<<res_p.Y()<<","<<res_p.Z()<<std::endl;	
	}

	void TestInverse()
	{
		std::cout<<"Testing inverse operation of 3x3 matrix. If mtx * mtx.Inverse is identity or close to, then inverse worked"<<std::endl;
		std::cout<<"Creating a matrix which is a rotation of 35 about the y axis, 20 about the x axis and 40 about the z axis"<<std::endl;
		
		Matrix4 m;
		m.RotateEuler(ConcatenationOrder::YXZ, 35, 20, 40);

		std::cout<<"Result of this matrix mult by its inverse is: "<<std::endl;
		Matrix4 res = m * m.Inverse(); 
		PrintMatrix4(res);
	}
	
	void TestTranspose()
	{
		Matrix4 m;
		m.SetEuler(ConcatenationOrder::YXZ, 120,50,80);
		
		std::cout<<"Matrix before transpose.. "<<std::endl;
		PrintMatrix4(m);

		std::cout<<"Matrix after transpose.. "<<std::endl;
		m.Transposed();
		PrintMatrix4(m);
	}
	
	void TestEulerRotation()
	{
		Matrix4 m;
		m.SetEuler(X, 45.0);
		m.RotateEuler(Y,20.0);
		
		std::cout<<"Set 45 degree matrix on X axis, then rotate by 20 on Y axis"<<std::endl;
		PrintMatrix4(m);
		std::cout<<'\n';

		m.Identity();
		m.SetEuler(Y, 35.0);
		m.RotateEuler(X,10.0);
		
		std::cout<<"Set 35 degree matrix on X axis, then rotate by 10 on X axis"<<std::endl;
		PrintMatrix4(m);
		std::cout<<'\n';

		m.Identity();
		m.SetEuler(Z, 120.0);
		m.RotateEuler(Y,20.0);
		
		std::cout<<"Set 120 degree matrix on Z axis, then rotate by 20 on Y axis"<<std::endl;
		PrintMatrix4(m);
		std::cout<<'\n';

		m.Identity();
		m.RotateEuler(ConcatenationOrder::YXZ, 35, 120, 90);
		std::cout<<"Printing Result of identity matrix multiplied by a matrix rotation 35 around x axis, 120 around y and 90 around z in YXZ concatenation order"<<std::endl;
		PrintMatrix4(m);
	}

	void TestArbitaryRotation()
	{
		std::cout<<"Testing 4x4 matrix arbitary rotation set to 45 degrees about (0,1,1), followed by 80 degrees about the x axis"<<std::endl;

		Matrix4 m;
		m.SetArbitaryAxis(Vector3(0,1,1),45);
		m.SetOrigin(Vector3(10,10,10));	
		m.RotateArbitaryAxis(Vector3(1,0,0),80);

		PrintMatrix4(m);
	}

	void TestPointRotation()
	{
		Point3 pt1(5,5,5);
		Matrix4 mtx1;

		mtx1.RotateEuler(Z,120);
		pt1 = mtx1 * pt1;
	
		std::cout<<"Rotating a point(5,5,5) by roll of 120 degrees"<<std::endl;
		std::cout<<"Expected results are (-6.83,1.83,5)"<<std::endl;
		std::cout<<"Final output for point is: "<<pt1.X()<<","<<pt1.Y()<<","<<pt1.Z()<<std::endl;
	}
	
	void TestVectorRotation()
	{
		Vector3 iv(2,5,8);
		Matrix4 m;
		m.SetOrigin(Vector3(50,50,50));
		m.SetArbitaryAxis(Vector3(0,1,0),45);


	    Vector3 fv = m * iv;

		std::cout<<"Performing a 45 degree yaw rotation on a vector with components (2,5,8)"<<std::endl;
		std::cout<<"Expected results to be ~ "<<"(7.07, 5.0, 4.186)"<<std::endl;
		std::cout<<fv.X()<<","<<fv.Y()<<","<<fv.Z()<<std::endl;
	}
};


class Mat3Test
{
public:
	void PrintMatrix3(const Matrix3 &mtx)
	{
		for(int i=0; i<3; ++i)
		{
			for(int j=0; j<3; ++j)
			{
				std::cout<<"M["<<i<<","<<j<<"]"<<"="<<mtx[i][j];
			
				if(j < 2)
				{
					std::cout<<", ";
				}
			}
			std::cout<<'\n';
		}
	}

	void TestVectorTransforms()
	{
		Matrix3 mtx;
		mtx.SetByAxisAngle(Vector3(0,1,0),25);

		std::cout<<"Creating a matrix rotated around yaw by 25 degrees"<<std::endl<<std::endl;

		Point3 p1(2,5,10);
		Vector3 v1(2,5,10);

		std::cout<<"Performing world->object transform for a point(2,5,10) by the matrix"<<std::endl;
		Point3 p2 = mtx.WorldToObject(p1);

		std::cout<<"Resulting point: ";
		std::cout<<p2.X()<<","<<p2.Y()<<","<<p2.Z()<<std::endl;		
			
		std::cout<<"Performing object->world transform for a point(2,5,10) by the matrix"<<std::endl;
		p2 = mtx.ObjectToWorld(p1);

		std::cout<<"Resulting point: ";
		std::cout<<p2.X()<<","<<p2.Y()<<","<<p2.Z()<<std::endl;		

		std::cout<<"Performing world->object transform for a point(2,5,10) by the matrix"<<std::endl;
		Vector3 v2 = mtx.WorldToObject(v1);

		std::cout<<std::endl;

		std::cout<<"Resulting vector: ";
		std::cout<<v2.X()<<","<<v2.Y()<<","<<v2.Z()<<std::endl;		
			
		std::cout<<"Performing object->world transform for a point(2,5,10) by the matrix"<<std::endl;
		v2 = mtx.ObjectToWorld(v1);

		std::cout<<"Resulting vector: ";
		std::cout<<v2.X()<<","<<v2.Y()<<","<<v2.Z()<<std::endl;		
	}

	void TestOperator()
	{
		std::cout<<"Testing matrix 3x3 composed of 45 degree yaw rotation post multiplied by vector(2,9,5)"<<std::endl;
		std::cout<<"Testing matrix 3x3 composed of 45 degree yaw rotation post multiplied by point(2,9,5)"<<std::endl;
		std::cout<<"Both should be composed of the same results"<<std::endl;

		Matrix3 mtx;
		mtx.SetEuler(Y,45);

		Vector3 v(2,9,5);
		Point3 p(2,9,5);

		Vector3 res_v = mtx * v;
		Point3 res_p = mtx * p;

		std::cout<<"Resulting vector: ";
		std::cout<<res_v.X()<<","<<res_v.Y()<<","<<res_v.Z()<<std::endl;
	
		std::cout<<"Resulting point: ";
		std::cout<<res_p.X()<<","<<res_p.Y()<<","<<res_p.Z()<<std::endl;	
	}

	void TestInverse()
	{
		std::cout<<"Testing inverse operation of 4x4 matrix. If mtx * mtx.Inverse is identity or close to, then inverse worked"<<std::endl;
		std::cout<<"Creating a matrix which is a rotation of 35 about the y axis, 20 about the x axis and 40 about the z axis"<<std::endl;
		
		Matrix3 m;
		m.RotateEuler(ConcatenationOrder::YXZ, 35, 20, 40);		

		std::cout<<"Result of this matrix mult by its inverse is: "<<std::endl;
		Matrix3 res = m * m.Inverse(); 
		PrintMatrix3(res);
	}
	
	void TestTranspose()
	{
		Matrix3 m;
		m.SetEuler(ConcatenationOrder::YXZ, 120,50,80);
		
		std::cout<<"Matrix before transpose.. "<<std::endl;
		PrintMatrix3(m);

		std::cout<<"Matrix after transpose.. "<<std::endl;
		m.Transposed();
		PrintMatrix3(m);
	}
	
	void TestEulerRotation()
	{
		Matrix3 m;
		m.SetEuler(X, 45.0);
		m.RotateEuler(Y,20.0);
		
		std::cout<<"Set 45 degree matrix on X axis, then rotate by 20 on Y axis"<<std::endl;
		PrintMatrix3(m);
		std::cout<<'\n';

		m.Identity();
		m.SetEuler(Y, 35.0);
		m.RotateEuler(X,10.0);
		
		std::cout<<"Set 35 degree matrix on X axis, then rotate by 10 on X axis"<<std::endl;
		PrintMatrix3(m);
		std::cout<<'\n';


		m.Identity();
		m.SetEuler(Z, 120.0);
		m.RotateEuler(Y,20.0);
		
		std::cout<<"Set 120 degree matrix on Z axis, then rotate by 20 on Y axis"<<std::endl;
		PrintMatrix3(m);
		std::cout<<'\n';

		m.Identity();
		m.RotateEuler(ConcatenationOrder::YXZ, 35, 120, 90);
		std::cout<<"Printing Result of identity matrix multiplied by a matrix rotation 35 around x axis, 120 around y and 90 around z in YXZ concatenation order"<<std::endl;
		PrintMatrix3(m);
	}

	void TestArbitaryRotation()
	{
		std::cout<<"Testing 3x3 matrix arbitary rotation set to 45 degrees about (0,1,1), followed by 80 degrees about the x axis"<<std::endl;

		Matrix3 m;
		m.SetByAxisAngle(Vector3(0,1,1),45);
		m.RotateByAxisAngle(Vector3(1,0,0),80);
		
		PrintMatrix3(m);
	}
	
	void TestVectorRotation()
	{
		Vector3 iv(2,5,8);
		Matrix3 m;
		m.SetByAxisAngle(Vector3(0,1,0),45);


	    Vector3 fv = m * iv;

		std::cout<<"Performing a 45 degree yaw rotation on a vector with components (2,5,8)"<<std::endl;
		std::cout<<"Expected results to be ~ "<<"(7.07, 5.0, 4.186)"<<std::endl;
		std::cout<<fv.X()<<","<<fv.Y()<<","<<fv.Z()<<std::endl;
	}


	void TestPointRotation()
	{
		Point3 pt1(4,4,8);
		Matrix3 mtx1;

		mtx1.RotateEuler(YXZ,40,50,0);
		pt1 = mtx1 * pt1;

		std::cout<<"Rotating a point(4,4,8) by yaw pitch roll (40,50,0) in the order YXZ"<<std::endl;
		std::cout<<"Final output for point is: "<<pt1.X()<<","<<pt1.Y()<<","<<pt1.Z()<<std::endl;
	}
};




class QuatTest
{
public:
	void PrintQuaternion(Quaternion& quat)
	{
		std::cout<<"Quaternion component values: "<<quat.W()<<","<<quat.X()<<","<<quat.Y()<<","<<quat.Z()<<std::endl;
	}

	void PrintQuaternion(Ogre::Quaternion& quat)
	{
		std::cout<<"Quaternion component values: "<<quat.w<<","<<quat.x<<","<<quat.y<<","<<quat.z<<std::endl;
	}

	void TestExtractionTo4x4()
	{
		Matrix3 dummy;
		Quaternion quat(Vector3(0,15,17),55);
		Point3 pos(10,40,50);

		Matrix4 mtx;
		mtx.ExtractTransform(quat,pos);

		std::cout<<"Printing our matrix values of extracting from a quaternion"<<std::endl;
		Mat4Test().PrintMatrix4(mtx);

		quat.Normalise();
		quat.Get().ToRotationMatrix(dummy.Get());
		std::cout<<"Printing matrix values that the result above should match"<<std::endl;
		Mat3Test().PrintMatrix3(dummy);
	}

	void TestOperator()
	{
		Quaternion rot1(Vector3(0,1,0),45);
		Ogre::Quaternion rot2(3.14/4.0, 0, 1, 0);

		std::cout<<"Rotation 45 degrees about yaw, w,x,y,z values for AABS Quaternion"<<std::endl;
		PrintQuaternion(rot1.Get());

		std::cout<<"Rotation 45 degrees about yaw, w,x,y,z values for Ogre Quaternion"<<std::endl;
		PrintQuaternion(rot2);

		Quaternion rot3(Vector3(1,0,0),30);
		Ogre::Quaternion rot4(30 * 3.14 / 180, 1 ,0 ,0);

		std::cout<<"Rotation of previous Ogre Quaternion 30 degrees about pitch, w,x,y,z values for AABS Quaternion"<<std::endl;
		rot2 = rot2 * rot4;
		PrintQuaternion(rot2);

		std::cout<<"Rotation of previous AABS Quaternion 45 degrees about pitch, w,x,y,z values for Ogre Quaternion"<<std::endl;
		rot1 = rot1 * rot3;
		PrintQuaternion(rot1);	
	}

	void TestInverse()
	{
		std::cout<<std::endl;
		Quaternion q1(Vector3(1,1,0),50);
		Ogre::Quaternion q2(50 * 3.14 / 180, 1, 1, 0);
		
		std::cout<<"Contents of a target quaternion: "<<std::endl;
		q1.Invert();
		PrintQuaternion(q1);

		std::cout<<"Testing source quaternion * difference which should equal to the target quaternion"<<std::endl;
		PrintQuaternion(q2.Inverse());
	}

	void TestUnitization()
	{
		Quaternion q1(Vector3(12,40,15),120);
		std::cout<<"Printing aabs quaternion with wxyz(120,12,44,15)"<<std::endl;
		PrintQuaternion(q1);
		std::cout<<"Printing aabs quaternion from before, normalised"<<std::endl;
		q1.Normalise();
		PrintQuaternion(q1);

		Ogre::Quaternion q2(Ogre::Degree(120).valueRadians(),12,40,15);
		std::cout<<"Printing ogre quaternion with wxyz(120,12,44,15)"<<std::endl;
		PrintQuaternion(q2);
		std::cout<<"Printing ogre quaternion from before, normalised"<<std::endl;
		q2.normalise();
		PrintQuaternion(q2);
	}

	void TestConjugation()
	{
		Quaternion q1(Vector3(1,1,1),270);
		
		std::cout<<"Testing conjugation of a quaternion with wxyz(270,1,1,1) which should result in wxyz(4.17,-1,-1,-1)"<<std::endl;
		q1.Conjugate();
		PrintQuaternion(q1);
	}

	void TestDifference()
	{
		std::cout<<std::endl;
		Quaternion src(Vector3(1,1,0),45);
		Quaternion dest(Vector3(1,1,0),45);


		Quaternion dif = src.Difference(dest);

		std::cout<<"Contents of a target quaternion: "<<std::endl;
		PrintQuaternion(dest);

		std::cout<<"Testing source quaternion * difference which should equal to the target quaternion"<<std::endl;
		PrintQuaternion(src * dif);
	}
};

#endif