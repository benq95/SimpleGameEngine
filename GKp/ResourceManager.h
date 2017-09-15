#pragma once

#include <map>
#include <string>
#include <GL/glew.h>
#include "texture.h"
#include "shader.h"
#include "VaoObject.h"
#include <vector>

using namespace std;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	// loads shaders from file, compile and storeage it in collection
	static void loadShader(string vShaderFile, string fShaderFile, string name);
	static void loadShader(string vShaderFile, string fShaderFile,string gShaderFile, string name);
	// returns shader 
	static Shader* GetShader(std::string name);
	static Texture LoadTexture(const GLchar *file, GLboolean alpha, string name);
	static Texture GetTexture(std::string name);
	static VaoObject loadVAOFromFile(const GLchar *file, string = "", bool readNormals = false);
	static VaoObject loadVAO(GLfloat* verticesArray, GLuint numberOfValues,bool normals,string name);
	static VaoObject* getVAO(string name);
	static void deleteAssets();
	static unsigned int loadCubemap(vector<std::string> faces);
	static bool ResourceManager::readWorld(std::string wordlName);
	static std::vector<std::string> GetTextureNames();
private:
	static map<string, Texture> textures;
	//collections
	static map<string, Shader> shaders;
	static map<string, VaoObject> vaos;
	static string readFile(string filePath);
	static Texture loadTextureFromFile(const GLchar *file, GLboolean alpha);
	static glm::ivec3 strVertextoVec3(string s);
	static bool readAssets();
	static bool ResourceManager::readShaders();
	static bool ResourceManager::readVaos();
	static bool ResourceManager::readTextures();
	static bool ResourceManager::readObjects();

};


