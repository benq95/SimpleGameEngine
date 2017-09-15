#pragma once
#include<iostream>
#include<string>
///<summary>
///klasa umo�liwiaj�ca kompilacje shaderow. Przechowywane w polu numer ID shadera. Posiada metod� use() kt�ra wywo�uje funkcj� glUseProgram dla ID przechowywanego w polu obiektu.
///
///</summary>
class Shader
{
public:
	Shader();
	~Shader();
	GLuint getID();
	void compile(const GLchar *vsSource, const GLchar *fsSource, const GLchar *gsSource="");
	Shader  &use();
	std::string getName();
	void setName(std::string name);
private:
	std::string name;
	GLuint id;
	void checkCompileErrors(GLuint object, std::string type);
};

