#pragma once
#include "AbstractGameObject.h"
#include "Shader.h"
#include "Texture.h"
#include "VaoObject.h"
#include "Behaviour.h"
#include "List"
#include"tinyxml2.h"

using namespace tinyxml2;

class SimpleObject :
	public AbstractGameObject
{
public:
	SimpleObject();
	SimpleObject(glm::vec3 position, Shader * shader, Texture texture, VaoObject * vao);
	SimpleObject(glm::mat4 transform, Shader * shader, Texture texture, VaoObject * vao);
	SimpleObject(glm::vec3 position);
	SimpleObject(Texture texture, glm::mat4 modelMatrix, VaoObject* VAO);



	~SimpleObject();
	virtual void update();
	virtual void draw();
	//void setShader(Shader shader);
	virtual void setShader(Shader * shader);
	void setTexture(Texture texture);
	void setVao(VaoObject * vao);
	virtual void setPosition(glm::vec3 position);
	virtual glm::vec3 getPosition();
	virtual void setVisible(bool visible);
	virtual bool isVisible();
	virtual void addBehaviour(Behaviour * behaviour);
	//virtual AbstractGameObject* clone();
	virtual void toXml(XMLDocument * xmlDoc);

protected:
	glm::mat4 modelMatrix;
	Shader * shader;
	VaoObject * vao;
	Texture texture;
	std::list<Behaviour*> behaviours;

	//virtual void setShaderID(GLuint shaderID);
	virtual void setVAO(VaoObject* VAO);
	virtual void setModelMatrix(glm::mat4 modelMatrix);
	void modelMatrixToXml(XMLElement * matrix);
private:
	void vectorToXml(XMLElement * matrix, int i);
};

