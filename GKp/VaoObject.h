#pragma once
///<summary>Klasa ta umo¿liwia generowanie Vao na podstawie tablicy wierzcho³ków. W tablicy wierzcho³ków przechowywane s¹ ich wspó³rzêdne, wspó³rzêdne tekstur oraz opcjonalnie normalne wierzcho³ków. Klasa posiada pole przechowuj¹ce id wygenerowanego VAO.</summary>

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