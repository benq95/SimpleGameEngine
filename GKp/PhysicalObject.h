#pragma once
#include "SimpleObject.h"
#include <btBulletDynamicsCommon.h>
#include "RigidBodySimpleFactory.h"
//#include "PhysicsWorld.h"

///<summary>
/// klasa rozszerzajaca klase SimpleObject 
/// posiada dodatkowe pole opisujace ksztalt oraz wlasciwosci obiektu fizycznego
///</summary>
class PhysicalObject :
	public SimpleObject
{
public:
	PhysicalObject(glm::vec3 position, Shader* shader, Texture texture, VaoObject * vao);
	PhysicalObject(glm::vec3 position, Shader* shader, Texture texture, VaoObject * vao,btRigidBody * rigBody);
	PhysicalObject(glm::vec3 position, Shader* shader, Texture texture, VaoObject * vao, std::string rigidBodyType);
	PhysicalObject(glm::mat4 transform, Shader* shader, Texture texture, VaoObject * vao, std::string rigidBodyType);// , PhysicsWorld *world);
	PhysicalObject(glm::vec3 position, Shader* shader, Texture texture, VaoObject * vao, std::string rigidBodyType, glm::vec3 dir);
	//PhysicalObject(glm::mat4 transform, Shader* shader, Texture texture, VaoObject * vao, std::string rigidBodyType, glm::vec3 dir);// , PhysicsWorld *world);

	PhysicalObject();
	~PhysicalObject();
	btRigidBody * getRigidBody();
	void setRigidBody(btRigidBody * ridigBody);
	void setCollisionShape(btCollisionShape * collisionShape);
	void update();
	//virtual std::string toString();
	virtual void toXml(XMLDocument * xmlDoc);
	void setRigidBodyType(std::string type);
private:
	btRigidBody* rigidBody;
	std::string rigidBodyType;
};

