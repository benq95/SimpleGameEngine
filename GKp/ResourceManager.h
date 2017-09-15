#pragma once

#include <map>
#include <string>
#include <GL/glew.h>
#include "texture.h"
#include "shader.h"
#include "VaoObject.h"
#include <vector>

using namespace std;
///<summary> statyczna klasa odpowiedzialna za wczytywanie oraz przechowywanie zasobów takich jak tekstury , shadery oraz siatki(Vertex Array Objects). Klasa ta tworzy instancje klas Shader,Texture i VaoObject.
///</summary>
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	/// <summary>
	/// kompiluje shadery z plikow o podanych nazwach i przechowuje ich id w mapie pod kluczem podanym w parametrze name
	/// </summary>
	static void loadShader(string vShaderFile, string fShaderFile, string name);
	/// <summary>
	/// kompiluje shadery z plikow o podanych nazwach i przechowuje ich id w mapie pod kluczem podanym w parametrze name
	/// </summary>
	static void loadShader(string vShaderFile, string fShaderFile,string gShaderFile, string name);
	/// <summary>
	/// zwraca shader o kluczu podanym w parametrze
	/// </summary>
	static Shader* GetShader(std::string name);
	/// <summary>
	/// laduje teksture z pliku podanego w parametrze i zapisuje ja w mapie
	/// </summary>
	///<param>
	/// string name - klucz pod ktorym zostanie zapisana tekstura
	///</param>
	static Texture LoadTexture(const GLchar *file, GLboolean alpha, string name);
	static Texture GetTexture(std::string name);
	static VaoObject loadVAOFromFile(const GLchar *file, string = "", bool readNormals = false);
	/// <summary>
	/// laduje VAO z pliku podanego w parametrze i zapisuje je w mapie
	/// </summary>
	/// <param>
	/// string name - klucz pod ktorym zostanie zapisane VAO
	/// </param>
	static VaoObject loadVAO(GLfloat* verticesArray, GLuint numberOfValues,bool normals,string name);
	static VaoObject* getVAO(string name);
	/// <summary>
	/// usowa zasoby z kolekcji
	/// </summary>

	static void deleteAssets();
	/// <summary>
	/// laduje tekstury skyboxa z pliku i tworzy z nich skyboxa
	/// </summary>
	/// <param>
	/// vector<std::string> faces - wektor przechowujacy obrazki z ktorych ma zostac zbudowany skybox
	/// </param>
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


