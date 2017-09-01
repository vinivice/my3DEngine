#include "ModelTree.h"

ModelTree::ModelTree(ModelType *modelType, glm::vec3 pos, GLfloat r, GLfloat p, GLfloat y, glm::vec3 scale) : Model(modelType, pos, r, p, y, scale) {}

void ModelTree::draw(Shader *shader, GLint level)
{
	if (level < 10)
	{
		std::ostringstream ssLevel;
		ssLevel << level;
		std::string location = "model[" + ssLevel.str() + "]";
		
		GLint modelLocation = glGetUniformLocation(shader->Program, location.c_str());
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->getModelMatrix()));


		for (std::vector<ModelTree*>::iterator it = this->parts.begin(); it != this->parts.end(); it++)
		{
			(*it)->draw(shader, level+1);
		}

		if (this->parts.empty() && this->modelType != NULL)
		{
			GLint levelLocation = glGetUniformLocation(shader->Program, "level");
			glUniform1i(levelLocation, level);

			glBindVertexArray(this->getVAO());
			glDrawElements(GL_TRIANGLES, this->modelType->getNumberVertices(), GL_UNSIGNED_INT, 0);
		}
	}
	
}

void ModelTree::addPart(ModelTree* part)
{
	this->parts.push_back(part);
}