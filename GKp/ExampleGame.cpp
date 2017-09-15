#include "stdafx.h"
#include "ExampleGame.h"



ExampleGame::ExampleGame(GLFWwindow* window) : Game(window)
{

}

ExampleGame::~ExampleGame()
{
}

void ExampleGame::init()
{
	Game::init();
	initSkybox();


	ResourceManager::loadShader("shader1.vs", "shader1.fs", "shader1");
	Shader* asd = ResourceManager::GetShader("shader1");
	asd->use();
	int shaderId = asd->getID();
	GLint viewLoc = glGetUniformLocation(shaderId, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	GLint projLoc = glGetUniformLocation(shaderId, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	lcLoc = glGetUniformLocation(shaderId, "lightColor");
	lpLoc = glGetUniformLocation(shaderId, "lightPos");
	vpLoc = glGetUniformLocation(shaderId, "viewPos");

	ambientColor = glm::vec3(255, 255, 255);

	ResourceManager::LoadTexture("container.jpg", GL_TRUE, "texture1");
	ResourceManager::LoadTexture("brick.jpg", GL_TRUE, "brick");
	ResourceManager::LoadTexture("steel.jpg", GL_TRUE, "texture2");
	ResourceManager::LoadTexture("weed.jpg", GL_TRUE, "texture3");
	ResourceManager::LoadTexture("bark.jpg", GL_TRUE, "bark");
	ResourceManager::LoadTexture("leafs.jpg", GL_TRUE, "leafs");
	ResourceManager::LoadTexture("BasketballColor.jpg", GL_TRUE, "ball");
	options.textureNames = ResourceManager::GetTextureNames();
	options.actualTexture = "brick";


	ResourceManager::loadVAOFromFile("test.obj", "vao1", true);
	ResourceManager::loadVAOFromFile("brick.obj", "brick", true);
	ResourceManager::loadVAOFromFile("untitled3.obj", "vao2", true);
	ResourceManager::loadVAOFromFile("BALL.obj", "vao3", true);
	ResourceManager::loadVAOFromFile("floor.obj", "floor", true);


//	ball2 = new SimpleCube(glm::vec3(1, 1, 1), asd, ResourceManager::GetTexture("bark"), ResourceManager::getVAO("vao3"));
	//physics objects init

	//floor = new PhysicalObject();
	//btScalar mass = 1;

	//btDefaultMotionState* fallMotionState =
	//	new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(5, 20, 5)));
	//btVector3 fallInertia(0, 0, 0);
	//btCollisionShape* fallShape = new btSphereShape(1);
	//fallShape->calculateLocalInertia(mass, fallInertia);
	//btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
	//btRigidBody * fallRigidBody = new btRigidBody(fallRigidBodyCI);
	//fallRigidBody->setRestitution(0.9f);
	//ball->setRigidBody(fallRigidBody);
	//ball = new PhysicalObject(glm::vec3(0, 0, 0), asd, ResourceManager::GetTexture("ball"), ResourceManager::getVAO("vao3"), fallRigidBody);

	//world.addPhyObj(ball);
	
	//gameObjects.push_front(ball);
	//generateCubes(100, 100);

	ResourceManager::readWorld("exampleWorld.xml");

	initFloorPlane();
	initSomeWall(6,3);

	rayTest = new SimpleObject(glm::vec3(1, 1, 1), asd, ResourceManager::GetTexture("bark"), ResourceManager::getVAO("vao3"));


	world.setReyTestObj(rayTest);
	
	initPrototypes();
}


void ExampleGame::processInput()
{
	static bool created= false;
	static bool placed = false;
	Game::processInput();
	if (keys[GLFW_KEY_1]) {
		if (!created) {
			createObject(rayTest->getPosition());
			created = true;
		}

	}
	else {
		created = false;
	}
}

void ExampleGame::update()
{
	Game::update();
	newTime = std::clock();
	deltaTime = (double)(newTime - oldTime) / (double)CLOCKS_PER_SEC;
	oldTime = std::clock();
	if (!options.paused) {
		world.update(deltaTime);
	}

	fps = 1.0f / deltaTime;
	if (PRINT_FPS) {
		std::cout << fps << std::endl;
	}
	processInput();
	camera.update();

	glm::vec3 testD = glm::normalize(camera.getPos());

	list<AbstractGameObject*>::iterator gameObject;
	for (gameObject = gameObjects.begin(); gameObject != gameObjects.end(); ++gameObject)
	{

		(*gameObject)->update();
		glm::vec3 testD2 = (camera.getPos());
		glm::vec3 testPos = (*gameObject)->getPosition();
		testD2 = testPos - testD2;
		testD2 = glm::normalize(testD2);
		GLfloat testAngle = glm::acos(glm::dot(testD2, camera.getfront()));
		if (testAngle< 0.8) {
			(*gameObject)->setVisible(true);
		}
		else {
			(*gameObject)->setVisible(false);
		}

	}
	//Game::render();
}

void ExampleGame::initSkybox()
{

	vector<std::string> faces;
	faces.push_back("right.jpg");
	faces.push_back("left.jpg");
	faces.push_back("top.jpg");
	faces.push_back("bottom.jpg");
	faces.push_back("back.jpg");
	faces.push_back("front.jpg");
	ResourceManager::loadShader("sbs.vs", "sbs.fs", "skyboxshader");
	cubemapTexture = ResourceManager::loadCubemap(faces);
	skyboxShader = ResourceManager::GetShader("skyboxshader");
	ResourceManager::loadVAO(testArray, 180, false, "skyboxvao");


	skyboxShader->use();
	GLint viewLoc = glGetUniformLocation(skyboxShader->getID(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	GLint projLoc = glGetUniformLocation(skyboxShader->getID(), "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}

void ExampleGame::initFloorPlane()
{
	floor = new PhysicalObject();
	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0.0f, 0)));
	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	groundRigidBody->setRestitution(1.0f);
	floor->setRigidBody(groundRigidBody);
	world.addPhysicalObject(floor);
	generateCubes(40,40);
}

void ExampleGame::initSomeWall(int x, int y)
{
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			createBrick(glm::vec3(10,j*1+0.5,i+10));
		}
	}
}


void ExampleGame::createBrick(glm::vec3 pos)
{
	/*btDefaultMotionState* brickMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(pos.x,pos.y, pos.z)));
	btScalar mass = 1;
	btVector3 brickInertia(0, 0, 0);
	btCollisionShape* brickShape = new btBoxShape(btVector3(1, 0.5, 0.5));
	brickShape->calculateLocalInertia(mass, brickInertia);
	btRigidBody::btRigidBodyConstructionInfo brickRigidBodyCI(mass, brickMotionState, brickShape, brickInertia);

	btRigidBody * brickRigidBody = new btRigidBody(brickRigidBodyCI);
	brickRigidBody->setRestitution(0.9f);
	*/
	//btRigidBody * brickRigidBody = RigidBodySimpleFactory::createRigidBody("brick");
	AbstractGameObject * someCube = new PhysicalObject(pos, ResourceManager::GetShader("shader1"), ResourceManager::GetTexture("brick"), ResourceManager::getVAO("brick"), "brick");
	world.addPhysicalObject((PhysicalObject*)someCube);
	gameObjects.push_front(someCube);
}
void ExampleGame::createObject(glm::vec3 pos)
{
	Texture nt = ResourceManager::GetTexture(options.getActualTexture());
	AbstractGameObject * someCube;
	VaoObject * nv;
	if (options.createShape == options.PLACE)
		nv=ResourceManager::getVAO("vao3");
	else
		nv=ResourceManager::getVAO("brick");

	if(options.createType==options.PLACE)
	{
		someCube = new PhysicalObject(pos, ResourceManager::GetShader("shader1"), nt, nv, options.getActualShape());
	}else
	{
		float power = options.power;
		glm::vec3 dir = camera.getfront() * power;
		someCube = new PhysicalObject(camera.getPos(), ResourceManager::GetShader("shader1"), nt, nv, options.getActualShape(), dir);
	}
	world.addPhysicalObject((PhysicalObject*)someCube);
	gameObjects.push_front(someCube);
}


void ExampleGame::initPrototypes()
{
	

}