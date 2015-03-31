#include "StdAfx.h"
#include "CompoundObject.h"

AABSEngine::Physics::CompoundObject::CompoundObject()
{
	m_inertiaTensor.SetInertiaTensor(0,0,0,0,0,0);
	m_centerOfMass = Core::Point3(0,0,0);
	m_mass = 0;
	m_static = false;
}

AABSEngine::Physics::CompoundObject::~CompoundObject()
{
}

float AABSEngine::Physics::CompoundObject::GetMass()
{
	return m_mass;
}

AABSEngine::Core::Matrix3 AABSEngine::Physics::CompoundObject::GetInertiaTensor()
{
	return m_inertiaTensor;
}

AABSEngine::Core::Point3 AABSEngine::Physics::CompoundObject::GetCenterOfMass()
{
	return m_centerOfMass;
}

bool AABSEngine::Physics::CompoundObject::GetIsStatic()
{
	return m_static;
}

bool AABSEngine::Physics::CompoundObject::GetIsKinematic()
{
	return m_kinematic;
}

OgreBulletCollisions::CollisionShape *AABSEngine::Physics::CompoundObject::CreateOgreBTCompoundShape()
{
	OgreBulletCollisions::CompoundCollisionShape *compound = new OgreBulletCollisions::CompoundCollisionShape();
	
	//add the child shapes
	for(int i=0; i<m_shapeList.size(); i++)
	{
		AABSEngine::Physics::CompoundChildObjectData *childObject = m_shapeList[i];
		OgreBulletCollisions::CollisionShape *childShape = childObject->m_object->CreateOgreBTShape();

		compound->addChildShape(childShape, Ogre::Vector3(childObject->m_position.X(), childObject->m_position.Y(), childObject->m_position.Z()), Ogre::Quaternion(childObject->m_orientation.W(),childObject->m_orientation.X(),childObject->m_orientation.Y(),childObject->m_orientation.Z()));
	}

	return compound;
}

void AABSEngine::Physics::CompoundObject::AddChildShape(AABSEngine::Physics::CollisionObject *obj, Core::Point3 pos, Core::Quaternion localOrientation)
{
	AABSEngine::Physics::CompoundChildObjectData *childObject = new AABSEngine::Physics::CompoundChildObjectData();
	childObject->m_object = obj;
	childObject->m_position = pos;
	childObject->m_orientation = localOrientation;

	m_shapeList.push_back(childObject);
}

void AABSEngine::Physics::CompoundObject::SetupPhysics(bool isStatic, bool isKinematic)
{
	m_static = isStatic;
	m_kinematic = isKinematic;
	if(!isStatic)
	{
		AABSEngine::Utility::ITensorCombiner combiner;
		combiner.ClearITensors(); //initialize the itensor combiner

		//loop through all of the compound child objects and calculate the combined inertia tensor
		for(int i=0; i<m_shapeList.size(); i++)
		{
			AABSEngine::Physics::CompoundChildObjectData *childObject = m_shapeList[i];
			combiner.AddData(childObject->m_object->GetInertiaTensor(), childObject->m_position, childObject->m_object->GetMass());
		}

		//get the combined inertia tensor
		combiner.CombineITensors();
		m_inertiaTensor = combiner.GetFinalITensor();

		//get the combined center of mass
		m_centerOfMass = combiner.GetFinalCOG();

		//shifts all of the child objects based on the new center of mass
		//new position = current position - combinedCOM
		for(int i=0; i<m_shapeList.size(); i++)
		{
			AABSEngine::Physics::CompoundChildObjectData *childObject = m_shapeList[i];
			Core::Vector3 newPosition = childObject->m_position - m_centerOfMass;
			childObject->m_position = Core::Point3(newPosition.X(), newPosition.Y(), newPosition.Z());
		}

		//set the mass
		m_mass = combiner.CalculateTotalMass();
	}
}

void AABSEngine::Physics::CompoundObject::SetLinearDamping(float damping)
{
	m_linearDamping = damping;
}

float AABSEngine::Physics::CompoundObject::GetLinearDamping()
{
	return m_linearDamping;
}

void AABSEngine::Physics::CompoundObject::SetAngularDamping(float damping)
{
	m_angularDamping = damping;
}

float AABSEngine::Physics::CompoundObject::GetAngularDamping()
{
	return m_angularDamping;
}

void AABSEngine::Physics::CompoundObject::SetVelocityThreshold(float linear, float angular)
{
	m_linearThreshold = linear;
	m_angularThreshold = angular;
}

float AABSEngine::Physics::CompoundObject::GetLinearThreshold()
{
	return m_linearThreshold;
}

float AABSEngine::Physics::CompoundObject::GetAngularThreshold()
{
	return m_angularThreshold;
}