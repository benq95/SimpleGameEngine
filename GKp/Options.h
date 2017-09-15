#pragma once
#include<vector>

class Options
{
public:
	Options();
	~Options();
	std::string  getActualTexture();
	std::string  getActualShape();


	bool paused;
	bool save=false;
	bool load=false;


	GLfloat ambientStrength;
	glm::vec3 ambientColor;
	enum shape{BRICK,BALL};
	int createShape = BRICK;
	enum type{ SHOOT, PLACE };
	int createType = PLACE;
	std::vector<std::string> textureNames;
	std::string  actualTexture;
	int actualTextureID=0;
	float power=5.0;


};

