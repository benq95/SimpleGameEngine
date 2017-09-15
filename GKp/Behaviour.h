#pragma once
#include"AbstractGameObject.h"

class Behaviour
{
public:
	Behaviour();
	~Behaviour();
	virtual void setRoot(AbstractGameObject * object);
	virtual void update() = 0;
	virtual void init()=0;
protected:
	AbstractGameObject * root;
};

