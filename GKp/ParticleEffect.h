#pragma once
#include "Behaviour.h"
#include "Shader.h"
#include "List"
struct Particle
{
	float Type;
	glm::vec3 pos;
	glm::vec3 vel;
	float lifetime;
};
class ParticleEffect :
	public Behaviour
{
public:
	ParticleEffect();
	~ParticleEffect();
	void update();
	void init();
	void setShader(Shader shader);
private:
	int currVB;
	int currTFB;
	std::list<Particle*> particles;
	GLuint particleBuffer[2];
	GLuint transformFeedback[2];
	Shader shader;
	GLuint program;


	// Vertex shader
	const GLchar* vertexShaderSrc = R"glsl(
	#version 150 core

    in float inValue;
	in vec3 pos;
	in vec3 vel;
    out float geoValue;

    void main()
    {
        geoValue = pos.x+vel.x;
    }
)glsl";

	// Geometry shader
	const GLchar* geoShaderSrc = R"glsl(
	#version 150 core
    layout(points) in;
    layout(triangle_strip, max_vertices = 3) out;

    in float[] geoValue;
    out float outValue;

    void main()
    {
        for (int i = 0; i < 3; i++) {
            outValue = geoValue[0] + i;
            EmitVertex();
        }

        EndPrimitive();
    }
)glsl";
	
//	//vertex shader
//	const GLchar* vertexShaderSrc = R"glsl(
//    #version 330 core
//	layout (location = 0) in float Type;
//	layout (location = 1) in vec3 Position;
//	layout (location = 2) in vec3 Velocity;
//	layout (location = 3) in float Age;
//
//	out float Type0;
//	out vec3 Position0;
//	out vec3 Velocity0;
//	out float Age0;
//
//	void main()
//	{
//		Type0 = Type;
//		Position0 = Position;
//		Velocity0 = Velocity;
//		Age0 = Age;
//	}
//)glsl";
//
//	//geometry shader
//	const GLchar* geoShaderSrc = R"glsl(
//    #version 330
//
//	layout(points) in;
//	layout(points) out;
//	layout(max_vertices = 30) out;
//
//	in float Type0[];
//	in vec3 Position0[];
//	in vec3 Velocity0[];
//	in float Age0[];
//
//	out float Type1;
//	out vec3 Position1;
//	out vec3 Velocity1;
//	out float Age1;
//
//	uniform float gDeltaTimeMillis;
//	uniform float gTime;
//	uniform sampler1D gRandomTexture;
//	uniform float gLauncherLifetime;
//	uniform float gShellLifetime;
//	uniform float gSecondaryShellLifetime;
//
//	#define PARTICLE_TYPE_LAUNCHER 0.0f
//	#define PARTICLE_TYPE_SHELL 1.0f
//	#define PARTICLE_TYPE_SECONDARY_SHELL 2.0f
//
//
//	vec3 GetRandomDir(float TexCoord)
//	{
//		vec3 Dir = texture(gRandomTexture, TexCoord).xyz;
//		Dir -= vec3(0.5, 0.5, 0.5);
//		return Dir;
//	}
//
//
//
//void main()
//{
//    float Age = Age0[0] + gDeltaTimeMillis;
//
//    if (Type0[0] == PARTICLE_TYPE_LAUNCHER) {
//        if (Age >= gLauncherLifetime) {
//            Type1 = PARTICLE_TYPE_SHELL;
//            Position1 = Position0[0];
//            vec3 Dir = GetRandomDir(gTime/1000.0);
//            Dir.y = max(Dir.y, 0.5);
//            Velocity1 = normalize(Dir) / 20.0;
//            Age1 = 0.0;
//            EmitVertex();
//            EndPrimitive();
//            Age = 0.0;
//        }
//
//        Type1 = PARTICLE_TYPE_LAUNCHER;
//        Position1 = Position0[0];
//        Velocity1 = Velocity0[0];
//        Age1 = Age;
//        EmitVertex();
//        EndPrimitive();
//    }
//	 else {
//        float DeltaTimeSecs = gDeltaTimeMillis / 1000.0f;
//        float t1 = Age0[0] / 1000.0;
//        float t2 = Age / 1000.0;
//        vec3 DeltaP = DeltaTimeSecs * Velocity0[0];
//        vec3 DeltaV = vec3(DeltaTimeSecs) * (0.0, -9.81, 0.0);
//
//	if (Type0[0] == PARTICLE_TYPE_SHELL) {
//            if (Age < gShellLifetime) {
//                Type1 = PARTICLE_TYPE_SHELL;
//                Position1 = Position0[0] + DeltaP;
//                Velocity1 = Velocity0[0] + DeltaV;
//                Age1 = Age;
//                EmitVertex();
//                EndPrimitive();
//            }
//            else {
//                for (int i = 0 ; i < 10 ; i++) {
//                    Type1 = PARTICLE_TYPE_SECONDARY_SHELL;
//                    Position1 = Position0[0];
//                    vec3 Dir = GetRandomDir((gTime + i)/1000.0);
//                    Velocity1 = normalize(Dir) / 20.0;
//                    Age1 = 0.0f;
//                    EmitVertex();
//                    EndPrimitive();
//                }
//            }
//        }
//	  else {
//            if (Age < gSecondaryShellLifetime) {
//                Type1 = PARTICLE_TYPE_SECONDARY_SHELL;
//                Position1 = Position0[0] + DeltaP;
//                Velocity1 = Velocity0[0] + DeltaV;
//                Age1 = Age;
//                EmitVertex();
//                EndPrimitive();
//            }
//        }
//    }
//}
//)glsl";
//
};

