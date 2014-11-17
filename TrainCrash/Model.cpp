#include "Model.h"


Model::Model(char * filename)
{
	_model = glmReadOBJ(filename);
	glmUnitize(_model);
	glmFacetNormals(_model);
	glmVertexNormals(_model, 90.0);
}


Model::~Model(void)
{
}

void Model::Draw() {
	glmDraw(this->_model, GLM_SMOOTH | GLM_MATERIAL);
}
