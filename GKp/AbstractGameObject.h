#pragma once
#include <glm/glm.hpp>
#include"tinyxml2.h"
using namespace tinyxml2;
///<summary>
/// Abstrakcyjna klasa definiujaca interfejs dla obiektow w grze. Jej implementacje mozna znalesc w klasach PhysicalObject oraz SimpleObject.
///</summary>
 class AbstractGameObject
{
public:
	AbstractGameObject();
	~AbstractGameObject();
	///<summary>
	/// Metoda sluzaca do ustawiania pozycji obiektu
	///</summary>
	virtual void setPosition(glm::vec3 position)=0;
	virtual glm::vec3 getPosition() = 0;
	///<summary>
	/// metoda wywolywana co klatke aktualizujaca stan obiektu
	///</summary>
	virtual void update()=0;
	///<summary>
	/// metoda wywolywana co klatke rysujaca obiekt na ekranie
	///</summary>
	virtual void draw()=0;
	virtual void setVisible(bool visible)=0;
	virtual bool isVisible()=0;
	///<summary>
	/// metoda dodajaca fragment bedacy opisem obiektu jako XML do dokumentu na ktory wskaznik podawany jest w parametrze
	///</summary>
	virtual void toXml(XMLDocument * xmlDoc) = 0;
	//virtual AbstractGameObject* clone() = 0;
	//virtual string toString()=0;
protected:
	bool visible;

};

