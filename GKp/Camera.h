#pragma once
//default values
#define DEFAULT_POSITION glm::vec3(0.0f, 0.0f, 3.0f)
#define DEFAULT_WORLD_UP  glm::vec3(0.0f, -1.0f, 0.0f)
#define DEFAULT_YAW -90.0f
#define DEFAULT_PITCH 0.0f
#define DEFAULT_VELO 5.0f
#define DEFAULT_SENSITIVTY 0.2f


/// <summary>
/// klasa reprezetujaca obiekt kamery z ktorej pozycji uzytkownik widzi swiat gry
/// </summary>
class Camera
{
public:

	~Camera();
	Camera(glm::vec3 position = DEFAULT_POSITION, glm::vec3 up = DEFAULT_WORLD_UP, GLfloat yaw = DEFAULT_YAW, GLfloat pitch = DEFAULT_PITCH);
	glm::mat4 GetViewMatrix();
	/// <summary>
	/// metoda wywolywana co klatke. aktualizuje wektory kamery oraz jej pozycje
	/// </summary>
	void update();
	/// <summary>
	/// przemieszcza kamere do przodu (wartosc ujemna przemieszcza do tylu)
	/// </summary>
	void moveForward(GLfloat value);
	///<summary>
	/// przemieszcza kamere w prawo (podanie wartosci ujemnej przemieszcza w lewo)
	///</summary>
	void moveRight(GLfloat value);
	///<summary>
	/// przemieszcza kamere do gory (lub w dol dla wartosci ujemnej)
	///</summary>
	void moveUp(GLfloat value);
	///<summary>
	/// obraca kamere
	///</summary>
	void rotateCamera(GLfloat x,GLfloat y);
	glm::vec3 getPos();
	///<summary>
	/// pobiera wektor wskazujacy kierunek skierowania kamery
	///</summary>
	glm::vec3 getfront();
private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	GLfloat yaw;
	GLfloat pitch;
	glm::vec3 worldUp;
	GLfloat mouseSensitivity;
	GLfloat velocity;

	void updateCameraVectors();
};

