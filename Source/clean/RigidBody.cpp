#include "StdAfx.h"
#include "RigidBody.h"
#include "btBulletCollisionCommon.h"
#include "Matrix3.h"
#include "Matrix4.h"

using namespace AABSEngine::Physics;

AABSEngine::Physics::RigidBody::RigidBody(OgreBulletCollisions::Object *input, float in_mass, float in_linearDamping, float in_angularDamping)
{
	m_physObject = input;
	SetMass(in_mass);

	m_linearDamping = in_linearDamping;
	m_angularDamping = in_angularDamping;

	m_linearVelocity = AABSEngine::Core::Vector3(0,0,0);
	m_angularVelocity = AABSEngine::Core::Vector3(0,0,0);

	m_previousAcceleration = AABSEngine::Core::Vector3(0,0,0);
	m_linearAcceleration = AABSEngine::Core::Vector3(0,0,0);

	m_sleep = false;
	m_static = false;
	m_kinematic = false;

	ClearAccumulators();
}

AABSEngine::Physics::RigidBody::~RigidBody()
{

}

const AABSEngine::Core::Vector3& AABSEngine::Physics::RigidBody::GetPreviousAcceleration()const
{
	return m_previousAcceleration;
}

void AABSEngine::Physics::RigidBody::SetPreviousAcceleration(const AABSEngine::Core::Vector3& accel)
{
	m_previousAcceleration = accel;
}

void AABSEngine::Physics::RigidBody::AddLinearVelocity(const AABSEngine::Core::Vector3& veloc, Decimal t)
{
	m_linearVelocity.addScaledVector(veloc,t);
}

void AABSEngine::Physics::RigidBody::AddAngularVelocity(const AABSEngine::Core::Vector3& veloc, Decimal t)
{
	m_angularVelocity.addScaledVector(veloc,t);
}

void AABSEngine::Physics::RigidBody::ApplyVelocityDamping(Decimal duration)
{
	m_linearVelocity *= pow(m_linearDamping, duration);
	m_angularVelocity *= pow(m_angularDamping, duration);
}

void AABSEngine::Physics::RigidBody::SetLinearDamping(Decimal damping)
{
	m_linearDamping = damping;
}

Decimal AABSEngine::Physics::RigidBody::GetLinearDamping()const
{
	return m_linearDamping;
}
	
void AABSEngine::Physics::RigidBody::SetAngularDamping(Decimal damping)
{
	m_angularDamping = damping;
}

Decimal AABSEngine::Physics::RigidBody::GetAngularDamping()const
{
	return m_angularDamping;
}

void AABSEngine::Physics::RigidBody::SetForceAccum(const AABSEngine::Core::Vector3& force)
{
	m_forceAccum = force;
}

void AABSEngine::Physics::RigidBody::SetTorqueAccum(const AABSEngine::Core::Vector3& torque)
{
	m_torqueAccum = torque;
}

const AABSEngine::Core::Vector3& AABSEngine::Physics::RigidBody::GetForceAccum()const
{
	return m_forceAccum;
}

const AABSEngine::Core::Vector3& AABSEngine::Physics::RigidBody::GetTorqueAccum()const
{
	return m_torqueAccum;
}

void AABSEngine::Physics::RigidBody::SetStatic(bool input)
{
	m_static = input;
}

bool AABSEngine::Physics::RigidBody::IsStatic() const
{
	return (m_static || m_mass <= 0.0f);
}

void AABSEngine::Physics::RigidBody::SetKinematic(bool input)
{
	m_kinematic = input;
}

bool AABSEngine::Physics::RigidBody::IsKinematic() const
{
	return m_kinematic;
}

void AABSEngine::Physics::RigidBody::BodyToWorldDirection(const AABSEngine::Core::Vector3& localDirect, AABSEngine::Core::Vector3& worldDirect)
{
	AABSEngine::Core::Matrix4 mat;

	mat.ExtractTransform(GetOrientation(), GetWorldPosition());

	worldDirect = mat.ObjectToWorld(localDirect);
}
			
void AABSEngine::Physics::RigidBody::WorldToBodyDirection(const AABSEngine::Core::Vector3& worldDirect, AABSEngine::Core::Vector3& localDirect)
{
	AABSEngine::Core::Matrix4 mat;

	mat.ExtractTransform(GetOrientation(), GetWorldPosition());

	localDirect = mat.WorldToObject(worldDirect);
}

void AABSEngine::Physics::RigidBody::BodyToWorldPoint(const AABSEngine::Core::Point3& localPoint, AABSEngine::Core::Point3& worldPoint)
{
	AABSEngine::Core::Matrix4 mat;

	mat.ExtractTransform(GetOrientation(), GetWorldPosition());

	worldPoint = mat.ObjectToWorld(localPoint);
}
			
void AABSEngine::Physics::RigidBody::WorldToBodyPoint(const AABSEngine::Core::Point3& worldPoint, AABSEngine::Core::Point3& localPoint)
{
	AABSEngine::Core::Matrix4 mat;

	mat.ExtractTransform(GetOrientation(), GetWorldPosition());

	localPoint = mat.WorldToObject(worldPoint);
}

