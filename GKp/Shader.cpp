#include "stdafx.h"
#include "Shader.h"


Shader::Shader()
{
	this->id = NULL;
}


Shader::~Shader()
{
}

GLuint Shader::getID()
{
	return id;
}

void Shader::compile(const GLchar * vsSource, const GLchar * fsSource, const GLchar *gsSource)
{

	this->id = glCreateProgram();
	GLuint vsID;
	GLuint fsID;
	GLuint gsID;
	vsID = glCreateShader(GL_VERTEX_SHADER);
	fsID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vsID, 1, &vsSource, NULL);
	glShaderSource(fsID, 1, &fsSource, NULL);
	glCompileShader(vsID);
	checkCompileErrors(vsID, "VERTEX");
	glCompileShader(fsID);
	checkCompileErrors(fsID, "FRAGMENT");


	if (gsSource != "") {
		
		gsID = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(gsID, 1, &vsSource, NULL);
		glCompileShader(gsID);
		checkCompileErrors(gsID, "GEOMETRY");
		glAttachShader(this->id, gsID);
		glAttachShader(this->id, fsID);
		glAttachShader(this->id, vsID);
		glLinkProgram(this->id);
		checkCompileErrors(this->id, "PROGRAM");
		glDeleteShader(gsID);
	}
	else {
		glAttachShader(this->id, fsID);
		glAttachShader(this->id, vsID);
		glLinkProgram(this->id);
		checkCompileErrors(this->id, "PROGRAM");
	}

	//glUseProgram(this->id);
	glDeleteShader(vsID);
	glDeleteShader(fsID);
	
	/*
	GLuint sVertex, sFragment, gShader;
	// Vertex Shader
	sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &vsSource, NULL);
	glCompileShader(sVertex);
	checkCompileErrors(sVertex, "VERTEX");
	// Fragment Shader
	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fsSource, NULL);
	glCompileShader(sFragment);
	checkCompileErrors(sFragment, "FRAGMENT");

	// Shader Program
	this->id = glCreateProgram();
	glAttachShader(this->id, sVertex);
	glAttachShader(this->id, sFragment);

	glLinkProgram(this->id);
	checkCompileErrors(this->id, "PROGRAM");
	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
	//glUseProgram(this->id);
	*/
}
Shader & Shader::use()
{
	glUseProgram(this->id);
	return *this;
}

std::string Shader::getName()
{
	return name;
}

void Shader::setName(std::string name)
{
	this->name = name;
}


void Shader::checkCompileErrors(GLuint object, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
				
		}
	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
}
