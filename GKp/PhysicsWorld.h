#pragma once

#include <btBulletDynamicsCommon.h>
#include <list>
#include "PhysicalObject.h"

class PhysicsWorld
{
public:
	PhysicsWorld();
	~PhysicsWorld();
	void init();
	void update(double deltaTime);
	void addPhyObj(PhysicalObject * phyobj);
	void setCameraPos(glm::vec3 cameraPos);
	void setCameraFront(glm::vec3 cameraFront);
	void setReyTestObj(AbstractGameObject * rayTest);
	void clear();
private:
	AbstractGameObject * rayTest;
	btVector3 cameraPos;
	btVector3 cameraFront;
	btDiscreteDynamicsWorld * world=NULL;

	
};

