#include "StdAfx.h"
#include "Camera.h"
#include "OgreMath.h"
using namespace AABSEngine::Rendering;

Camera::Camera(Ogre::Camera* cam, float movespeed, float rotateSpeed)
{
	m_camera = cam;
	m_moveSpeed = movespeed;
	m_rotateSpeed = rotateSpeed;
	m_deltaPitch = 0.0f;
	m_accumulatedPitch = 0.0f;
}

Camera::~Camera()
{

}

void Camera::SetDeltaTime(float deltaTime)
{
	m_deltaTime = deltaTime;
}

void Camera::SetMoveSpeed(float movespeed)
{
	m_moveSpeed = movespeed;
}

void Camera::SetRotateSpeed(float rotateSpeed)
{
	m_rotateSpeed = rotateSpeed;
}

void Camera::MoveUp()
{
	m_camera->setPosition(Ogre::Vector3(m_camera->getPosition().x, m_camera->getPosition().y + m_moveSpeed * m_deltaTime, m_camera->getPosition().z));
}

void Camera::MoveDown()
{
	m_camera->setPosition(Ogre::Vector3(m_camera->getPosition().x, m_camera->getPosition().y - m_moveSpeed * m_deltaTime, m_camera->getPosition().z));
}

void Camera::MoveForward()
{
	Ogre::Vector3 deltaPosition(m_camera->getDirection() * m_moveSpeed * m_deltaTime);
	Ogre::Vector3 newPosition = m_camera->getPosition() + deltaPosition;
	m_camera->setPosition(newPosition);
}

void Camera::MoveBackward()
{
	Ogre::Vector3 deltaPosition(m_camera->getDirection() * m_moveSpeed * m_deltaTime * -1);
	Ogre::Vector3 newPosition = m_camera->getPosition() + deltaPosition;
	m_camera->setPosition(newPosition);
}

void Camera::StrafeLeft()
{
	Ogre::Vector3 deltaPosition(m_camera->getDirection().z, 0, m_camera->getDirection().x * -1);
	Ogre::Vector3 newPosition = m_camera->getPosition() + (deltaPosition * m_deltaTime * m_moveSpeed);
	m_camera->setPosition(newPosition);
}

void Camera::StrafeRight()
{
	Ogre::Vector3 deltaPosition(m_camera->getDirection().z, 0, m_camera->getDirection().x * -1);
	Ogre::Vector3 newPosition = m_camera->getPosition() + (deltaPosition * m_deltaTime * m_moveSpeed * -1);
	m_camera->setPosition(newPosition);
}

void Camera::RotateLeft()
{
	m_camera->yaw(Ogre::Radian(2.0f) * m_deltaTime);
}

void Camera::RotateRight()
{
	m_camera->yaw(Ogre::Radian(2.0f) * m_deltaTime * -1);
}


void Camera::Rotate(int deltax, int deltay)
{
	m_camera->yaw(Ogre::Radian(2.0f) * m_deltaTime * deltax/180.0f * -1 * m_rotateSpeed);
	m_deltaPitch = (Ogre::Radian(2.0f) * m_deltaTime * deltay/180.0f * -1 * m_rotateSpeed);
	
	//+ or - 90 degrees
	Ogre::Radian kHalfPi = Ogre::Radian(Ogre::Math::HALF_PI) - Ogre::Radian((1.0 * Ogre::Math::PI) / 180.0);
	Ogre::Radian y,p,r;

	Ogre::Matrix3 rotation;
	m_camera->getOrientation().ToRotationMatrix(rotation);
	rotation.ToEulerAnglesYXZ(y,p,r);

	if(p + m_deltaPitch > kHalfPi)
	{
		m_deltaPitch = kHalfPi - p;
	}
	else if(p + m_deltaPitch < - kHalfPi)
	{
		m_deltaPitch = -kHalfPi - p;
	}

	m_camera->pitch(m_deltaPitch);
}

void Camera::SetPosition(const AABSEngine::Core::Point3 &newPosition)
{
	m_camera->setPosition(Ogre::Vector3(newPosition.X(), newPosition.Y(), newPosition.Z()));
}

AABSEngine::Core::Vector3 Camera::GetDirection()const
{
	Ogre::Vector3 heading = m_camera->getDirection();

	return AABSEngine::Core::Vector3(heading.x, heading.y, heading.z);
}

AABSEngine::Core::Point3 Camera::GetOrigin()const
{
	Ogre::Vector3 origin = m_camera->getPosition();

	return AABSEngine::Core::Vector3(origin.x, origin.y, origin.z);
}