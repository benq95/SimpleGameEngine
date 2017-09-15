#include "stdafx.h"
#include "SimpleObject.h"

using namespace tinyxml2;

SimpleObject::SimpleObject()
{
	//modelMatrix;// = glm::rotate(modelMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	
}

SimpleObject::SimpleObject(glm::vec3 position, Shader * shader, Texture texture, VaoObject * vao)
{
	this->setPosition(position);
	this->setShader(shader);
	this->setTexture(texture);
	this->setVao(vao);

}

SimpleObject::SimpleObject(glm::mat4 transform, Shader * shader, Texture texture, VaoObject * vao)
{
	setModelMatrix(transform);
	this->setShader(shader);
	this->setTexture(texture);
	this->setVao(vao);
}

SimpleObject::SimpleObject(glm::vec3 position)
{
//	modelMatrix = glm::rotate(modelMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	SimpleObject();
}

SimpleObject::SimpleObject(Texture texture, glm::mat4 modelMatrix, VaoObject * VAO)
{
	setTexture(texture);
	setModelMatrix(modelMatrix);
	setVAO(VAO);
}


SimpleObject::~SimpleObject()
{
}

void SimpleObject::update()
{
	for (Behaviour * behaviour : behaviours) {
		behaviour->update();
	}
}

void SimpleObject::draw()
{
	if (visible) {
		texture.bind();
		glBindVertexArray(vao->getID());
		GLint modelLoc = glGetUniformLocation(shader->getID(), "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glDrawArrays(GL_TRIANGLES, 0, vao->getTrianglesNumber());
		glBindVertexArray(0);
	}
}

void SimpleObject::setShader(Shader * shader)
{
	this->shader = shader;
}

void SimpleObject::setTexture(Texture texture)
{
	this->texture = texture;
}

void SimpleObject::setVao(VaoObject * vao)
{
	this->vao = vao;
}

void SimpleObject::setPosition(glm::vec3 position)
{
	modelMatrix=glm::translate(glm::mat4(),position);
}

glm::vec3 SimpleObject::getPosition()
{
	return glm::vec3(modelMatrix[3][0], modelMatrix[3][1], modelMatrix[3][2]);
}

void SimpleObject::setVisible(bool visible)
{
	this->visible = visible;
}

bool SimpleObject::isVisible()
{
	return visible;
}

void SimpleObject::addBehaviour(Behaviour * behaviour)
{
	behaviour->setRoot(this);
	behaviours.push_front(behaviour);
}

//AbstractGameObject* SimpleCube::clone()
//{
//		return new SimpleCube(this->texture, this->modelMatrix, this->VAO);
//}


//void SimpleCube::setShaderID(GLuint shaderID)
//{
//	this->shaderID = shaderID;
//}
//void SimpleCube::setShaderID(Shader * shader)
//{
//	this->shader = shader;
//}

void SimpleObject::setVAO(VaoObject * VAO)
{
	this->vao = VAO;
}

void SimpleObject::setModelMatrix(glm::mat4 modelMatrix)
{
	this->modelMatrix = modelMatrix;
}

void SimpleObject::modelMatrixToXml(XMLElement * matrix)
{
	for (int i = 0; i < 4; i++) {
		vectorToXml(matrix, i);
	}

}

void SimpleObject::vectorToXml(XMLElement * matrix,int i) {

	std::string name = "row" + std::to_string(i) + "_x";
	matrix->SetAttribute(name.c_str(), modelMatrix[i].x);
	name = "row" + std::to_string(i) + "_y";
	matrix->SetAttribute(name.c_str(), modelMatrix[i].y);
	name = "row" + std::to_string(i) + "_z";
	matrix->SetAttribute(name.c_str(), modelMatrix[i].z);
	name = "row" + std::to_string(i) + "_w";
	matrix->SetAttribute(name.c_str(), modelMatrix[i].w);
}


void SimpleObject::toXml(XMLDocument * xmlDoc)
{
	//XMLDocument doc = new XMLDocument();
	XMLElement *object = xmlDoc->NewElement("object");
	object->SetAttribute("texture", texture.getName().c_str());
	object->SetAttribute("vao", vao->getName().c_str());
	object->SetAttribute("shader", shader->getName().c_str());
	object->SetAttribute("type", "none");
	XMLElement *matrix = xmlDoc->NewElement("modelMatrix");
	modelMatrixToXml(matrix);
	object->InsertFirstChild(matrix);
	//XMLPrinter printer;
	//object->Accept(&printer);
	//std::cout << printer.CStr();
	XMLElement * root = xmlDoc->FirstChildElement();
	root->InsertFirstChild(object);
	//doc.SaveFile("foo.xml");
}


