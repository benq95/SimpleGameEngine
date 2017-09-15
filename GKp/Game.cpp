#include "stdafx.h"

#include "Game.h"




std::map<std::string, Shader> ResourceManager::shaders;
std::map<std::string, Texture> ResourceManager::textures;
std::map<std::string, VaoObject> ResourceManager::vaos;
Game::Game(GLFWwindow* window)
{
	this->window = window;

	glfwMakeContextCurrent(window);

}


Game::~Game()
{
	ResourceManager::deleteAssets();
}

void Game::setKey(int keyIndex)
{
	if (keys!=NULL)
	keys[keyIndex] = GL_TRUE;
}

void Game::clearKey(int keyIndex)
{
	if (keys != NULL)
	keys[keyIndex] = GL_FALSE;
}

void Game::changeCameraDirection(GLfloat x, GLfloat y)
{
	camera.rotateCamera(x, y);
}

void Game::mainGameloop()
{
	while (!glfwWindowShouldClose(window))
	{
		update();
		glfwPollEvents();
		render();
		glfwSwapBuffers(window);
	}
	exitGame();
}

void Game::init()
{
	
	world.init();
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glewExperimental = 1;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to setup GLEW\n");
		exit(1);
	}
	mainWindow = new NkWindow(window,&options);
	mainWindow->init();
	ambientStrength =0.3f;
	oldTime = std::clock();
	for (int i = 0; i < 1024;i++) {
		keys[i] = GL_FALSE;
	}
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	projectionMatrix = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

}


void Game::initFloorPlane()
{
}

void Game::update()
{
	mainWindow->update();
	world.setCameraPos(camera.getPos());
	world.setCameraFront(camera.getfront());
}

void Game::render()
{
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glDepthMask(GL_FALSE);

		skyboxShader->use();
		GLint viewLoc = glGetUniformLocation(skyboxShader->getID(), "view");
		glm::mat4 skyboxView = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(skyboxView));

		GLuint skyboxVAO = ResourceManager::getVAO("skyboxvao")->getID();
		glBindVertexArray(skyboxVAO);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glDepthMask(GL_TRUE);

		Shader* asd = ResourceManager::GetShader("shader1");
		asd->use();
		glm::vec3 ambientColorI = options.ambientColor*options.ambientStrength/255.f;
		
		glUniform3fv(lcLoc, 1, glm::value_ptr(ambientColorI));
		glm::vec3 cameraPos = camera.getPos();
		glUniform3fv(vpLoc, 1, glm::value_ptr(cameraPos));

		GLint modelLoc2 = glGetUniformLocation(asd->getID(), "view");
		glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));

		drawCubes();
		//ball->draw();

		rayTest->draw();
		mainWindow->render();

}

void Game::processInput()
{
	static bool clicked=false;
	if (keys[GLFW_KEY_W]) {
		camera.moveForward(deltaTime);
	}else if (keys[GLFW_KEY_S]) {
		camera.moveForward(-deltaTime);
	}
	if (keys[GLFW_KEY_A]) {
		camera.moveRight(deltaTime);
	}else if (keys[GLFW_KEY_D])
		camera.moveRight(-deltaTime);
	if (keys[GLFW_KEY_SPACE]) {
		camera.moveUp(-deltaTime);
	}
	else if (keys[GLFW_KEY_Z])
		camera.moveUp(+deltaTime);
	if (keys[GLFW_KEY_E]) {
		delCube = true;
	}
	if (keys[GLFW_KEY_X]) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	if (keys[GLFW_KEY_C]) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	if (keys[GLFW_KEY_O]) {
		toXml("foo.xml");
	}
	if (keys[GLFW_KEY_I]) {
		parseXml("foo.xml");
	}
	if (options.save) {
		options.save = false;
		toXml("save.xml");
	}
	if (options.load) {
		options.load = false;
		parseXml("save.xml");
	}

	if (keys[GLFW_KEY_P]) {
		if (!clicked) {
			if (options.paused) {
				options.paused = (GL_FALSE);
			}
			else {
				options.paused = (GL_TRUE);
			}
			clicked = true;
		}
	}
	else {
		clicked = false;
	}
}

void Game::exitGame()
{
	glfwTerminate();
}



