#pragma once
#include "Model.h"
#include "glm\glm.hpp"

struct LightInfo
{
	glm::vec3 power;
	glm::vec3 position;
};

class PointLight : public Model
{
public:
	glm::vec3 power;

	PointLight(GLfloat Rp, GLfloat Gp, GLfloat Bp, glm::vec3 pos);
	LightInfo getInfo();
};