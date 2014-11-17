#pragma once
#include <gl/freeglut.h>

class Texture
{
private:
	GLuint _textureId;
public:
	Texture();
	~Texture(void);
	GLuint GetTextureId ();
	void LoadTexture(const char * filename);
};

