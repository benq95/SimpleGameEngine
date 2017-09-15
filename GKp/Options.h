#pragma once
#include<vector>
///<summary>
/// klasa przedstawiajaca opcje w grze. Z jej wartosci korzysta klasa glowna gry Game. Jest edytowana przez klase NKwindow
///</summary>
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
	///<summary>
	/// wektor przechowujacy nazwy tekstur. na jego podstawie generowane jest menu sluzace do wyboru tekstury 
	///</summary>
	std::vector<std::string> textureNames;
	///<summary>
	///  nazwa aktualnie 
	///</summary>
	std::string  actualTexture;
	int actualTextureID=0;
	float power=5.0;


};

