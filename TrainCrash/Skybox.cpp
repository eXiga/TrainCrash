#include "Skybox.h"

Skybox::Skybox(void)
{
	this->_textures = new Texture[6];
	this->_textures[0].LoadTexture("../Content/Skybox/jajlands1_ft.jpg");
	this->_textures[1].LoadTexture("../Content/Skybox/jajlands1_lf.jpg");
	this->_textures[2].LoadTexture("../Content/Skybox/jajlands1_bk.jpg");
	this->_textures[3].LoadTexture("../Content/Skybox/jajlands1_rt.jpg");
	this->_textures[4].LoadTexture("../Content/Skybox/jajlands1_up.jpg");
	this->_textures[5].LoadTexture("../Content/Skybox/jajlands1_dn.jpg");
}

Skybox::~Skybox(void)
{
	delete[] this->_textures;
}

void Skybox::Draw() 
{
	glPushAttrib(GL_ENABLE_BIT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);

	this->DrawFrontFace();
	this->DrawLeftFace();
	this->DrawBackFace();
	this->DrawRightFace();
	this->DrawUpFace();
	this->DrawDownFace();

	glPopAttrib();
	glPopMatrix();
}

void Skybox::DrawFrontFace() {
	glBindTexture(GL_TEXTURE_2D, this->_textures[0].GetTextureId());
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(X_POSITION, Y_POSITION, Z_POSITION + LENGTH);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(X_POSITION, Y_POSITION + HEIGHT, Z_POSITION + LENGTH);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(X_POSITION + WIDTH, Y_POSITION + HEIGHT, Z_POSITION + LENGTH);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(X_POSITION + WIDTH, Y_POSITION, Z_POSITION + LENGTH);
	glEnd();
}

void Skybox::DrawLeftFace() {
	glBindTexture(GL_TEXTURE_2D, this->_textures[1].GetTextureId());
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(X_POSITION, Y_POSITION + HEIGHT, Z_POSITION);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(X_POSITION, Y_POSITION + HEIGHT, Z_POSITION + LENGTH);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(X_POSITION, Y_POSITION, Z_POSITION + LENGTH);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(X_POSITION, Y_POSITION, Z_POSITION);
	glEnd();
}

void Skybox::DrawBackFace() {
	glBindTexture(GL_TEXTURE_2D, this->_textures[2].GetTextureId());
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(X_POSITION + WIDTH, Y_POSITION, Z_POSITION);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(X_POSITION + WIDTH, Y_POSITION + HEIGHT, Z_POSITION);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(X_POSITION, Y_POSITION + HEIGHT, Z_POSITION);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(X_POSITION, Y_POSITION, Z_POSITION);
	glEnd();
}

void Skybox::DrawRightFace() {
	glBindTexture(GL_TEXTURE_2D, this->_textures[3].GetTextureId());
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(X_POSITION + WIDTH, Y_POSITION, Z_POSITION);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(X_POSITION + WIDTH, Y_POSITION, Z_POSITION + LENGTH);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(X_POSITION + WIDTH, Y_POSITION + HEIGHT, Z_POSITION + LENGTH);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(X_POSITION + WIDTH, Y_POSITION + HEIGHT, Z_POSITION);
	glEnd();
}

void Skybox::DrawUpFace() {
	glBindTexture(GL_TEXTURE_2D, this->_textures[4].GetTextureId());
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(X_POSITION + WIDTH, Y_POSITION + HEIGHT, Z_POSITION);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(X_POSITION + WIDTH, Y_POSITION + HEIGHT, Z_POSITION + LENGTH);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(X_POSITION, Y_POSITION + HEIGHT,Z_POSITION + LENGTH);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(X_POSITION, Y_POSITION + HEIGHT, Z_POSITION);
	glEnd();
}

void Skybox::DrawDownFace() {
	glBindTexture(GL_TEXTURE_2D, this->_textures[5].GetTextureId());
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(X_POSITION, Y_POSITION, Z_POSITION);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(X_POSITION, Y_POSITION, Z_POSITION + LENGTH);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(X_POSITION + WIDTH, Y_POSITION, Z_POSITION + LENGTH);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(X_POSITION + WIDTH, Y_POSITION, Z_POSITION);
	glEnd();
}
