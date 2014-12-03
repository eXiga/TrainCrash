#include "Model.h"
#include "Bitmap.h"
#include <windows.h>
#include <cassert>
#include <cmath>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

GLuint LoadTexture(const char *pszFilename);

Model::Model(char * filename)
{
	_model.import(filename);
	_model.normalize();

	// Load any associated textures.
	// Note the path where the textures are assumed to be located.

	const ModelOBJ::Material *pMaterial = 0;
	GLuint textureId = 0;
	std::string::size_type offset = 0;
	std::string _filename;

	for (int i = 0; i < _model.getNumberOfMaterials(); ++i)
	{
		pMaterial = &_model.getMaterial(i);

		// Look for and load any diffuse color map textures.

		if (pMaterial->colorMapFilename.empty())
			continue;

		// Try load the texture using the path in the .MTL file.
		textureId = LoadTexture(pMaterial->colorMapFilename.c_str());

		if (!textureId)
		{
			offset = pMaterial->colorMapFilename.find_last_of('\\');

			if (offset != std::string::npos)
				_filename = pMaterial->colorMapFilename.substr(++offset);
			else
				_filename = pMaterial->colorMapFilename;

			// Try loading the texture from the same directory as the OBJ file.
			textureId = LoadTexture((_model.getPath() + _filename).c_str());
		}

		if (textureId)
			_textures[pMaterial->colorMapFilename] = textureId;

		// Look for and load any normal map textures.

		if (pMaterial->bumpMapFilename.empty())
			continue;

		// Try load the texture using the path in the .MTL file.
		textureId = LoadTexture(pMaterial->bumpMapFilename.c_str());

		if (!textureId)
		{
			offset = pMaterial->bumpMapFilename.find_last_of('\\');

			if (offset != std::string::npos)
				_filename = pMaterial->bumpMapFilename.substr(++offset);
			else
				_filename = pMaterial->bumpMapFilename;

			// Try loading the texture from the same directory as the OBJ file.
			textureId = this->LoadTexture((_model.getPath() + _filename).c_str());
		}

		if (textureId)
			_textures[pMaterial->bumpMapFilename] = textureId;
	}
}

GLuint Model::LoadTexture(const char *pszFilename)
{
	GLuint id = 0;
	Bitmap bitmap;

	if (bitmap.loadPicture(pszFilename))
	{
		// The Bitmap class loads images and orients them top-down.
		// OpenGL expects bitmap images to be oriented bottom-up.
		bitmap.flipVertical();

		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		gluBuild2DMipmaps(GL_TEXTURE_2D, 4, bitmap.width, bitmap.height,
			GL_BGRA_EXT, GL_UNSIGNED_BYTE, bitmap.getPixels());
	}

	return id;
}


Model::~Model(void)
{
	//glmDelete(this->_model);
}

void Model::Draw() {
	//glmDraw(this->_model, GLM_SMOOTH |  GLM_MATERIAL);
	const ModelOBJ::Mesh *pMesh = 0;
	const ModelOBJ::Material *pMaterial = 0;
	const ModelOBJ::Vertex *pVertices = 0;
	ModelTextures::const_iterator iter;

	for (int i = 0; i < _model.getNumberOfMeshes(); ++i)
	{
		pMesh = &_model.getMesh(i);
		pMaterial = pMesh->pMaterial;
		pVertices = _model.getVertexBuffer();

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pMaterial->ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, pMaterial->diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, pMaterial->specular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, pMaterial->shininess * 128.0f);

		iter = _textures.find(pMaterial->colorMapFilename);

		if (iter == _textures.end())
		{
			glDisable(GL_TEXTURE_2D);
		}
		else
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, iter->second);
		}

		if (_model.hasPositions())
		{
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, _model.getVertexSize(),
				_model.getVertexBuffer()->position);
		}

		if (_model.hasTextureCoords())
		{
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, _model.getVertexSize(),
				_model.getVertexBuffer()->texCoord);
		}

		if (_model.hasNormals())
		{
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_FLOAT, _model.getVertexSize(),
				_model.getVertexBuffer()->normal);
		}

		glDrawElements(GL_TRIANGLES, pMesh->triangleCount * 3, GL_UNSIGNED_INT,
			_model.getIndexBuffer() + pMesh->startIndex);

		if (_model.hasNormals())
			glDisableClientState(GL_NORMAL_ARRAY);

		if (_model.hasTextureCoords())
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		if (_model.hasPositions())
			glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void Model::Scale(float scaleFactor) {
	//glmScale(this->_model, scaleFactor);
}
