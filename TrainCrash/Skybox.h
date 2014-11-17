#pragma once
#include <gl/freeglut.h>
#include "Texture.h"

class Skybox
{
private:
	const static int X_POSITION = -200;
	const static int Y_POSITION = -100;
	const static int Z_POSITION = -200;
	const static int WIDTH = 400;
	const static int HEIGHT = 200;
	const static int LENGTH = 400;

	Texture * _textures;
public:
	Skybox(void);
	~Skybox(void);
	void Draw();
private:
	void DrawFrontFace ();
	void DrawLeftFace ();
	void DrawBackFace ();
	void DrawRightFace ();
	void DrawUpFace ();
	void DrawDownFace ();
};

