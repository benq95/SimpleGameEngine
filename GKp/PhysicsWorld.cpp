#include "stdafx.h"
#include "PhysicsWorld.h"


PhysicsWorld::PhysicsWorld()
{
}


PhysicsWorld::~PhysicsWorld()
{
}

void PhysicsWorld::init()
{
	//  physic word initalization
	btBroadphaseInterface* broadphase = new btDbvtBroadphase();
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
	world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	world->setGravity(btVector3(0, -1, 0));

}
void PhysicsWorld::clear()
{
	//world->clearForces();
	
	delete world;
	world = NULL;
	init();
}

void PhysicsWorld::update(double deltaTime)
{
	world->stepSimulation(1 / deltaTime / 190, 10);
	//world->rayTest(btVector3(0, 0, 0), btVector3(0, 0, 0), null);
	btVector3  cameraTarget = cameraPos + cameraFront*100;

	btCollisionWorld::ClosestRayResultCallback res(cameraPos, cameraTarget);

	world->rayTest(cameraPos, cameraTarget, res); // m_btWorld is btDiscreteDynamicsWorld

	if (res.hasHit()) {
		//printf("Collision at: <%.2f, %.2f, %.2f>\n", res.m_hitPointWorld.getX(), res.m_hitPointWorld.getY(), res.m_hitPointWorld.getZ());
		rayTest->setPosition(glm::vec3(res.m_hitPointWorld.getX(), res.m_hitPointWorld.getY(), res.m_hitPointWorld.getZ()));
	}

}

void PhysicsWorld::addPhysicalObject(PhysicalObject * phyobj)
{
	if (world != NULL) {
		world->addRigidBody(phyobj->getRigidBody());
		
	}
}

void PhysicsWorld::setCameraPos(glm::vec3 cameraPos)
{
	this->cameraPos = btVector3(cameraPos.x, cameraPos.y, cameraPos.z);
}

void PhysicsWorld::setCameraFront(glm::vec3 cameraFront)
{
	this->cameraFront = btVector3(cameraFront.x, cameraFront.y, cameraFront.z);
}

void PhysicsWorld::setReyTestObj(AbstractGameObject * rayTest)
{
	this->rayTest=rayTest;
}

