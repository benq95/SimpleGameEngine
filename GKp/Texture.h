#pragma once
#include <GL/glew.h>
///<summary>
///Klasa umo¿liwiaj¹ca generowanie tekstury na podstawie obrazu. Przechowywujê w polu ID tekstury  oraz informacje o teksturze takie jak rozmiar, wrap, filter.
///</summary>
class Texture
{
public:
	Texture();
	~Texture();
	void Generate(GLuint width, GLuint height, unsigned char* data);
	void bind() const;

	void setImgFormat(GLuint imgFormat);
	void setIntFormat(GLuint intFormat);
	GLuint getImgFormat();
	GLuint getIntFormat();
	GLuint getID();
	std::string getName();
	void setName(std::string name);
private:
	std::string name;
	GLuint id;
	GLuint width;
	GLuint height;
	GLuint intFormat= GL_RGB;
	GLuint imgFormat= GL_RGB;
	GLuint wrapS= GL_REPEAT;
	GLuint wrapT= GL_REPEAT;
	GLuint filterMin= GL_LINEAR_MIPMAP_LINEAR;
	GLuint filterMax= GL_LINEAR;
			
};

