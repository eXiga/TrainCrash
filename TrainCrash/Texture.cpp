#include "Texture.h"
#include "SOIL.h"

Texture::Texture()
{
}

Texture::~Texture(void)
{
}

GLuint Texture::GetTextureId() {
	return this->_textureId;
}

void Texture::LoadTexture(const char * filename) {
	this->_textureId = SOIL_load_OGL_texture (filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
}
