#include "stdafx.h"
#include "Options.h"


Options::Options()
{
	paused = true;
	ambientColor = glm::vec3(200, 200, 200);
	ambientStrength = 0.7;
	power = 5.0;
}


Options::~Options()
{
}

std::string Options::getActualTexture()
{
	return textureNames.at(actualTextureID);
}

std::string Options::getActualShape()
{
	if (createShape == BALL)
		return "ball";
	else
		return "brick";
}

