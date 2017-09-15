#include "stdafx.h"
#include "Behaviour.h"


Behaviour::Behaviour()
{
}


Behaviour::~Behaviour()
{
}

void Behaviour::setRoot(AbstractGameObject * object)
{
	this->root = object;
}