Decimal AABSEngine::Physics::RigidBody::GetInverseMass()const
{
	return m_inverseMass;
}

Decimal AABSEngine::Physics::RigidBody::GetMass() const
{
	return m_mass;
}

void AABSEngine::Physics::RigidBody::SetMass(float in_mass)
{
	m_mass = in_mass;

	if(m_mass != 0)
	{
		m_inverseMass =  1.0 / m_mass;
	}
	else
	{
		m_inverseMass = 0.0;
	}
}

const AABSEngine::Core::Vector3& AABSEngine::Physics::RigidBody::GetLinearVelocity()const
{
	return m_linearVelocity;
}

void AABSEngine::Physics::RigidBody::SetLinearVelocity(const AABSEngine::Core::Vector3& in_velocity)
{
	m_linearVelocity = in_velocity;
}

const AABSEngine::Core::Vector3& AABSEngine::Physics::RigidBody::GetAngularVelocity()const
{
	return m_angularVelocity;
}

void AABSEngine::Physics::RigidBody::SetAngularVelocity(const AABSEngine::Core::Vector3& in_velocity)
{
	m_angularVelocity = in_velocity;
}

const AABSEngine::Core::Point3& AABSEngine::Physics::RigidBody::GetCOM()const
{
	return m_centerOfMass;
}

void AABSEngine::Physics::RigidBody::SetCOM(const AABSEngine::Core::Point3& in_com)
{
	m_centerOfMass = in_com;
}

void AABSEngine::Physics::RigidBody::SetMaterialID(int id)
{
	m_materialID = id;
}

int AABSEngine::Physics::RigidBody::GetMaterialID()const
{
	return m_materialID;
}

void AABSEngine::Physics::RigidBody::SetLinearAcceleration(const AABSEngine::Core::Vector3& accel)
{
	m_linearAcceleration = accel;
}

void AABSEngine::Physics::RigidBody::WorldInverseTensor(AABSEngine::Core::Matrix3& iWorldTensor)
{
	AABSEngine::Core::Matrix3 rot;
	rot.ExtractTransform(GetOrientation());

	//bodyTensor pre rotation
	Decimal m00 = m_inverseInertiaTensor[0][0] * rot[0][0] + m_inverseInertiaTensor[0][1] * rot[1][0] + m_inverseInertiaTensor[0][2] * rot[2][0];
	Decimal m01 = m_inverseInertiaTensor[0][0] * rot[0][1] + m_inverseInertiaTensor[0][1] * rot[1][1] + m_inverseInertiaTensor[0][2] * rot[2][1];
	Decimal m02 = m_inverseInertiaTensor[0][0] * rot[0][2] + m_inverseInertiaTensor[0][1] * rot[1][2] + m_inverseInertiaTensor[0][2] * rot[2][2];

	Decimal m10 = m_inverseInertiaTensor[1][0] * rot[0][0] + m_inverseInertiaTensor[1][1] * rot[1][0] + m_inverseInertiaTensor[1][2] * rot[2][0];
	Decimal m11 = m_inverseInertiaTensor[1][0] * rot[0][1] + m_inverseInertiaTensor[1][1] * rot[1][1] + m_inverseInertiaTensor[1][2] * rot[2][1];
	Decimal m12 = m_inverseInertiaTensor[1][0] * rot[0][2] + m_inverseInertiaTensor[1][1] * rot[1][2] + m_inverseInertiaTensor[1][2] * rot[2][2];

	Decimal m20 = m_inverseInertiaTensor[2][0] * rot[0][0] + m_inverseInertiaTensor[2][1] * rot[1][0] + m_inverseInertiaTensor[2][2] * rot[2][0];
	Decimal m21 = m_inverseInertiaTensor[2][0] * rot[0][1] + m_inverseInertiaTensor[2][1] * rot[1][1] + m_inverseInertiaTensor[2][2] * rot[2][1];
	Decimal m22 = m_inverseInertiaTensor[2][0] * rot[0][2] + m_inverseInertiaTensor[2][1] * rot[1][2] + m_inverseInertiaTensor[2][2] * rot[2][2];

	//rotation postmult mtx
	iWorldTensor[0][0] = rot[0][0] * m00 + rot[0][1] * m10 + rot[0][2] * m20;
	iWorldTensor[1][0] = rot[1][0] * m00 + rot[1][1] * m10 + rot[1][2] * m20;
	iWorldTensor[2][0] = rot[2][0] * m00 + rot[2][1] * m10 + rot[2][2] * m20;

	iWorldTensor[0][1] = rot[0][0] * m01 + rot[0][1] * m11 + rot[0][2] * m21;
	iWorldTensor[1][1] = rot[1][0] * m01 + rot[1][1] * m11 + rot[1][2] * m21;
	iWorldTensor[2][1] = rot[2][0] * m01 + rot[2][1] * m11 + rot[2][2] * m21;

	iWorldTensor[0][2] = rot[0][0] * m02 + rot[0][1] * m12 + rot[0][2] * m22;
	iWorldTensor[1][2] = rot[1][0] * m02 + rot[1][1] * m12 + rot[1][2] * m22;
	iWorldTensor[2][2] = rot[2][0] * m02 + rot[2][1] * m12 + rot[2][2] * m22;
}

