#pragma once
#include<glm\glm.hpp>
#include<glm\gtc\matrix_transform.hpp>
#include<vector>
#include"ModelType.h"
#include"GL\glew.h"

class Model 
{
protected:
	glm::vec3 position;
	GLfloat rool; //rotate over x
	GLfloat pitch; // rotate over y
	GLfloat yaw; //rotate over z
	glm::vec3 front;
	glm::vec3 up;


	ModelType *modelType;

public:
	Model(ModelType *modelType, glm::vec3 pos, GLfloat r, GLfloat p, GLfloat y);
	GLuint getVAO();
	glm::mat4 getModelMatrix();
	void updateVectors();
	void increaseAngles(GLfloat dr, GLfloat dp, GLfloat dy);
	void setAngles(GLfloat r, GLfloat p, GLfloat y);
	/*
	void updatePosition(float dx, float dy, float dz);
	void setPosition(float x, float y, float z);
	void setVectors(glm::vec3 front, glm::vec3 up, glm::vec3 right);
	virtual void updateObject() = 0;
	*/
	
};