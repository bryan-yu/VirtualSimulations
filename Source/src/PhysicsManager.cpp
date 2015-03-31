#include "StdAfx.h"
#include "PhysicsManager.h"
#include "RigidBody.h"
#include "Object.h"
#include "PenetrationResolver.h"
#include "CollisionResolver.h"
#include "ITensorCalculator.h"
#include "Manifold.h"
#include "OgreBulletCollisionsCompoundShape.h"
#include "GameObjectManager.h"
#include "Singleton.h"

AABSEngine::Physics::PhysicsManager* AABSEngine::Physics::PhysicsManager::m_singleton = NULL;

AABSEngine::Physics::PhysicsManager::PhysicsManager()
{
	//setup physics
	m_collisionWorld = NULL;
	timeAccumulator = 0;
}

AABSEngine::Physics::PhysicsManager* AABSEngine::Physics::PhysicsManager::Instance()
{
	if(m_singleton == NULL)
	{
		m_singleton = new AABSEngine::Physics::PhysicsManager();
	}

	return m_singleton;
}

void AABSEngine::Physics::PhysicsManager::SetupPhysicsWorld(Ogre::SceneManager *mgr, int minx, int miny, int minz, int maxx, int maxy, int maxz)
{
	//setup physics
	m_collisionWorld = new OgreBulletCollisions::CollisionsWorld(mgr, Ogre::AxisAlignedBox(minx, miny, minz, maxx, maxy, maxz));
	m_collisionWorld->getBulletCollisionWorld()->getDispatchInfo().m_useContinuous = true;

	m_forceRegistry = new ForceRegistry();
}

