#include "stdafx.h"
#include "RigidBodySimpleFactory.h"


RigidBodySimpleFactory::RigidBodySimpleFactory()
{
}


RigidBodySimpleFactory::~RigidBodySimpleFactory()
{
}

btRigidBody * RigidBodySimpleFactory::createRigidBody(std::string type, btTransform tr)
{
	if (type == "ball") {
		return createBallRigidBody(tr);
	}
	if (type == "brick") {
		return createBrickRigidBody(tr);
	}

}

btRigidBody * RigidBodySimpleFactory::createBrickRigidBody(btTransform tr)
{
	btDefaultMotionState* brickMotionState =
		new btDefaultMotionState(tr);
	btScalar mass = 1;
	btVector3 brickInertia(0, 0, 0);
	btCollisionShape* brickShape = new btBoxShape(btVector3(1, 0.5, 0.5));
	brickShape->calculateLocalInertia(mass, brickInertia);
	btRigidBody::btRigidBodyConstructionInfo brickRigidBodyCI(mass, brickMotionState, brickShape, brickInertia);

	btRigidBody * brickRigidBody = new btRigidBody(brickRigidBodyCI);
	brickRigidBody->setRestitution(0.7f);
	return brickRigidBody;
}

btRigidBody * RigidBodySimpleFactory::createBallRigidBody(btTransform tr)
{
	btDefaultMotionState* ballMotionState =
		new btDefaultMotionState(tr);
	btScalar mass = 1;
	btVector3 ballInertia(0, 0, 0);
	btCollisionShape* ballShape = new btSphereShape(1);
	ballShape->calculateLocalInertia(mass, ballInertia);
	btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI(mass, ballMotionState, ballShape, ballInertia);

	btRigidBody * ballRigidBody = new btRigidBody(ballRigidBodyCI);
	ballRigidBody->setRestitution(0.9f);
	return ballRigidBody;
}

