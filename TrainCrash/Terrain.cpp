#include "Terrain.h"
#include <gl/freeglut.h>

Terrain::Terrain(void)
{
	this->_terrainTexture = new Texture();
	this->_terrainTexture->LoadTexture("../Content/Textures/Grass.tga");
}


Terrain::~Terrain(void)
{
}

void Terrain::Draw() {
	glPushMatrix();
	glTranslatef(0.0f, -8.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, this->_terrainTexture->GetTextureId());
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-100.0f, 0.0f, -100.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-100.0f, 0.0f,  100.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 100.0f, 0.0f,  100.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();
	glPopMatrix();
}
