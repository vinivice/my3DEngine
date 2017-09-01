#include"ModelType.h"

ModelType::ModelType(std::string name, GLfloat *vertices, GLsizeiptr verticesSize, GLuint *indices, GLsizeiptr indicesSize, GLint nVertices)
{
	setModelType(name, vertices, verticesSize, indices, indicesSize, nVertices);
}


void ModelType::setModelType(std::string name, GLfloat *vertices, GLsizeiptr verticesSize, GLuint *indices, GLsizeiptr indicesSize, GLint nVertices)
{
	this->modelName = name;
	glGenVertexArrays(1, &(this->VAO));
	glGenBuffers(1, &(this->VBO));
	glGenBuffers(1, &(this->EBO));

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	this->numberVertices = nVertices;

}

GLuint ModelType::getVAO()
{
	return this->VAO;
}

GLint ModelType::getNumberVertices()
{
	return this->numberVertices;
}
