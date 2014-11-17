#pragma once
#include "Texture.h"

class Terrain
{
private:
	Texture * _terrainTexture;
public:
	Terrain(void);
	~Terrain(void);
	void Draw ();
};

