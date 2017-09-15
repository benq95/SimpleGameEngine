#pragma once
#include "Game.h"
///<summary> klasa rozszerzajaca klase Game. posiada metody inicjalizujace poczatkowy stan oraz inicjalizacje zasobow  <summary>
class ExampleGame :
	public Game
{
public:
	ExampleGame(GLFWwindow* window);
	~ExampleGame();
	virtual void init();
protected:

	virtual void processInput();
	virtual  void update();
	void initSkybox();
	void initPrototypes();
	void initFloorPlane();
	void initSomeWall(int x,int y);
	void createObject(glm::vec3 pos);
	void createBrick(glm::vec3 pos);
	//void createBrick(GLfloat x, GLfloat y, GLfloat z);
	SimpleObject * ball2;
};

