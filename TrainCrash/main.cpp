#include "GLContext.h"

int main (int argc, char** argv) {
	GLContext * context = new GLContext (&argc, argv);
	context->Start();
	return 0;
}