void Game::generateCubes(GLuint x, GLuint y)
{
	Shader* asd = ResourceManager::GetShader("shader1");
	cubesGroundX = x;
	cubesGroundY = y;
	//arrayOfCubes = new SimpleCube[cubesGroundX*cubesGroundY];
	for (GLuint i = 0; i < cubesGroundX; i++) {
		for (GLuint j = 0; j < cubesGroundY; j++) {
			AbstractGameObject * someCube = new SimpleObject(glm::vec3(i*6, 0, j*6),asd, ResourceManager::GetTexture("texture3"), ResourceManager::getVAO("floor"));
			gameObjects.push_front(someCube);
		}
	}
}

void Game::generateTree(GLuint x, GLuint y,GLuint h,GLuint s)
{
	Shader* asd = ResourceManager::GetShader("shader1");
	for (int i = 1; i <= h; i++) {
		AbstractGameObject * someCube = new SimpleObject(glm::vec3(x, i, y), asd, ResourceManager::GetTexture("bark"), ResourceManager::getVAO("vao2"));
		gameObjects.push_front(someCube);
	}
	
	for (int k = s; k >= 0; k--) {
		for (int i = int(-s); i <= int(s); i++) {
			for (int j = int(-s); j <= int(s); j++) {
				AbstractGameObject * someCube = new SimpleObject(glm::vec3(x+i, int(h+1+s-k), y+j), asd, ResourceManager::GetTexture("leafs"), ResourceManager::getVAO("vao1"));
				gameObjects.push_front(someCube);
			}
		}
	}

}

void Game::drawCubes()
{
	for (auto &gameObject : gameObjects)
	{
		gameObject->draw();
	}
}

void Game::toXml(std::string name)
{
	XMLDocument xmlDoc=new XMLDocument();
	XMLElement * root = xmlDoc.NewElement("gameState");
	xmlDoc.InsertFirstChild(root);
	for (auto &gameObject : gameObjects)
	{
		gameObject->toXml(&xmlDoc);
	}
	//rayTest->toXml(&xmlDoc);
	xmlDoc.SaveFile(name.c_str());
}

void Game::parseXml(std::string name)
{
	deleteObjects();
	initFloorPlane();
	XMLDocument xmlDoc;
	xmlDoc.LoadFile(name.c_str());
	XMLElement * root = xmlDoc.FirstChildElement("gameState");
	
		XMLElement * element = root->FirstChildElement("object");
	while (element!=NULL) {
		AbstractGameObject * newObject;// = new SimpleCube();
		std::string vaoName = element->Attribute("vao");
		std::string textureName = element->Attribute("texture");
		std::string shaderName = element->Attribute("shader");

		XMLElement * matrix = element->FirstChildElement("modelMatrix");
		glm::mat4 transform = xmlToModelMatrix(matrix);



		std::string type = element->Attribute("type");

		if (type == "none") {
			newObject = new SimpleObject(transform, ResourceManager::GetShader(shaderName), ResourceManager::GetTexture(textureName), ResourceManager::getVAO(vaoName));
		}
		else{
			newObject = new PhysicalObject(transform, ResourceManager::GetShader(shaderName), ResourceManager::GetTexture(textureName), ResourceManager::getVAO(vaoName), type);
			world.addPhyObj((PhysicalObject*)newObject);
		}
		gameObjects.push_front(newObject);
		
		element = element->NextSiblingElement("object");
	}
		
}

void Game::deleteObjects()
{
	world.clear();
	while (gameObjects.size() > 0)
		gameObjects.pop_back();
}


glm::mat4 Game::xmlToModelMatrix(XMLElement * matrix)
{

	glm::mat4 modelMatrix;
	for (int i = 0; i < 4; i++)
	{
		std::string name = "row" + std::to_string(i)+ "_x";
		std::string str = matrix->Attribute(name.c_str());
		float x = atof(str.c_str() );
		name = "row" + std::to_string(i)+ "_y";
		str = matrix->Attribute(name.c_str());
		float y = atof(str.c_str());

		name = "row" + std::to_string(i)+ "_z";
		str = matrix->Attribute(name.c_str());
		float z = atof(str.c_str());

		name = "row" + std::to_string(i) + "_w";
		str = matrix->Attribute(name.c_str());
		float w = atof(str.c_str());

		modelMatrix[i] = glm::vec4(x, y,z,w);
	}


	return modelMatrix;
}


