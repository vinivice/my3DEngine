#pragma once
#include "Model.h"
#include "Shader.h"
#include <vector>
#include <string>
#include <sstream>
#include <glm\gtc\type_ptr.hpp>


class ModelTree : public Model
{
protected:
	std::vector<ModelTree*> parts;

public:
	ModelTree(ModelType *modelType, glm::vec3 pos, GLfloat r, GLfloat p, GLfloat y, glm::vec3 scale);
	//virtual void update();
	virtual void draw(Shader *shader, GLint level = 0);
	void addPart(ModelTree* part);
};