#include "GLContext.h"
#include <GL/freeglut.h>

GLContext *GLContext::_context = NULL; 

GLContext::GLContext(int * argc, char ** argv) {
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(WINDOW_X_POSITION, WINDOW_Y_POSITION);	
	glutInitWindowSize(WINDOW_HEIGHT, WINDOW_WIDTH);
	glutCreateWindow("Train crash");
	glutDisplayFunc(DrawWrapper);
	glutIdleFunc(DrawWrapper);
	glutSpecialFunc(HandleKeyPressWrapper);
	glutReshapeFunc(ChangeSizeWrapper);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
}

GLContext::~GLContext(void) {
	
}

void GLContext::SetContext(GLContext * context) {
	_context = context;
}

void GLContext::SetSkybox(Skybox * skybox) {
	_skybox = skybox;
}

void GLContext::SetCamera (Camera * camera) {
	this->_camera = camera;
}

void GLContext::Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
 	this->_camera->Look(this->_camera->GetPositionX(), 1.0f, this->_camera->GetPositionZ(),
 		this->_camera->GetPositionX() + this->_camera->GetVectorX(), 1.0f,  this->_camera->GetPositionZ() + this->_camera->GetVectorZ(),
 		0.0f, 1.0f,  0.0f);
	this->_skybox->Draw();

	glutSwapBuffers();
}

void GLContext::DrawWrapper() {
	_context->Draw();
}

void GLContext::HandleKeyPress(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT :
		this->_camera->TurnLeft();
		break;
	case GLUT_KEY_RIGHT :
		this->_camera->TurnRight();
		break;
	case GLUT_KEY_UP :
		this->_camera->TurnUp();
		break;
	case GLUT_KEY_DOWN :
		this->_camera->TurnDown();
		break;
	}
}

void GLContext::HandleKeyPressWrapper(int key, int x, int y) {
	_context->HandleKeyPress(key, x, y);
}

void GLContext::ChangeSize(int width, int height) {
	if (height == 0) {
		height = 1;
	}
	float ratio =  width * 1.0 / height;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(45, ratio, .5f, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GLContext::ChangeSizeWrapper(int width, int height) {
	_context->ChangeSize(width, height);
}

void GLContext::Start() {
	glutMainLoop();
}
