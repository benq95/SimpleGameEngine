#pragma once
#include <glm/glm.hpp>
#include"tinyxml2.h"
using namespace tinyxml2;
 class AbstractGameObject
{
public:
	AbstractGameObject();
	~AbstractGameObject();
	virtual void setPosition(glm::vec3 position)=0;
	virtual glm::vec3 getPosition() = 0;
	virtual void update()=0;
	virtual void draw()=0;
	virtual void setVisible(bool visible)=0;
	virtual bool isVisible()=0;
	virtual void toXml(XMLDocument * xmlDoc) = 0;
	//virtual AbstractGameObject* clone() = 0;
	//virtual string toString()=0;
protected:
	bool visible;

};

