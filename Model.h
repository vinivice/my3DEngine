#pragma once
#include<glm\glm.hpp>
#include<glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include<vector>
#include <cmath>
#include<iostream>

#include"ModelType.h"
#include"GL\glew.h"
#include"Shader.h"

class Model 
{
protected:
	glm::vec3 position;
	GLfloat roll; //rotate over x
	GLfloat pitch; // rotate over y
	GLfloat yaw; //rotate over z
	glm::vec3 front; //aka x
	glm::vec3 up; // aka y


	ModelType *modelType;

public:
	Model(ModelType *modelType, glm::vec3 pos, GLfloat r, GLfloat p, GLfloat y);
	GLuint getVAO();
	glm::mat4 getModelMatrix();
	void updateVectors();
	void increaseAngles(GLfloat dr, GLfloat dp, GLfloat dy);
	void setAngles(GLfloat r, GLfloat p, GLfloat y);
	void printData();
	//virtual void update();
	virtual void draw(Shader *shader, GLint level = 0);

	/*
	void updatePosition(float dx, float dy, float dz);
	void setPosition(float x, float y, float z);
	void setVectors(glm::vec3 front, glm::vec3 up, glm::vec3 right);
	virtual void updateObject() = 0;
	*/
	
};