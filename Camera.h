#pragma once
#include "Model.h"
#include"GLFW\glfw3.h"

#define PRECISION 0.001f

class Camera : public Model
{
protected:
	unsigned char moveMode;
	GLfloat linearSpeed, angularSpeed;
public:
	Camera();
	glm::mat4 getView();
	//void camera_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void move(GLFWwindow* window, GLfloat dt, GLdouble mousedx, GLdouble mousedy, glm::mat4 &view);
};