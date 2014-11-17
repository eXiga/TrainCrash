#include "GLContext.h"

int main (int argc, char** argv) {
	GLContext * context = new GLContext (&argc, argv);
	Camera * camera = new Camera ();
	Skybox * skybox = new Skybox ();
	context->SetContext(context);
	context->SetCamera(camera);
	context->SetSkybox(skybox);
	context->Start();
	return 0;
}