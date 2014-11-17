#include "GLContext.h"

int main (int argc, char** argv) {
	GLContext * context = new GLContext (&argc, argv);
	Camera * camera = new Camera ();
	Skybox * skybox = new Skybox ();
	Terrain * terrain = new Terrain ();
	context->SetContext(context);
	context->SetCamera(camera);
	context->SetSkybox(skybox);
	context->SetTerrain(terrain);
	context->Start();
	return 0;
}