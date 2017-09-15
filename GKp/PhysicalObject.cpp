#include "stdafx.h"
#include "PhysicalObject.h"


PhysicalObject::PhysicalObject(glm::vec3 position, Shader* shader, Texture texture, VaoObject * vao) : SimpleObject(position,  shader, texture,  vao)
{

}

PhysicalObject::PhysicalObject(glm::vec3 position, Shader* shader, Texture texture, VaoObject * vao, btRigidBody *rigBody): PhysicalObject(position,shader, texture,vao)
{
	setRigidBody(rigBody);
}

PhysicalObject::PhysicalObject(glm::vec3 position, Shader * shader, Texture texture, VaoObject * vao, std::string rigidBodyType) : PhysicalObject(position, shader, texture, vao)
{
	btTransform	tr;
	tr.setFromOpenGLMatrix(glm::value_ptr(modelMatrix));
	btRigidBody * rigBody = RigidBodySimpleFactory::createRigidBody(rigidBodyType, tr);
	setRigidBody(rigBody);
	setRigidBodyType(rigidBodyType);
}

PhysicalObject::PhysicalObject(glm::mat4 transform, Shader * shader, Texture texture, VaoObject * vao, std::string rigidBodyType) :SimpleObject(transform, shader, texture, vao)
{
	btTransform	tr;
	tr.setFromOpenGLMatrix(glm::value_ptr(modelMatrix));
	btRigidBody * rigBody = RigidBodySimpleFactory::createRigidBody(rigidBodyType, tr);
	setRigidBody(rigBody);
	setRigidBodyType(rigidBodyType);
}

PhysicalObject::PhysicalObject(glm::vec3 position, Shader * shader, Texture texture, VaoObject * vao, std::string rigidBodyType, glm::vec3 dir) : PhysicalObject(position, shader, texture, vao)
{
	btTransform	tr;
	tr.setFromOpenGLMatrix(glm::value_ptr(modelMatrix));
	btRigidBody * rigBody = RigidBodySimpleFactory::createRigidBody(rigidBodyType, tr);
	rigBody->setLinearVelocity(btVector3(dir.x, dir.y, dir.z));
	setRigidBody(rigBody);
	setRigidBodyType(rigidBodyType);
}

//PhysicalObject::PhysicalObject(glm::mat4 transform, Shader * shader, Texture texture, VaoObject * vao, std::string rigidBodyType, glm::vec3 dir):PhysicalObject(glm::vec3(0,0,0) , shader,  texture,  vao,  rigidBodyType,  dir)
//{
//	setModelMatrix(transform);
//	//setRigidBodyType(rigidBodyType);
//	//world->addPhyObj(this);
//}

PhysicalObject::PhysicalObject()
{
}


PhysicalObject::~PhysicalObject()
{
}


void PhysicalObject::setRigidBody(btRigidBody * ridigBody)
{
	this->rigidBody = ridigBody;
}

btRigidBody * PhysicalObject::getRigidBody()
{

	return rigidBody;
}

void PhysicalObject::setCollisionShape(btCollisionShape * collisionShape)
{
	rigidBody->setCollisionShape(collisionShape);
}

void PhysicalObject::update()
{
	btTransform trans;
	rigidBody->getMotionState()->getWorldTransform(trans);
	trans.getOpenGLMatrix(glm::value_ptr(modelMatrix));
}

void PhysicalObject::toXml(XMLDocument * xmlDoc)
{
	
	XMLElement *object = xmlDoc->NewElement("object");
	object->SetAttribute("texture", texture.getName().c_str());
	object->SetAttribute("vao", vao->getName().c_str());
	object->SetAttribute("shader", shader->getName().c_str());
	object->SetAttribute("type", rigidBodyType.c_str());
	XMLElement *matrix = xmlDoc->NewElement("modelMatrix");
	modelMatrixToXml(matrix);
	object->InsertFirstChild(matrix);
	//XMLPrinter printer;
	//object->Accept(&printer);
	//std::cout << printer.CStr();
	XMLElement * root = xmlDoc->FirstChildElement();
	root->InsertFirstChild(object);

}

void PhysicalObject::setRigidBodyType(std::string type)
{
	rigidBodyType = type;
}

