#pragma once
#include "GLM.h"

class Model
{
private:
	GLMmodel * _model;
public:
	Model(char * filename);
	~Model(void);
	void Draw ();
};

