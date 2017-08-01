#pragma once
#include<string> 
#include<GL\glew.h>
#include<glm\glm.hpp>

//singletons for different models
class ModelType {
protected:
	std::string modelName;

	//glm::vec3 *vertices; //3 position, 3 color
	//int *indices;

	GLuint VAO, VBO, EBO;

public:
	ModelType();
	ModelType(std::string name, GLfloat *vertices, GLsizeiptr verticesSize, GLuint *indices, GLsizeiptr indicesSize);
	void setModelType(std::string name, GLfloat *vertices, GLsizeiptr verticesSize, GLuint *indices, GLsizeiptr indicesSize);
	GLuint getVAO();
	
	

};
