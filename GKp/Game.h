#pragma once
#include <ctime>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <list>
#include"SimpleObject.h"
#include"AbstractGameObject.h"
#include"Camera.h"
#include<stdlib.h>
#include"ParticleEffect.h"
#include <btBulletDynamicsCommon.h>
#include"PhysicalObject.h"
#include"PhysicsWorld.h"
#include"NkWindow.h"
#include"ResourceManager.h"
#include"tinyxml2.h"
#include"Options.h"
using namespace tinyxml2;

#define PRINT_FPS false
///<summary>
/// Klasa g³ówna gry. Posiada implementacje podstawowych funkcjonalnosci. Jest klasa bazowa dla ExampleGame ktora ja rozszerza o inicjalizacje zasobow, obsluge wiekszej ilosci klawiszy itd.
///</summary>
class Game
{
public:
	Game(GLFWwindow* window);
	~Game();
	/// <summary>
	/// metoda uruchamiajaca glowna petle gry ktora trwa az do wylaczenia programu 
	/// </summary>

	virtual void startMainGameLoop();
	/// <summary>
	/// metoda ustawiajaca na true flage wcisniecia klawisza o indeksie podanym w parametrze
	/// </summary>
	void setKey(int keyIndex);
	/// <summary>
	/// metoda ustawiajaca na false flage wcisniecia klawisza o indeksie podanym w parametrze
	/// </summary>
	void clearKey(int keyIndex);
	/// <summary>
	/// metoda pozwalajaca na zmiane kierunku kamery 
	/// </summary>

	void changeCameraDirection(GLfloat x,GLfloat y);
	/// <summary>
	/// metoda odpowiedzialna za przygotowanie wstepnego stanu gry 
	/// </summary>
	virtual void init();

protected:
	Options options;

	virtual void initFloorPlane();
	virtual  void update();
	virtual void render();
	virtual void processInput();
	void exitGame();

	GLboolean  keys[1024] = {GL_FALSE};
	GLFWwindow* window;
	Camera camera;
	std::list<AbstractGameObject*> gameObjects;
	std::list<PhysicalObject*> prototypes;
	static map<string, PhysicalObject*> prototypes2;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;

	std::clock_t  oldTime;
	std::clock_t newTime;
	double deltaTime=0;
	double fps;



	// gui
	NkWindow* mainWindow;

	struct nk_context *ctx;
	glm::vec3 ambientColor;
	float ambientStrength;

	// physics
	PhysicsWorld world;
	PhysicalObject * ball;
	PhysicalObject * floor;

	AbstractGameObject * rayTest;

	GLint lcLoc;
	GLint lpLoc;
	GLint vpLoc;

	GLfloat minimalAngle = 3.1f;
	void generateCubes(GLuint x, GLuint y);
	void generateTree(GLuint x, GLuint y,GLuint h, GLuint s);
	void drawCubes();
	bool delCube;
	GLuint cubesGroundX;
	GLuint cubesGroundY;

	Shader* skyboxShader;
	unsigned int cubemapTexture;
	
	void toXml(std::string name = "foo.xml");
	void parseXml(std::string name = "foo.xml");
	void deleteObjects();
	//glm::mat4 readModelMatrix(XMLElement * matrix);
	glm::mat4 Game::xmlToModelMatrix(XMLElement * matrix);
	ParticleEffect pe;
	GLfloat testArray[180] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
};

