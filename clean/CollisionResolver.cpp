#include "StdAfx.h"
#include "CollisionResolver.h"

void AABSEngine::Physics::CollisionResolver::ResolveCollision(const Core::Point3 &contactA, const Core::Point3 &contactB, const Core::Vector3 &contactNormal, Core::GameObject *objectA, Core::GameObject *objectB)
{
	//get the rigid bodies
	Physics::RigidBody *rb1 = objectA->GetPhysicsObject();
	Physics::RigidBody *rb2 = objectB->GetPhysicsObject();

	//get the linear velocities
	Core::Vector3 v1 = rb1->GetLinearVelocity(); //v1
	Core::Vector3 v2 = rb2->GetLinearVelocity(); //v2

	//get the angular velocities
	Core::Vector3 w1 = rb1->GetAngularVelocity(); //w1
	Core::Vector3 w2 = rb2->GetAngularVelocity(); //w2

	//get the inverse mass of the objects
	float inverseMass1 = rb1->GetInverseMass(); // 1 / mass1
	float inverseMass2 = rb2->GetInverseMass(); // 1 / mass2

	//get the distance of the contact point from the center of mass of each object and add to 'position'
	Core::Vector3 com1WorldTransform(rb1->GetWorldPosition() + rb1->GetCOM());
	Core::Vector3 com2WorldTransform(rb2->GetWorldPosition() + rb2->GetCOM());

	//calculate contact points in local coordinate
	Core::Vector3 r1(contactA - com1WorldTransform); //r1
	Core::Vector3 r2(contactB - com2WorldTransform); //r2

	//get the epsilon from a look up table based on object a and b material
	float coeffOfRestitution = 0.6f; // TODO temporary value
	//int coeffOfRestitution = LookUpTable[rb1->GetMaterialID()][rb2->GetMaterialID()];

	//calculate linear impulse (undivided by the mass)
	Core::Vector3 impulse(0,0,0);

	//find torque generated per unit impulse (impulsive torque)
	Core::Vector3 r1CrossN = r1.crossProduct(contactNormal); //(r1 x n)
	Core::Vector3 r2CrossN = r2.crossProduct(contactNormal); //(r2 x n)

	//n * -(1 + epsilon) * (n.(v1-v2) + w1.(r1 x n) - w2 (r2 x n))
	impulse =  contactNormal * -(1 + coeffOfRestitution) * (contactNormal.dotProduct(v1-v2) + w1.dotProduct(r1CrossN) - w2.dotProduct(r2CrossN)); //top part

	//find change in angular velocity per unit of impulsive torque
	Core::Vector3 jInvMultRCrossN1 = rb1->GetInverseITensor().ObjectToWorld(r1CrossN); // J1_inverse * (r1 x n)

	//find change in angular velocity per unit impulsive torque
	Core::Vector3 jInvMultRCrossN2 = rb2->GetInverseITensor().ObjectToWorld(r2CrossN); // J2_inverse * (r2 x n)

	float bottomPart1Value = r1CrossN.dotProduct(jInvMultRCrossN1); // (r1 x n) * J1_inverse * (r1 x n)
	float bottomPart2Value = r2CrossN.dotProduct(jInvMultRCrossN2); // (r2 x n) * J2_inverse * (r2 x n)
	float bottomPartFinalValue = (inverseMass1 + inverseMass2) + (bottomPart1Value + bottomPart2Value); // 1/m1 + 1/m2 + (r1 x n) * J1_inverse * (r1 x n) + (r2 x n) * J2_inverse * (r2 x n)

	//calculate the final impulse
	if(bottomPartFinalValue > 0.0f)
	{
		impulse /= bottomPartFinalValue;

		//check if this object is static
		if(rb1->IsStatic() == false && rb1->IsKinematic() == false)
		{
			bool sleep = true;

			Core::Vector3 v1_final = v1 + (impulse * inverseMass1); // v1 + impulse / mass
			Core::Vector3 w1_final = w1 + jInvMultRCrossN1 * impulse.magnitude(); //w1_final = w1 + |impulse| * inverseInertiaTensor1 * (r1 x contactNormal)

			rb1->SetLinearVelocity(Core::Vector3(0,0,0));
			rb1->SetAngularVelocity(Core::Vector3(0,0,0));
			if((v1_final.magnitude()) >= rb1->GetLinearVelocityThreshold()) //check against the linear velocity threshold
			{
				rb1->SetLinearVelocity(v1_final);
				sleep = false;
			}
			if((w1_final.magnitude()) >= rb1->GetAngularVelocityThreshold()) //check against angular velocity threshold
			{
				rb1->SetAngularVelocity(w1_final);
				sleep = false;
			}

			if(sleep)
			{
				rb1->Sleep();
			}
			else
			{
				rb1->Awaken();
			}
		}

		//check if this object is static
		if(rb2->IsStatic() == false && rb2->IsKinematic() == false)
		{
			bool sleep = true;

			Core::Vector3 v2_final = v2 - (impulse * inverseMass2); // v2 + impulse / mass
			Core::Vector3 w2_final = w2 - jInvMultRCrossN2 * impulse.magnitude(); //w2_final = w2 + |impulse| * inverseInertiaTensor2 * (r2 x contactNormal)

			rb2->SetLinearVelocity(Core::Vector3(0,0,0));
			rb2->SetAngularVelocity(Core::Vector3(0,0,0));
			if((v2_final.magnitude()) >= rb2->GetLinearVelocityThreshold()) //check against the linear velocity threshold
			{
				rb2->SetLinearVelocity(v2_final);
				sleep = false;
			}
			if((w2_final.magnitude()) >= rb2->GetAngularVelocityThreshold()) //check against angular velocity threshold
			{
				rb2->SetAngularVelocity(w2_final);
				sleep = false;
			}

			if(sleep)
			{
				rb2->Sleep();
			}
			else
			{
				rb2->Awaken();
			}
		}
	}
}