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
#include"ModelTree.h"
#include "Camera.h"
#include "Light.h"

//TEMPORARY FOR TEST************************************************
GLfloat ka, kd, ks, omega = 0.1f;
GLint n;
//******************************************************************

const GLint WIDTH = 800, HEIGHT = 600;
Camera *camera = new Camera();
PointLight *pointLight = new PointLight(100.0f, 100.0f, 100.0f, glm::vec3(0.0f));
bool keyPress = false, keyRepeat = false, keyRelease = false;
GLdouble mouseOldX, mouseOldY, mouseNewX, mouseNewY;

GLboolean run = false;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if(key == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	else if (key == GLFW_KEY_B && action == GLFW_PRESS)
	{
		run = !run;
	}
	else if (key == GLFW_KEY_M && action == GLFW_PRESS)
	{
		omega += 0.1;
	}
	else if (key == GLFW_KEY_N && action == GLFW_PRESS)
	{
		omega -= 0.1;
	}
}

int main() {
	//TEMPORARY FOR TEST************************************************
	ka = kd = ks = 1.0f;
	n = 2;
	//******************************************************************

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

	glEnable(GL_DEPTH_TEST);

	Shader ourShader("core.vs", "core.fs");

	glfwSetKeyCallback(window, key_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	GLfloat verticesCube[] =
	{
		//position				//color					//Normal
		0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 0.0f,		1.0f / sqrtf(3), 1.0f / sqrtf(3), 1.0f / sqrtf(3),
		0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 0.0f,		1.0f / sqrtf(3), 1.0f / sqrtf(3), -1.0f / sqrtf(3),
		0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,		1.0f / sqrtf(3), -1.0f / sqrtf(3), 1.0f / sqrtf(3),
		0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 1.0f,		1.0f / sqrtf(3), -1.0f / sqrtf(3), -1.0f / sqrtf(3),
		-0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		-1.0f / sqrtf(3), 1.0f / sqrtf(3), 1.0f / sqrtf(3),
		-0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 1.0f,		-1.0f / sqrtf(3), 1.0f / sqrtf(3), -1.0f / sqrtf(3),
		-0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 1.0f,		-1.0f / sqrtf(3), -1.0f / sqrtf(3), 1.0f / sqrtf(3),
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		-1.0f / sqrtf(3), -1.0f / sqrtf(3), -1.0f / sqrtf(3)
	};

	GLuint indicesCube[] =
	{
		0, 1, 2, //R1
		1, 2, 3, //R2
		4, 5, 6, //L1
		5, 6, 7, //L2
		0, 1, 4, //Up1
		1, 4, 5, //Up2
		2, 3, 6, //Bot1
		3, 6, 7, //Bot2
		0, 2, 4, //Front1
		2, 4, 6, //Front2
		1, 3, 5, //Back1
		3, 5, 7 //Back2
	};
	
	GLfloat verticesSquare[] =
	{
		//Position				//Color					//Normal
		1.0f, 1.0f, 0.0f,       0.0f, 0.0f, 1.0f,		0.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, 0.0f,		1.0f, 1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f

	};

	GLuint indicesSquare[] =
	{
		0, 1, 3, //First Triangle
		1, 2, 3 //Second Triangle
	};

	ModelType *Square = new ModelType("square", verticesSquare, sizeof(verticesSquare), indicesSquare, sizeof(indicesSquare), 6);
	ModelType *Cube = new ModelType("cube", verticesCube, sizeof(verticesCube), indicesCube, sizeof(indicesCube), 36);
	Model *LModel;
	std::vector<Model*> modelsVector;

	modelsVector.push_back(new Model(Square, glm::vec3(-0.5f, 0.5f, -15.0f), 0.0f, 0.0f, 0.0f, glm::vec3(0.5f)));
	modelsVector.push_back(new Model(Square, glm::vec3(0.5f, 0.5f, -10.0f), 0.0f, 0.0f, 0.0f, glm::vec3(0.5f)));
	modelsVector.push_back(new Model(Square, glm::vec3(0.5f, -0.5f, -5.f), 0.0f, 0.0f, 0.0f, glm::vec3(0.5f)));
	modelsVector.push_back(new Model(Square, glm::vec3(-0.5f, -0.5f, -2.0f), 0.0f, 0.0f, 0.0f, glm::vec3(0.5f)));

	modelsVector.push_back(new Model(Cube, glm::vec3(-0.5f, -0.5f, -25.0f), 0.0f, 0.0f, 0.0f, glm::vec3(0.5f)));
	LModel = new Model(Cube, glm::vec3(-0.5f, -0.5f, -25.0f), 0.0f, 0.0f, 0.0f, glm::vec3(0.1f));
	modelsVector.push_back(LModel);

	ModelTree *tempModelTree = new ModelTree(NULL, glm::vec3(0.0f, 0.0f, -20.0f), 0.0f, 0.0f, 0.0f, glm::vec3(0.5f));

	tempModelTree->addPart(new ModelTree(Square, glm::vec3(0.5f, 0.0f, 0.0f), 0.0f, -90.0f, 0.0f, glm::vec3(0.5f)));
	tempModelTree->addPart(new ModelTree(Square, glm::vec3(-0.5f, 0.0f, 0.0f), 0.0f, 90.0f, 0.0f, glm::vec3(0.5f)));
	tempModelTree->addPart(new ModelTree(Square, glm::vec3(0.0f, 0.5f, 0.0f), 90.0f, 0.0f, 0.0f, glm::vec3(0.5f)));
	tempModelTree->addPart(new ModelTree(Square, glm::vec3(0.0f, -0.5f, 0.0f), -90.0f, 0.0f, 0.0f, glm::vec3(0.5f)));
	tempModelTree->addPart(new ModelTree(Square, glm::vec3(0.0f, 0.0f, 0.5f), 0.0f, 0.0f, 0.0f, glm::vec3(0.5f)));
	tempModelTree->addPart(new ModelTree(Square, glm::vec3(0.0f, 0.0f, -0.5f), 0.0f, 0.0f, 0.0f, glm::vec3(0.5f)));

	modelsVector.push_back(tempModelTree);

	tempModelTree = new ModelTree(NULL, glm::vec3(0.0f, 0.0f, -40.0f), 0.0f, 0.0f, 0.0f, glm::vec3(0.5f));

	tempModelTree->addPart(new ModelTree(Cube, glm::vec3(0.0f, 0.50f, 0.0f), 0.0f, 0.0f, 0.0f, glm::vec3(0.20f)));
	tempModelTree->addPart(new ModelTree(Cube, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, glm::vec3(0.5f, 0.80f, 0.25f)));
	tempModelTree->addPart(new ModelTree(Cube, glm::vec3(0.30f, 0.10f, 0.0f), 0.0f, 0.0f, 0.0f, glm::vec3(0.10f, 0.5f, 0.10f)));
	tempModelTree->addPart(new ModelTree(Cube, glm::vec3(-0.30f, 0.10f, 0.0f), 0.0f, 0.0f, 0.0f, glm::vec3(0.10f, 0.5f, 0.10f)));
	tempModelTree->addPart(new ModelTree(Cube, glm::vec3(0.10f, -0.75f, 0.0f), 0.0f, 0.0f, 0.0f, glm::vec3(0.10f, 0.70f, 0.10f)));
	tempModelTree->addPart(new ModelTree(Cube, glm::vec3(-0.10f, -0.75f, 0.0f), 0.0f, 0.0f, 0.0f, glm::vec3(0.10f, 0.70f, 0.10f)));


	modelsVector.push_back(tempModelTree);


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

	GLfloat oldTime, newTime, dt;
	oldTime = (GLfloat)glfwGetTime();
	glm::mat4 modelMatrix;
	GLint modelLocation, viewLocation, projectionLocation, lightPowerLocation, lightPositionLocation, tempLightConstsLocation;
	glfwGetCursorPos(window, &mouseOldX, &mouseOldY);


	while (!glfwWindowShouldClose(window))
	{
		newTime = (GLfloat)glfwGetTime();
		dt = newTime - oldTime;
		glfwPollEvents();
		glfwGetCursorPos(window, &mouseNewX, &mouseNewY);
		
		camera->move(window, dt, mouseNewX - mouseOldX, mouseNewY - mouseOldY, viewMatrix);

		pointLight->setPosition(0.0f, 1.0f*sin(omega*newTime), -20.0f + 10.0f*cos(omega*newTime));
		LModel->setPosition(pointLight->position);
		std::cout << pointLight->position.x << ", " << pointLight->position.y << ", " << pointLight->position.z << std::endl;
		lightPowerLocation = glGetUniformLocation(ourShader.Program, "lightPower");
		lightPositionLocation = glGetUniformLocation(ourShader.Program, "lightPosition");
		glUniform3fv(lightPowerLocation, 1, glm::value_ptr(pointLight->power));
		glUniform3fv(lightPositionLocation, 1, glm::value_ptr(pointLight->position));
		tempLightConstsLocation = glGetUniformLocation(ourShader.Program, "temporaryLightConstants");
		glUniform4f(tempLightConstsLocation, ka, kd, ks, n);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
		modelLocation = glGetUniformLocation(ourShader.Program, "model[0]");
		viewLocation = glGetUniformLocation(ourShader.Program, "view");
		projectionLocation = glGetUniformLocation(ourShader.Program, "projection");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		for (std::vector<Model*>::iterator it = modelsVector.begin(); it != modelsVector.end(); it++)
		{
			if (run)
			{
				(*it)->turn(0.0f, 0.0f, dt*(15.0f));
				(*it)->updateVectors();
				//(*it)->printData();
			}
			/*
			modelMatrix = (*it)->getModelMatrix();


			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));



			glBindVertexArray((*it)->getVAO());
			//glDrawArrays(GL_TRIANGLES, 0, 3);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			*/
			(*it)->draw(&ourShader);
		}
	
		glBindVertexArray(0);
		glfwSwapBuffers(window);

		//std::cout << "FPS: " << 1 / (newTime - oldTime) << "\n";
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