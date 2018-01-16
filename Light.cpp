#include "Light.h"

PointLight::PointLight(GLfloat Rp, GLfloat Gp, GLfloat Bp, glm::vec3 pos) //: Model(NULL, pos, 0.0f, 0.0f, 0.0f, glm::vec3(1.0f))
{
	this->power = glm::vec3(Rp, Gp, Bp);
	this->position = pos;
}

void PointLight::setPosition(GLfloat x, GLfloat y, GLfloat z)
{
	this->position = glm::vec3(x, y, z);
}

void PointLight::move(GLfloat dx, GLfloat dy, GLfloat dz)
{
	this->position += glm::vec3(dx, dy, dz);
}