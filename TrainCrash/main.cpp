#include "GLContext.h"

int main (int argc, char** argv) {
	GLContext * context = new GLContext (&argc, argv);
	Camera * camera = new Camera ();
	context->SetContext(context);
	context->SetCamera(camera);
	context->Start();
	return 0;
}