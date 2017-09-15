#pragma once

#include <btBulletDynamicsCommon.h>
#include <list>
#include "PhysicalObject.h"
///<summary>
///klasa reprezetujaca fizyczny swiat.
///</summary>
class PhysicsWorld
{
public:
	PhysicsWorld();
	~PhysicsWorld();
	///<summary>
	/// metoda inicjalizujaca fizyczny swiat, ustawia grawitacje
	///</summary>
	void init();
	/// <summary>
	/// metoda aktualizujaca fizyczny swiat gry o czas podany w parametrze
	/// </summary>
	void update(double deltaTime);
	/// <summary>
	/// metoda pozwalajaca na dodanie obiektu fizycznego do swiata fizycznego 
	/// </summary>
	/// <param>
	/// PhysicalObject * phyobj - wskaznik na obiekt fizyczny ktory zostanie dodany do fizycznego swiata
	/// </param>
	void addPhysicalObject(PhysicalObject * phyobj);
	void setCameraPos(glm::vec3 cameraPos);
	void setCameraFront(glm::vec3 cameraFront);
	void setReyTestObj(AbstractGameObject * rayTest);
	/// <summary>
	/// metoda oczyszczajaca swiat z wszystkich obiektow fizycznych wykorzystywana podczas ladowania wczesniej zapisanego stanu gry
	/// </summary>

	void clear();
private:
	AbstractGameObject * rayTest;
	btVector3 cameraPos;
	btVector3 cameraFront;
	btDiscreteDynamicsWorld * world=NULL;

	
};

