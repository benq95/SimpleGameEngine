#pragma once
///<summary>Klasa ta umo�liwia generowanie Vao na podstawie tablicy wierzcho�k�w. W tablicy wierzcho�k�w przechowywane s� ich wsp�rz�dne, wsp�rz�dne tekstur oraz opcjonalnie normalne wierzcho�k�w. Klasa posiada pole przechowuj�ce id wygenerowanego VAO.</summary>

class VaoObject
{
public:
	VaoObject();
	VaoObject(GLfloat * verticesArray, GLuint numberOfValues,bool normals);
	~VaoObject();
	void generate(GLfloat* verticesArray,GLuint numberOfValues);
	GLuint getID();
	GLuint getTrianglesNumber();
	void bind();
	std::string getName();
	void setName(std::string name);
private:
	std::string name;
	bool normals=false;
	GLuint id;
	GLuint verticlesNumber;
};