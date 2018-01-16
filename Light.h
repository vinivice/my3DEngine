#pragma once
#include "Model.h"
#include "glm\glm.hpp"

class PointLight //: public Model
{
public:
	glm::vec3 power;
	glm::vec3 position;

	PointLight(GLfloat Rp, GLfloat Gp, GLfloat Bp, glm::vec3 pos);
	void setPosition(GLfloat x, GLfloat y, GLfloat z);
	void move(GLfloat dx, GLfloat dy, GLfloat dz);
};