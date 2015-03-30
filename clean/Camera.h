#pragma once

#include <string>
#include "Ogre.h"
#include "OgreCamera.h"
#include "IMovable.h"
#include "Point3.h"
#include "Vector3.h"

namespace AABSEngine
{


	namespace Rendering
	{
	/**
	* @class Camera
	*
	* @brief Main camera class
	*
	* @author AABS
	* @version X
	* @date October 2013
	*
	*/
	class Camera : public AABSEngine::Core::IMovable
		{
		private:
		protected:
			Ogre::Camera *m_camera;
			float m_moveSpeed;
			float m_rotateSpeed;
			float m_deltaTime;

			Ogre::Radian m_deltaPitch;
			Ogre::Radian m_accumulatedPitch;
		public:
			Camera(Ogre::Camera* cam, float movespeed, float rotateSpeed);
			~Camera();
			void SetDeltaTime(float deltaTime);
			void SetMoveSpeed(float movespeed);
			void SetRotateSpeed(float rotatespeed);
			void SetPosition(const Core::Point3 &newPosition);
			virtual void MoveUp();
			virtual void MoveDown();
			virtual void MoveForward();
			virtual void MoveBackward();
			virtual void StrafeLeft();
			virtual void StrafeRight();
			virtual void RotateLeft();
			virtual void RotateRight();
			virtual void Rotate(int deltax, int deltay);

			AABSEngine::Core::Vector3 GetDirection()const;
			AABSEngine::Core::Point3 GetOrigin()const;
		};
	}
}