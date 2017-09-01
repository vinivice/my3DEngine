#include "Model.h"

Model::Model(ModelType *modelType, glm::vec3 pos, GLfloat r, GLfloat p, GLfloat y, glm::vec3 scale)
{
	this->modelType = modelType;
	this->position = pos;
	this->front = glm::vec3(1.0f, 0.0f, 0.0f);
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->yaw = y;
	this->pitch = p;
	this->roll = r;
	this->updateVectors();
	this->scale = scale;
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
	model[0] = glm::vec4(this->scale.x*this->front, 0.0f);
	model[1] = glm::vec4(this->scale.y*this->up, 0.0f);
	model[2] = glm::vec4(this->scale.z*right, 0.0f);
	//model = glm::scale(model, glm::vec3(1.0f)); //not used yet

	return model;
}

void Model::updateVectors()
{
	GLfloat cx, sx, cy, sy, cz, sz;

	cx = cos(glm::radians(this->roll));
	sx = sin(glm::radians(this->roll));

	cy = cos(glm::radians(this->pitch));
	sy = sin(glm::radians(this->pitch));

	cz = cos(glm::radians(this->yaw));
	sz = sin(glm::radians(this->yaw));

	//incomplete
	this->front = glm::normalize(glm::vec3(
					cy*cz,
					sx*sy*cz + cx*sz,
					sx*sz - cx*sy*cz
	));

	/*glm::vec3 right = glm::normalize(glm::cross(this->front, glm::vec3(0.0f, 1.0f, 0.0f)));
	this->up = glm::normalize(glm::cross(right, this->front));
	*/
	
	this->up = glm::normalize(glm::vec3(
		-cy*sz,
		cx*cz - sx*sy*sz,
		cx*sy*sz + sx*cz
	));

}

void Model::increaseAngles(GLfloat dr, GLfloat dp, GLfloat dy)
{
	//this->rool += dr;
	//this->pitch += dp;
	//this->yaw += dy;

	this->roll = fmod(this->roll + dr, 360.0f);
	this->pitch = fmod(this->pitch + dp, 360.0f);
	this->yaw = fmod(this->yaw + dy, 360.0f);
}

void Model::setAngles(GLfloat r, GLfloat p, GLfloat y)
{
	this->roll = r;
	this->pitch = p;
	this->yaw = y;
}

void Model::printData()
{
	//std::cout << "Position(" << this->position.x << ", " << this->position.y << ", " << this->position.z << ")\nAngle(" << this->rool << ", " << this->pitch << ", " << this->yaw << ")\n";
	std::cout << "Front(" << this->front.x << ", " << this->front.y << ", " << this->front.z << ")\nUp(" << this->up.x << ", " << this->up.y << ", " << this->up.z  << ")\n";
}

void Model::draw(Shader *shader, GLint level)
{
	GLint modelLocation = glGetUniformLocation(shader->Program, "model[0]");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->getModelMatrix()));

	GLint levelLocation = glGetUniformLocation(shader->Program, "level");
	glUniform1i(levelLocation, level);

	glBindVertexArray(this->getVAO());
	glDrawElements(GL_TRIANGLES, this->modelType->getNumberVertices(), GL_UNSIGNED_INT, 0);

}
