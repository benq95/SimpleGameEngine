#pragma once
#include <btBulletDynamicsCommon.h>
///<summary>
/// klasa odpowiadajaca za tworzenie cial fizycznych
///</summary>
class RigidBodySimpleFactory
{
public:
	RigidBodySimpleFactory();
	~RigidBodySimpleFactory();
	static btRigidBody* createRigidBody(std::string type,btTransform tr);
private:
	static btRigidBody* createBrickRigidBody(btTransform tr);
	static btRigidBody* createBallRigidBody(btTransform tr);

};