void AABSEngine::Physics::PhysicsManager::AddSceneObject(AABSEngine::Core::GameObject *gameObject, Ogre::Entity *entity)
{
	//mesh converter
	OgreBulletCollisions::StaticMeshToShapeConverter meshConverter;
	meshConverter.addEntity(entity);

	//setup collision object
	OgreBulletCollisions::Object *collisionObject = new OgreBulletCollisions::Object(gameObject->GetName(), m_collisionWorld, true);
	OgreBulletCollisions::CollisionShape *cShape = (OgreBulletCollisions::CollisionShape*)meshConverter.createTrimesh(); //create trimesh collision shape from ogrebullet staticmesh to shape converter
			
	collisionObject->setShape(cShape, Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
	collisionObject->setPosition(gameObject->GetSceneNode()->getPosition());

	//create physics object
	AABSEngine::Physics::RigidBody *pObj = new AABSEngine::Physics::RigidBody(collisionObject, 0);
	Core::Matrix3 zeroMatrix;
	zeroMatrix.SetInertiaTensor(0,0,0,0,0,0);
	pObj->SetITensor(zeroMatrix);
	collisionObject->getBulletObject()->setUserPointer(gameObject); //add reference to the game object

	pObj->SetStatic(true); //make it static object
	pObj->SetAngularDamping(0);
	pObj->SetLinearDamping(0);

	//add the physics object to the game object for reference
	gameObject->SetPhysicsObject(pObj);

	//add to the collision world
	m_collisionWorld->addObject(collisionObject, CollisionMask::COL_ENVIRONMENT, Physics::ENV_COLLISION_FILTER);
	m_physicsObjectList.push_back(pObj);
}

void AABSEngine::Physics::PhysicsManager::AddObject(AABSEngine::Core::GameObject *gObj, std::string selectedCollisionObject, Core::Point3 initPosition, Core::Quaternion initRotation, int collisionGroup, int collisionFilter)
{
	//get the selected compound object
	Physics::CompoundObject *compound = m_predefinedObjects[selectedCollisionObject];

	//translate the gameobject wrapper node to center of mass
	Ogre::SceneNode *wrapperNode = gObj->GetSceneNode();
	if(wrapperNode != NULL)
	{
		wrapperNode->translate(compound->GetCenterOfMass().X(), compound->GetCenterOfMass().Y(), compound->GetCenterOfMass().Z());
		wrapperNode->getChild(0)->translate(compound->GetCenterOfMass().X() * -1, compound->GetCenterOfMass().Y() * -1, compound->GetCenterOfMass().Z() * -1);
	}

	OgreBulletCollisions::Object *collisionObject = new OgreBulletCollisions::Object(gObj->GetName(), m_collisionWorld, true);
	OgreBulletCollisions::CollisionShape *cShape = compound->CreateOgreBTCompoundShape(); //create a new bullet ogre compound shape
	
	//setup the necessary ogre bt collision object parameters
	collisionObject->setShape(cShape, Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
	collisionObject->getBulletObject()->setUserPointer(gObj);

	if(wrapperNode != NULL)
	{
		//match the physics object position - only at initialization: scene node position will follow the rigid body object later on
		collisionObject->setPosition(gObj->GetSceneNode()->getPosition());
		collisionObject->setOrientation(gObj->GetSceneNode()->getOrientation());
	}
	else
	{
		collisionObject->setPosition(Ogre::Vector3(initPosition.X(), initPosition.Y(), initPosition.Z()));
		collisionObject->setOrientation(Ogre::Quaternion(initRotation.W(), initRotation.X(), initRotation.Y(), initRotation.Z()));
	}

	//any other initial transformation
	if(wrapperNode != NULL)
	{
		wrapperNode->translate(initPosition.X(), initPosition.Y(), initPosition.Z());
		wrapperNode->rotate(Ogre::Quaternion(initRotation.W(), initRotation.X(), initRotation.Y(), initRotation.Z()));
	}

	//rotation 'error' somewhere here...
	btQuaternion btQuat(0,0,0,1);
	if(initRotation.X() != 0 || initRotation.Y() != 0 || initRotation.Z() != 0)
	{
		btQuat.setRotation(btVector3(initRotation.X(), initRotation.Y(), initRotation.Z()), initRotation.W());
	}
	collisionObject->setTransform(btVector3(initPosition.X(), initPosition.Y(),initPosition.Z()), btQuat);

	//create physics object
	AABSEngine::Physics::RigidBody *pObj = new AABSEngine::Physics::RigidBody(collisionObject, compound->GetMass());
	pObj->SetStatic(compound->GetIsStatic()); //set static true/false
	pObj->SetKinematic(compound->GetIsKinematic()); //set kinematic true/false
	pObj->SetITensor(compound->GetInertiaTensor()); //set inertia tensor
	pObj->SetAngularDamping(compound->GetAngularDamping()); //set angular damping
	pObj->SetLinearDamping(compound->GetLinearDamping()); //set linear damping
	pObj->SetVelocityThreshold(compound->GetLinearThreshold(), compound->GetAngularThreshold()); //set velocity threshold for the jitter hack

	gObj->SetPhysicsObject(pObj);  //set the rigid body as a component to game object

	//add to the collision world
	m_collisionWorld->addObject(collisionObject, collisionGroup, collisionFilter);
	m_physicsObjectList.push_back(pObj);
}

void AABSEngine::Physics::PhysicsManager::Integrate(AABSEngine::Core::GameObject* gObj, Decimal deltaTime)
{
	//retrieve rigid body object
	Physics::RigidBody* rigidBody = gObj->GetPhysicsObject();

	if(rigidBody->IsAsleep() == false)
	{
		//get current position of underlying rigid body
		Core::Point3 position(rigidBody->GetCollisionObject()->getWorldPosition().x, rigidBody->GetCollisionObject()->getWorldPosition().y, rigidBody->GetCollisionObject()->getWorldPosition().z);
		rigidBody->SetPreviousWorldPosition(position); //set previous position

		//get inverse inertia tensor converted to world matrix 
		Core::Matrix3 worldITensor;
		rigidBody->WorldInverseTensor(worldITensor);

		//calculate accelerations for the current frame (linearAccel = force / mass) && (angularAccel = torque / I)
		Core::Vector3 linearAccel = rigidBody->GetLinearAcceleration() + (rigidBody->GetForceAccum() * rigidBody->GetInverseMass()); // we know F = m * a. Therefore a = F / m
		Core::Vector3 angularAccel = worldITensor.ObjectToWorld(rigidBody->GetTorqueAccum());

		//linear velocity components
		Core::Vector3 u = rigidBody->GetLinearVelocity(); //initial velocity u
		rigidBody->AddLinearVelocity(linearAccel, deltaTime); //v = u + at
		Core::Vector3 v = rigidBody->GetLinearVelocity(); //grab the final velocity

		Core::Vector3 displacement = (u + v) * deltaTime * 0.5; //calculate the displacement using s = (u + v) * t * 0.5
		Core::Point3 newPosition = position + displacement;
		rigidBody->SetWorldPosition(newPosition);

		//calculate angular velocity component
		AABSEngine::Core::Quaternion orientation(rigidBody->GetCollisionObject()->getWorldOrientation());
		rigidBody->AddAngularVelocity(angularAccel, deltaTime);
		orientation.AddScaledVector(rigidBody->GetAngularVelocity(), deltaTime);
		rigidBody->SetOrientation(orientation);

		//update graphics representation
		Ogre::SceneNode* sceneNode = gObj->GetSceneNode();
		if(sceneNode != NULL)
		{
			sceneNode->setPosition(newPosition.X(), newPosition.Y(), newPosition.Z());
			sceneNode->setOrientation(rigidBody->GetOrientation().W(), rigidBody->GetOrientation().X(), rigidBody->GetOrientation().Y(), rigidBody->GetOrientation().Z());
		}
	}

	//adjustments to the rigid body parameters
	rigidBody->ClearAccumulators(); //clear force accumulators
	rigidBody->ApplyVelocityDamping(deltaTime); //apply velocity damping (for friction-like behaviour)
}

void AABSEngine::Physics::PhysicsManager::Update(Decimal deltaTime)
{
	if (!m_collisionWorld) { return; }

	//check time
	timeAccumulator += deltaTime;
	if(timeAccumulator < DESIRED_TIMESTEP) { return; }

	//reset timeAccumulator - skipping frames if delta time is simply too big
	while(timeAccumulator > DESIRED_TIMESTEP)
	{
		timeAccumulator -= DESIRED_TIMESTEP; //as if using modulus operator
	}

	deltaTime = DESIRED_TIMESTEP; //always make deltaTime to be using desired timestep

    // update here or after collision check? - doesn't matter as this only affect first frame I guess
	if (m_forceRegistry != NULL) { m_forceRegistry->Update(deltaTime); }

	CollisionDetection();

	PenetrationCalculation();

	Integrate(deltaTime);
}

void AABSEngine::Physics::PhysicsManager::CalculateInertiaAndCOG(AABSEngine::Physics::RigidBody *physObject, OgreBulletCollisions::StaticMeshToShapeConverter &meshConverter)
{
	//get all of the vertices used in the meshconverter information
	int totalVertices = meshConverter.getVertexCount();
	if(totalVertices < 1)
	{
		return;
	}
	
	//filter all of the duplicate
	const Ogre::Vector3 *temp = meshConverter.getVertices();
	std::vector<AABSEngine::Core::Vector3> verticesList;
	for(int i=0; i<totalVertices; i++)
	{
		//get the vertex data
		AABSEngine::Core::Vector3 vect(temp->x, temp->y, temp->z);

		//check if there is a duplicate
		bool exist = false;
		for(int j=0; j<verticesList.size(); j++)
		{
			if(vect == verticesList[j])
			{
				exist = true;
				break;
			}
		}

		if(!exist)
		{
			verticesList.push_back(vect);
		}

		temp++;
	}

	//calculating the inertia tensor
	AABSEngine::Utility::ITensorCalculator tensorAlgorithm;
	tensorAlgorithm.SetVertices(verticesList);
	tensorAlgorithm.SetBodyMass(physObject->GetMass());
	tensorAlgorithm.CalculateITensor();

	//set the physics rigid body center of mass
	physObject->SetCOM(tensorAlgorithm.GetBodyCOM());
	Core::GameObject *gObj = (Core::GameObject *)physObject->GetCollisionObject()->getBulletObject()->getUserPointer();
}

bool AABSEngine::Physics::PhysicsManager::AddForceGenerator(std::string name, AABSEngine::Physics::ForceGenerator* gen)
{
  if (m_forceGeneratorMap.find(name) != m_forceGeneratorMap.end())
    return false;
  else
    m_forceGeneratorMap[name] = gen;
  return true;
}

bool AABSEngine::Physics::PhysicsManager::RegisterRigidBodyWithForceGenerator(std::string name, AABSEngine::Physics::RigidBody* body)
{
  if (m_forceGeneratorMap.find(name) == m_forceGeneratorMap.end())
    return false;
  else
    m_forceRegistry->RegisterForce(m_forceGeneratorMap[name], body);
  return true;
}

bool AABSEngine::Physics::PhysicsManager::DeregisterRigidBodyFromForceGenerator(std::string name, AABSEngine::Physics::RigidBody* body)
{
  if (m_forceGeneratorMap.find(name) == m_forceGeneratorMap.end())
    return false;
  else
	  m_forceRegistry->DeRegisterForce(m_forceGeneratorMap[name], body);
  return true;
}

//temporarily here as not used anywhere else (for now)...
//converts degree and axes values to quaternion values
void AABSEngine::Physics::PhysicsManager::ConvertToQuaternion(float &w, float &x, float &y, float &z)
{
	float angle = w;
	w = cos(Ogre::Degree(angle).valueRadians()/2.0);
	x = x*sin(Ogre::Degree(angle).valueRadians()/2.0);
	y = y*sin(Ogre::Degree(angle).valueRadians()/2.0);
	z = z*sin(Ogre::Degree(angle).valueRadians()/2.0);
}

void AABSEngine::Physics::PhysicsManager::InitialiseAllObjects(std::string xmlFile)
{
	pugi::xml_document xDoc;
	if(!xDoc.load_file(xmlFile.c_str()))
	{
		return;
	}

	pugi::xml_node objectNodes = xDoc.child("Objects");
	for (pugi::xml_node obj = objectNodes.first_child(); obj; obj = obj.next_sibling())
	{
		AABSEngine::Physics::CompoundObject *compound = new AABSEngine::Physics::CompoundObject();

		//get the name of the object
		std::string name = obj.child_value("Name");

		pugi::xml_node colShapes = obj.child("CollisionShapes");

		bool staticObject = false;
		std::string static_attribute = colShapes.attribute("static").value(); 
		if(static_attribute == "true")
		{
			staticObject = true;
		}

		bool kinematicObject = false;
		std::string kinematic = obj.child_value("Kinematic");
		if(kinematic == "true")
		{
			kinematicObject = true;
		}

		//get the damping
		std::string str_lDamping = colShapes.attribute("linearDamping").value(); float linearDamping = atof(str_lDamping.c_str());
		std::string str_aDamping = colShapes.attribute("angularDamping").value(); float angularDamping = atof(str_aDamping.c_str());

		//get the velocity threshold
		std::string str_lThreshold = colShapes.attribute("linearThreshold").value(); float linearThreshold = atof(str_lThreshold.c_str());
		std::string str_aThreshold = colShapes.attribute("angularThreshold").value(); float angularThreshold = atof(str_aThreshold.c_str());


		for (pugi::xml_node colShape = colShapes.first_child(); colShape; colShape = colShape.next_sibling())
		{
			std::string type = colShape.attribute("type").value(); 
			std::string str_mass = colShape.attribute("mass").value(); //mass in kg
			float mass = atof(str_mass.c_str());
			
			std::string str_pos_x = colShape.child("Position").attribute("x").value(); 
			std::string str_pos_y = colShape.child("Position").attribute("y").value(); 
			std::string str_pos_z = colShape.child("Position").attribute("z").value(); 
			float posx = atof(str_pos_x.c_str());
			float posy = atof(str_pos_y.c_str());
			float posz = atof(str_pos_z.c_str());

			float quatw = 0;
			float quatx = 0;
			float quaty = 0;
			float quatz = 0;

			int orientCount = 0;

			pugi::xml_node  orientNodes = colShape.child("Orientations");
			for(pugi::xml_node colOrient = orientNodes.first_child(); colOrient; colOrient = colOrient.next_sibling())
			{
				float tempQuatwB = colOrient.attribute("w").as_float();
				float tempQuatxB = colOrient.attribute("x").as_float();
				float tempQuatyB = colOrient.attribute("y").as_float();
				float tempQuatzB = colOrient.attribute("z").as_float();

				float angle = 0.0;

				//more than one rotation?
				if(orientCount>0)
				{
					ConvertToQuaternion(tempQuatwB, tempQuatxB, tempQuatyB, tempQuatzB);

					float tempQuatwA = quatw;
					float tempQuatxA = quatx;
					float tempQuatyA = quaty;
					float tempQuatzA = quatz;

					//quaternion rotation addition...
					quatw=(tempQuatwA*tempQuatwB)-(tempQuatxA*tempQuatxB)-(tempQuatyA*tempQuatyB)-(tempQuatzA*tempQuatzB);
					quatx=(tempQuatwA*tempQuatxB)+(tempQuatxA*tempQuatwB)+(tempQuatyA*tempQuatzB)-(tempQuatzA*tempQuatyB);
					quaty=(tempQuatwA*tempQuatyB)+(tempQuatyA*tempQuatwB)+(tempQuatzA*tempQuatxB)-(tempQuatxA*tempQuatzB);
					quatz=(tempQuatwA*tempQuatzB)+(tempQuatzA*tempQuatwB)+(tempQuatxA*tempQuatyB)-(tempQuatyA*tempQuatxB);
				}
				else
				{
					quatw = tempQuatwB;
					quatx = tempQuatxB;
					quaty = tempQuatyB;
					quatz = tempQuatzB;

					ConvertToQuaternion(quatw, quatx, quaty, quatz);
				}

				orientCount++;
			}

			//check for the type
			if(type == "box")
			{
				//do box operation here
				std::string str_width = colShape.child_value("Width");
				std::string str_length = colShape.child_value("Length");
				std::string str_height = colShape.child_value("Height");
				float width = atof(str_width.c_str());
				float length = atof(str_length.c_str());
				float height = atof(str_height.c_str());

				Physics::CollisionBox *newBox = new Physics::CollisionBox(mass, width, height, length);
				compound->AddChildShape(newBox, Core::Point3(posx, posy, posz), Core::Quaternion(quatw, quatx, quaty, quatz));
			}
			else if(type == "cylinder")
			{
				//cylinder info extraction
				std::string str_radius = colShape.child_value("Radius");
				std::string str_height = colShape.child_value("Height");
				float radius = atof(str_radius.c_str());
				float height = atof(str_height.c_str());

				Physics::CollisionCylinder *newCylinder = new Physics::CollisionCylinder(mass, radius, height);
				compound->AddChildShape(newCylinder, Core::Point3(posx, posy, posz), Core::Quaternion(quatw, quatx, quaty, quatz));

			}
			else if(type == "sphere")
			{
				//sphere info extraction
				std::string str_radius = colShape.child_value("Radius");
				float radius = atof(str_radius.c_str());

				Physics::CollisionSphere *newSphere = new Physics::CollisionSphere(mass, radius);
				compound->AddChildShape(newSphere, Core::Point3(posx, posy, posz), Core::Quaternion::IDENTITY);
			}
		}

		//setup the physics
		compound->SetupPhysics(staticObject, kinematicObject);
		compound->SetLinearDamping(linearDamping);
		compound->SetAngularDamping(angularDamping);
		compound->SetVelocityThreshold(linearThreshold, angularThreshold);

		//add this compound shape to map
		m_predefinedObjects.insert(std::make_pair(name, compound));
	}
}

void AABSEngine::Physics::PhysicsManager::CollisionDetection()
{
	//do ogrebullet collision check
	m_collisionWorld->discreteCollide();

	//check the number of collisions
	for (int i=0;i<m_collisionWorld->getBulletCollisionWorld()->getDispatcher()->getNumManifolds();i++)
	{
		btPersistentManifold* contactManifold =  m_collisionWorld->getBulletCollisionWorld()->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obA = const_cast<btCollisionObject*>(contactManifold->getBody0());
		btCollisionObject* obB = const_cast<btCollisionObject*>(contactManifold->getBody1());

		AABSEngine::Core::GameObject *gObjA = (AABSEngine::Core::GameObject *)obA->getUserPointer(); //get the game object A
		AABSEngine::Core::GameObject *gObjB = (AABSEngine::Core::GameObject *)obB->getUserPointer(); //get the game object B

		std::vector<Core::Vector3> sumContactA;
		std::vector<Core::Vector3> sumContactB;
		std::vector<Core::Vector3> sumNormalOnB;
	
		int numContacts = contactManifold->getNumContacts();
		for (int j=0;j<numContacts;j++)
		{
			btManifoldPoint& pt = contactManifold->getContactPoint(j);

			if(pt.getDistance() < 0)
			{
				const btVector3& ptA = pt.getPositionWorldOnA(); //contact point of object 1
				const btVector3& ptB = pt.getPositionWorldOnB(); //contact point of object 2
				const btVector3& normalOnB = pt.m_normalWorldOnB; //contact normal in the direction of object 2

				Core::Point3 contactA(ptA.x(), ptA.y(), ptA.z()); //contact A in our engine Point3 data structure
				Core::Point3 contactB(ptB.x(), ptB.y(), ptB.z()); //contact B in our engine Point3 data structure
				Core::Vector3 contactNormal(normalOnB.x(), normalOnB.y(), normalOnB.z()); //contact normal in our engine Vector3 data structure

				//collision resolution - calculating impulse and settling the final velocities
				m_collisionFilter.Put(gObjA,gObjB,contactNormal,pt.getDistance(),contactA,contactB);
				
				sumContactA.push_back(contactA);
				sumContactB.push_back(contactB);
				sumNormalOnB.push_back(contactNormal);
			}
		}

		if(sumContactA.size() > 0)
		{
			//average all of the contact pairs
			Core::Vector3 avgContactA;
			Core::Vector3 avgContactB;
			Core::Vector3 avgNormalOnB;

			for(int i=0; i<sumContactA.size(); i++)
			{
				avgContactA += sumContactA[i];
				avgContactB += sumContactB[i];
				avgNormalOnB += sumNormalOnB[i];
			}

			avgContactA /= sumContactA.size();
			avgContactB /= sumContactB.size();
			avgNormalOnB /= sumNormalOnB.size();

			//add to averaged contact pairs
			AveragedContactPair avgPair;
			avgPair.m_objA = gObjA;
			avgPair.m_objB = gObjB;
			avgPair.m_contactNormal = avgNormalOnB;
			avgPair.m_contactA = avgContactA;
			avgPair.m_contactB = avgContactB;
			m_averagedContactPairs.push_back(avgPair);
		}
	}
}

void AABSEngine::Physics::PhysicsManager::PenetrationCalculation()
{
	AABSEngine::Physics::PResolver psolver;

	for(int i=0; i<m_collisionFilter.Items(); i++)
	{
		Manifold *item = m_collisionFilter[i];

		//add manifold to penetration resolver
		psolver.AddCollision(item->m_ob[0], item->m_ob[1], item->m_nB, item->m_pB, item->m_worldCP[0], item->m_worldCP[1]);
	}
	
	//resolve all current contact manifolds
	psolver.ResolveCollisions(psolver.TotalContacts());

	//do collision resolution based on the averaged contact points
	for(int i=0; i<m_averagedContactPairs.size(); i++)
	{
		AveragedContactPair avgPair = m_averagedContactPairs[i];

		//resolve impulses
		AABSEngine::Physics::CollisionResolver::ResolveCollision(avgPair.m_contactA, avgPair.m_contactB, avgPair.m_contactNormal, avgPair.m_objA, avgPair.m_objB);
	}

	//clear the filter
	m_collisionFilter.Empty(); 
	m_averagedContactPairs.clear();
}

void AABSEngine::Physics::PhysicsManager::Integrate(float deltaTime)
{
	//loop through all physics object
	std::vector<AABSEngine::Physics::RigidBody *>::iterator it = m_physicsObjectList.begin();
	while(it != m_physicsObjectList.end())
	{
		AABSEngine::Physics::RigidBody *pObj = *it;
		AABSEngine::Core::GameObject *gObj = (AABSEngine::Core::GameObject *)pObj->GetCollisionObject()->getBulletObject()->getUserPointer();

		//##if this is to be deleted
		if(gObj->ToBeRemoved())
		{
			//deregister all physics object
			m_forceRegistry->DeRegisterAllForces(gObj->GetPhysicsObject());

			//erase from the vector
			it = m_physicsObjectList.erase(it);

			m_collisionWorld->getBulletCollisionWorld()->removeCollisionObject(pObj->GetCollisionObject()->getBulletObject());
			m_collisionWorld->removeObject(pObj->GetCollisionObject()); //remove ogrebt object
			m_collisionWorld->getSceneManager()->getRootSceneNode()->removeChild(gObj->GetSceneNode()); //remove the graphics from scene manager

			AABSEngine::Core::Singleton<AABSEngine::Core::GameObjectManager>::Instance()->RemoveObject(gObj);
		}
		else
		{
			//update the movement for any objects with mass greater than 0
			if(pObj->IsStatic() == false)
			{				
				Integrate(gObj,deltaTime);		
			}

			it++;
		}
	}
}