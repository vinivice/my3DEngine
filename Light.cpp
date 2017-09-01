#include "Light.h"

PointLight::PointLight(GLfloat Rp, GLfloat Gp, GLfloat Bp, glm::vec3 pos) : Model(NULL, pos, 0.0f, 0.0f, 0.0f, glm::vec3(1.0f))
{
	this->power = glm::vec3(Rp, Gp, Bp);
}

LightInfo PointLight::getInfo()
{
	LightInfo li;
	li.position = this->position;
	li.power = this->power;
	return li;
}