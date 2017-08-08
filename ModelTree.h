#pragma once
#include "Model.h"
#include <vector>

class ModelTree : public Model
{
protected:
	std::vector<ModelTree*> parts;

public:
	ModelTree(ModelType *modelType, glm::vec3 pos, GLfloat r, GLfloat p, GLfloat y);
	virtual void update();
	virtual void draw(GLboolean willDraw = true);
};