const AABSEngine::Core::Vector3& AABSEngine::Physics::RigidBody::GetLinearAcceleration()const
{
	return m_linearAcceleration;
}

void AABSEngine::Physics::RigidBody::SetITensor(const AABSEngine::Core::Matrix3& tensor)
{
	m_inertiaTensor = tensor;
	m_inverseInertiaTensor = tensor.Inverse();
}
			
AABSEngine::Core::Matrix3 AABSEngine::Physics::RigidBody::GetInverseITensor()const
{
	return m_inertiaTensor.Inverse();
}

const AABSEngine::Core::Matrix3& AABSEngine::Physics::RigidBody::GetITensor()const 
{ 
	return m_inertiaTensor;
}

void AABSEngine::Physics::RigidBody::SetOrientation(const AABSEngine::Core::Quaternion& orient)
{
	if(m_physObject)
	{
		m_physObject->setOrientation(orient.X(), orient.Y(), orient.Z(), orient.W());
	}
}

AABSEngine::Core::Quaternion AABSEngine::Physics::RigidBody::GetOrientation()const
{
	AABSEngine::Core::Quaternion temp;

	if(m_physObject)
	{
		temp.Get().w = m_physObject->getWorldOrientation().w;
		temp.Get().x = m_physObject->getWorldOrientation().x;
		temp.Get().y = m_physObject->getWorldOrientation().y;
		temp.Get().z = m_physObject->getWorldOrientation().z;
		
		return temp;
	}

	return AABSEngine::Core::Quaternion(0,0,0,0);
}

void AABSEngine::Physics::RigidBody::SetWorldPosition(const AABSEngine::Core::Point3& worldPos)
{
	if(m_physObject)
	{
		m_physObject->setPosition(worldPos.X(), worldPos.Y(), worldPos.Z());
	}
}

AABSEngine::Core::Point3 AABSEngine::Physics::RigidBody::GetWorldPosition()const
{
	AABSEngine::Core::Point3 pos(0,0,0);

	if(m_physObject)
	{
		pos.xyz(m_physObject->getWorldPosition().x,
			m_physObject->getWorldPosition().y, 
			m_physObject->getWorldPosition().z);
	}
	return pos;
}

void RigidBody::AddForce(AABSEngine::Core::Vector3& force)
{
	m_forceAccum += force;
}

void RigidBody::AddForceAtPoint(AABSEngine::Core::Vector3& force, AABSEngine::Core::Point3& point)
{
    AABSEngine::Core::Vector3 lever(point - m_centerOfMass); /* get vector to center of mass */

    m_forceAccum += force;
    m_torqueAccum += lever.crossProduct(force);
}

void RigidBody::AddTorque(AABSEngine::Core::Vector3& torque)
{
	m_torqueAccum += torque;
}

const AABSEngine::Core::Vector3& AABSEngine::Physics::RigidBody::GetLinearMomentum()const
{
	return m_linearMomentum;
}
			
void AABSEngine::Physics::RigidBody::SetLinearMomentum(const AABSEngine::Core::Vector3& momentum)
{
	m_linearMomentum = momentum;
}

const AABSEngine::Core::Vector3& AABSEngine::Physics::RigidBody::GetAngularMomentum()const
{
	return m_angularMomentum;
}
	
void AABSEngine::Physics::RigidBody::SetAngularMomentum(const AABSEngine::Core::Vector3& momentum)
{
	m_angularMomentum = momentum;
}

void AABSEngine::Physics::RigidBody::ClearAccumulators()
{
	m_forceAccum.xyz(0,0,0);
	m_torqueAccum.xyz(0,0,0);
}

void AABSEngine::Physics::RigidBody::SetVelocityThreshold(float linear, float angular)
{
	m_minLinearVelocityMagnitude = linear;
	m_minAngularVelocityMagnitude = angular;
}

float AABSEngine::Physics::RigidBody::GetLinearVelocityThreshold()
{
	return m_minLinearVelocityMagnitude;
}

float AABSEngine::Physics::RigidBody::GetAngularVelocityThreshold()
{
	return m_minAngularVelocityMagnitude;
}

bool AABSEngine::Physics::RigidBody::IsAsleep()
{
	return m_sleep;
}

void AABSEngine::Physics::RigidBody::Sleep()
{
	m_sleep = true;
	m_linearVelocity = AABSEngine::Core::Vector3(0,0,0); //set velocity to zero
	m_angularVelocity = AABSEngine::Core::Vector3(0,0,0);
}

void AABSEngine::Physics::RigidBody::Awaken()
{
	m_sleep = false;
}

void AABSEngine::Physics::RigidBody::SetPreviousWorldPosition(const AABSEngine::Core::Point3 &pp)
{
	m_previousPosition = pp;
}

AABSEngine::Core::Point3 AABSEngine::Physics::RigidBody::GetPreviousWorldPosition() const
{
	return m_previousPosition;
}