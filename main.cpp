#include<iostream>

#define GLEW_STATIC
#include <GL\glew.h>

#include <GLFW/glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include<vector>

#include "Shader.h"
#include"ModelType.h"
#include"Model.h"
#include "Camera.h"

const GLint WIDTH = 800, HEIGHT = 600;
Camera *camera = new Camera();
bool keyPress = false, keyRepeat = false, keyRelease = false;
GLdouble mouseOldX, mouseOldY, mouseNewX, mouseNewY;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if(key == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

int main() {

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Learn", nullptr, nullptr);

	int screedWidth, screedHeight;
	glfwGetFramebufferSize(window, &screedWidth, &screedHeight);

	if (nullptr == window)
	{
		std::cout << "FAIL WINDOW" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit())
	{
		std::cout << "FAIL GLEW" << std::endl;

		return EXIT_FAILURE;
	}

	glViewport(0, 0, screedWidth, screedHeight);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glEnable(GL_DEPTH_TEST);

	Shader ourShader("core.vs", "core.fs");

	glfwSetKeyCallback(window, key_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	GLfloat vertices[] =
	{
		//Position				//Color					
		0.5f, 0.5f, 0.5f,       1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 1.0f

	};

	GLuint indices[] =
	{
		0, 1, 3, //First Triangle
		1, 2, 3 //Second Triangle
	};

	ModelType *Square1 = new ModelType("square", vertices, sizeof(vertices), indices, sizeof(indices));
	ModelType *Square2 = new ModelType("square", vertices, sizeof(vertices), indices, sizeof(indices));
	ModelType *Square3 = new ModelType("square", vertices, sizeof(vertices), indices, sizeof(indices));
	ModelType *Square4 = new ModelType("square", vertices, sizeof(vertices), indices, sizeof(indices));
	std::vector<Model*> modelsVector;

	modelsVector.push_back(new Model(Square1, glm::vec3(-0.5f, 0.5f, -15.0f), 0.0f, 0.0f, 0.0f));
	modelsVector.push_back(new Model(Square2, glm::vec3(0.5f, 0.5f, -10.0f), 0.0f, 0.0f, 0.0f));
	modelsVector.push_back(new Model(Square3, glm::vec3(0.5f, -0.5f, -5.f), 0.0f, 0.0f, 0.0f));
	modelsVector.push_back(new Model(Square4, glm::vec3(-0.5f, -0.5f, -2.0f), 0.0f, 0.0f, 0.0f));

	/*
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	*/
	glm::mat4 viewMatrix = camera->getView();

	glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), (GLfloat)WIDTH / HEIGHT, 0.1f, 100.0f);

	GLfloat oldTime, newTime;
	oldTime = (GLfloat)glfwGetTime();
	glm::mat4 modelMatrix;
	GLint modelLocation, viewLocation, projectionLocation;
	glfwGetCursorPos(window, &mouseOldX, &mouseOldY);


	while (!glfwWindowShouldClose(window))
	{
		newTime = (GLfloat)glfwGetTime();
		glfwPollEvents();
		glfwGetCursorPos(window, &mouseNewX, &mouseNewY);
		
		camera->move(window, newTime - oldTime, mouseNewX - mouseOldX, mouseNewY - mouseOldY, viewMatrix);


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.use();
		/*
		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		transform = glm::rotate(transform, newTime*(-5.0f), glm::vec3(0.0f, 0.0f, 1.0f));

		transformLocation = glGetUniformLocation(ourShader.Program, "transform");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));

		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0);

		*/
		modelLocation = glGetUniformLocation(ourShader.Program, "model");
		viewLocation = glGetUniformLocation(ourShader.Program, "view");
		projectionLocation = glGetUniformLocation(ourShader.Program, "projection");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		for (std::vector<Model*>::iterator it = modelsVector.begin(); it != modelsVector.end(); it++)
		{
			(*it)->increaseAngles(0.0f, 0.0f, (newTime - oldTime)*(5.0f));
			(*it)->updateVectors();
			//(*it)->updateVectors(0.0f, 0.0f, 0.0f);
			modelMatrix = (*it)->getModelMatrix();


			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
			


			glBindVertexArray((*it)->getVAO());
			//glDrawArrays(GL_TRIANGLES, 0, 3);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}

		glBindVertexArray(0);
		glfwSwapBuffers(window);

		oldTime = newTime;
		mouseOldX = mouseNewX;
		mouseOldY = mouseNewY;
	}

	/*
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	*/
	glfwTerminate();

	return EXIT_FAILURE;
}