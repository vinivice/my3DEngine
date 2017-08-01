#include "Model.h"

Model::Model(ModelType *modelType, glm::vec3 pos, GLfloat r, GLfloat p, GLfloat y)
{
	this->modelType = modelType;
	this->position = pos;
	this->front = glm::vec3(1.0f, 0.0f, 0.0f);
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->yaw = y;
	this->pitch = p;
	this->rool = r;
	this->updateVectors();
}

GLuint Model::getVAO()
{
	return this->modelType->getVAO();
}

glm::mat4 Model::getModelMatrix()
{
	glm::vec3 right = glm::normalize(glm::cross(this->front, this->up));
	glm::mat4 model;
	model = glm::translate(model, this->position);
	model[0] = glm::vec4(this->front, 0.0f);
	model[1] = glm::vec4(this->up, 0.0f);
	model[2] = glm::vec4(right, 0.0f);
	//model = glm::scale(model, glm::vec3(1.0f)); //not used yet

	return model;
}

void Model::updateVectors()
{
	//incomplete
	this->front = glm::normalize(glm::vec3(
		cos(glm::radians(this->yaw))*cos(glm::radians(this->pitch)),
		sin(glm::radians(this->yaw)),
		cos(glm::radians(this->yaw))*(-sin(glm::radians(this->pitch)))
	));

	glm::vec3 right = glm::normalize(glm::cross(this->front, glm::vec3(0.0f, 1.0f, 0.0f)));
	this->up = glm::normalize(glm::cross(right, this->front));


}

void Model::increaseAngles(GLfloat dr, GLfloat dp, GLfloat dy)
{
	this->rool += dr;
	this->pitch += dp;
	this->yaw += dy;
}

void Model::setAngles(GLfloat r, GLfloat p, GLfloat y)
{
	this->rool = r;
	this->pitch = p;
	this->yaw = y;
}