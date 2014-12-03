#pragma once
#include <gl/freeglut.h>
#include "ModelOBJ.h"

typedef std::map<std::string, GLuint> ModelTextures;

class Model
{
private:
	ModelOBJ _model;
	ModelTextures _textures;
public:
	Model(char * filename);
	~Model(void);
	void Draw ();
private:
	GLuint LoadTexture(const char *pszFilename);
};

