#include "ModelTree.h"

ModelTree::ModelTree(ModelType *modelType, glm::vec3 pos, GLfloat r, GLfloat p, GLfloat y) : Model(modelType, pos, r, p, y) {}

void ModelTree::draw(GLboolean willDraw = true)
{
	for (std::vector<ModelTree*>::iterator it = this->parts.begin(); it != this->parts.end(); it++)
	{
		(*it)->draw(false);
	}
}