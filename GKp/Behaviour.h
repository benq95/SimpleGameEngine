#pragma once
#include"AbstractGameObject.h"

/// <summary>
/// abstrakcyjna klasa ktora miala miec mozliwosc dodawania dodatkowych zachowan do obiektow. Nie doczekala sie swojej implementacji.
/// </summary>
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

