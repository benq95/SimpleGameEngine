#include "stdafx.h"
#include "ParticleEffect.h"


ParticleEffect::ParticleEffect()
{
	currVB=0;
	currTFB=1;
}


ParticleEffect::~ParticleEffect()
{
}

void ParticleEffect::update()
{
	// zamiana indeksow 
	currVB = currTFB;
	currTFB = (currTFB + 1) % 2;
	glUseProgram(program);
	glEnable(GL_RASTERIZER_DISCARD);
	glBindBuffer(GL_ARRAY_BUFFER, particleBuffer[currVB]);
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, transformFeedback[currTFB]);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), 0); // type
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)4); // position
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)16); // velocity
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)28); // lifetime

	glBeginTransformFeedback(GL_POINTS);

	glDrawTransformFeedback(GL_POINTS, transformFeedback[currVB]);

	glEndTransformFeedback();
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);

	//render feedbacku
	glDisable(GL_RASTERIZER_DISCARD);

	GLfloat feedback[15];
	glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 1, sizeof(feedback), feedback);

	glBindBuffer(GL_ARRAY_BUFFER, particleBuffer[currTFB]);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)4); // position

	glDrawTransformFeedback(GL_POINTS, transformFeedback[currTFB]);

	glDisableVertexAttribArray(0);
}

void ParticleEffect::init()
{

	// Compile shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSrc, nullptr);
	glCompileShader(vertexShader);

	GLuint geoShader = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geoShader, 1, &geoShaderSrc, nullptr);
	glCompileShader(geoShader);

	// Create program and specify transform feedback variables
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, geoShader);

	const GLchar* feedbackVaryings[] = { "outValue" };
	glTransformFeedbackVaryings(program, 1, feedbackVaryings, GL_INTERLEAVED_ATTRIBS);

	glLinkProgram(program);
	glUseProgram(program);

	// Create VAO
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create input VBO and vertex format
	GLfloat data[] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };

	Particle data2[10];
	for (int i = 0; i < 10; i++) {
		data2[i].lifetime = i;
		data2[i].pos = glm::vec3(i,i+1,i+2);
		data2[i].vel = glm::vec3(((float)i) *0.1, i*0.2, i*0.3);
		data2[i].Type = i;
	}

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data2), data2, GL_STATIC_DRAW);

	GLint inputAttrib = glGetAttribLocation(program, "inValue");
	GLint inputpos = glGetAttribLocation(program, "pos");
	GLint inputvel = glGetAttribLocation(program, "vel");
	//GLint inputpos = glGetAttribLocation(program, "type");
	glEnableVertexAttribArray(inputpos);
	glEnableVertexAttribArray(inputAttrib);
	glEnableVertexAttribArray(inputvel);
	glVertexAttribPointer(inputAttrib, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), 0);
	glVertexAttribPointer(inputpos, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)4);
	glVertexAttribPointer(inputvel, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)16);

	// Create transform feedback buffer
	GLuint tbo;
	glGenBuffers(1, &tbo);
	glBindBuffer(GL_ARRAY_BUFFER, tbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 30, nullptr, GL_STATIC_READ);

	// Perform feedback transform
	glEnable(GL_RASTERIZER_DISCARD);

	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tbo);

	glBeginTransformFeedback(GL_TRIANGLES);
	glDrawArrays(GL_POINTS, 0, 10);
	glEndTransformFeedback();

	glDisable(GL_RASTERIZER_DISCARD);

	glFlush();

	// Fetch and print results
	GLfloat feedback[30];
	glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(feedback), feedback);

	for (int i = 0; i < 30; i++) {
		printf("%f\n", feedback[i]);
	}
	// do it once again
	glEnable(GL_RASTERIZER_DISCARD);

	//glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tbo);

	glBeginTransformFeedback(GL_TRIANGLES);
	//glDrawArrays(GL_POINTS, 0, 10);
	glDrawTransformFeedback(GL_POINTS, 0);

	glEndTransformFeedback();

	glDisable(GL_RASTERIZER_DISCARD);

	glFlush();

	// Fetch and print results
//	GLfloat feedback[30];
	glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(feedback), feedback);

	for (int i = 0; i < 30; i++) {
		printf("%f\n", feedback[i]);
	}



	glDeleteProgram(program);
	glDeleteShader(geoShader);
	glDeleteShader(vertexShader);

	glDeleteBuffers(1, &tbo);
	glDeleteBuffers(1, &vbo);

	glDeleteVertexArrays(1, &vao);


	/*
	// Compile shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShader);

	GLuint geoShader = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geoShader, 1, &geoShaderSrc, NULL);
	glCompileShader(geoShader);

	// Create program and specify transform feedback variables
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, geoShader);

	const GLchar* feedbackVaryings[] = { "outValue" };
	glTransformFeedbackVaryings(program, 1, feedbackVaryings, GL_INTERLEAVED_ATTRIBS);



	//const GLchar* varyings[4];
	//varyings[0] = "Type1";
	//varyings[1] = "Position1";
	//varyings[2] = "Velocity1";
	//varyings[3] = "Age1";

	//glTransformFeedbackVaryings(program, 4, varyings, GL_INTERLEAVED_ATTRIBS);


	glLinkProgram(program);
	glUseProgram(program);


	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create input VBO and vertex format
	GLfloat data[] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };

	Particle particles[10];

	//glGenTransformFeedbacks(2, transformFeedback);
	//glGenBuffers(2, particleBuffer);
	//for (unsigned int i = 0; i < 2; i++) {
	//	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, transformFeedback[i]);
	//	glBindBuffer(GL_ARRAY_BUFFER, particleBuffer[i]);
	//	glBufferData(GL_ARRAY_BUFFER, sizeof(particles), particles, GL_DYNAMIC_DRAW);
	//	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, particleBuffer[i]);
	//}

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

	GLint inputAttrib = glGetAttribLocation(program, "inValue");
	glEnableVertexAttribArray(inputAttrib);
	glVertexAttribPointer(inputAttrib, 1, GL_FLOAT, GL_FALSE, 0, 0);

	// Create transform feedback buffer
	GLuint tbo;
	glGenBuffers(1, &tbo);
	glBindBuffer(GL_ARRAY_BUFFER, tbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data) * 3, nullptr, GL_STATIC_READ);

	// Perform feedback transform
	glEnable(GL_RASTERIZER_DISCARD);

	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tbo);

	glBeginTransformFeedback(GL_TRIANGLES);
	glDrawArrays(GL_POINTS, 0, 5);
	glEndTransformFeedback();

	glDisable(GL_RASTERIZER_DISCARD);

	glFlush();

	// Fetch and print results
	GLfloat feedback[15];
	glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(feedback), feedback);

	for (int i = 0; i < 15; i++) {
		printf("%f\n", feedback[i]);
	}

	glDeleteProgram(program);
	glDeleteShader(geoShader);
	glDeleteShader(vertexShader);

	glDeleteBuffers(1, &tbo);
	glDeleteBuffers(1, &vbo);

	glDeleteVertexArrays(1, &vao);

	*/
}

void ParticleEffect::setShader(Shader shader)
{
	this->shader = shader;
}
