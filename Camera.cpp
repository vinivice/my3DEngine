#include "Camera.h"
#include<iostream>

Camera::Camera() :Model(NULL, glm::vec3(0.0f), 0.0f, 90.0f, 0.0f)
{
	//chande initialization
	this->moveMode = 0;
	this->linearSpeed = 5.0f;
	this->angularSpeed = 25.0f;
}

glm::mat4 Camera::getView()
{
	return glm::lookAt(this->position, this->position + this->front, glm::vec3(0.0f, 1.0f, 0.0f));
}
/*
void Camera::camera_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	
	if (glfwGetKey(window, GLFW_KEY_W) != GLFW_RELEASE)
	{
		this->moveMode = this->moveMode | FORWARD;
	}

	if (glfwGetKey(window, GLFW_KEY_S) != GLFW_RELEASE)
	{
		this->moveMode = this->moveMode | BACKWARD;
	}

	if (glfwGetKey(window, GLFW_KEY_D) != GLFW_RELEASE)
	{
		this->moveMode = this->moveMode | RIGHT;
	}

	if (glfwGetKey(window, GLFW_KEY_A) != GLFW_RELEASE)
	{
		this->moveMode = this->moveMode | LEFT;
	}
	//std::cout << "MOVEMODE: " << (unsigned int)this->moveMode << std::endl;
}
*/
void Camera::move(GLFWwindow* window, GLfloat dt, GLdouble mousedx, GLdouble mousedy, glm::mat4 &view)
{
	bool update = false;
	glm::vec3 right = glm::normalize(glm::cross(this->front, this->up));
	glm::vec3 ds(0.0f);

//	if ((this->moveMode & FORWARD) != 0)
	if (glfwGetKey(window, GLFW_KEY_W) != GLFW_RELEASE)
	{
		ds += this->front;
	}

	//if ((this->moveMode & BACKWARD) != 0)
	if (glfwGetKey(window, GLFW_KEY_S) != GLFW_RELEASE)
	{
		ds -= this->front;
	}

	//if ((this->moveMode & RIGHT) != 0)
	if (glfwGetKey(window, GLFW_KEY_D) != GLFW_RELEASE)
	{
		ds += right;
	}

	//if ((this->moveMode & LEFT) != 0)
	if (glfwGetKey(window, GLFW_KEY_A) != GLFW_RELEASE)
	{
		ds -= right;
	}

	if (glm::length(ds) > PRECISION)
	{
		this->position += this->linearSpeed*dt*glm::normalize(ds);
		update = true;
	}
	//std::cout << "POSITION: " << this->position.x << " " << this->position.y << " " << this->position.z << std::endl;

	//std::cout << mousedx << " " << mousedy << std::endl;
	if (mousedx > PRECISION || mousedx < -PRECISION)
	{
		this->pitch -= mousedx*this->angularSpeed*dt;
		while (this->pitch >= 360.0f)
		{
			this->pitch -= 360.0f;
		}

		while (this->pitch < 0.0f)
		{
			this->pitch += 360.0f;
		}
		update = true;
	}

	if (mousedy > PRECISION || mousedy < -PRECISION)
	{
		this->yaw -= mousedy*this->angularSpeed*dt;
		if (this->yaw > 89.0f)
		{
			this->yaw = 89.0f;
		}

		if (this->yaw < -89.0f)
		{
			this->yaw = -89.0f;
		}
		update = true;
	}

	if (update)
	{
		this->moveMode = 0;
		this->updateVectors();
		view = this->getView();
		std::cout << "front " << front.x << "\t" << front.y << "\t" << front.z << std::endl;
		std::cout << "up " << up.x << "\t" << up.y << "\t" << up.z << std::endl;

	}
}