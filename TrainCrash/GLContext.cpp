#include "GLContext.h"
#include <GL/freeglut.h>
#include <iostream>

GLContext *GLContext::_context = NULL; 
#define MOVEMENT_RATE 0.0004
bool should = false;
double maxHeight;




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
	this->_train = new Model("../Content/Models/Train/train_enginecar.obj");
	this->_train->Scale(2);
	this->_car = new Model("../Content/Models/Car/carA_84sedan.obj");
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

void GLContext::SetTerrain (Terrain * terrain) {
	this->_terrain = terrain;
}

void GLContext::Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	double offset = (MOVEMENT_RATE * glutGet(GLUT_ELAPSED_TIME));
	double fly = offset;
	if (offset > 2.3) {
		should = true;
	}
	glLoadIdentity();
	this->_camera->Look(this->_camera->GetPositionX(), 1.0f, this->_camera->GetPositionZ(),
		this->_camera->GetPositionX() + this->_camera->GetVectorX(), 1.0f,  this->_camera->GetPositionZ() + this->_camera->GetVectorZ(),
		0.0f, 1.0f,  0.0f);

	this->_skybox->Draw();
	this->_terrain->Draw();

	glPushMatrix();
	if (!should) {
		glTranslatef(-3 + offset, -0.3, -1);
	}
	else {
		glTranslatef(-3 + 2.3, -0.3, -1);
	}

	glScalef(3, 3, 3);

	this->_train->Draw();
	glPopMatrix();

	glPushMatrix();
	if(!should) {
		glTranslatef(1, -0.5, -1);
	} else {
		if (offset > 3.1) {
			if (offset > 4.0) {
				glTranslatef(1 + 4.0 - 2.3, maxHeight - (4.0 - 3.1), -1);
			} else {
				glTranslatef(1 + offset - 2.3, maxHeight - (offset - 3.1), -1);
			}

		}
		else {
			maxHeight = -0.5 + fly - 2.3;
			glTranslatef(1 + fly - 2.3, maxHeight, -1 );
		}
	}

	if (!should)
	{
		glRotatef(90, 0, 1, 0);
	} 
	else
	{
		std::cout << offset << std::endl;
		glRotatef(90, 0, 1, 0);
		if (!(offset > 3.2)) {
			glRotatef(offset * 50, 1, 0, 0);
		}
		else {
			glRotatef(3.2 * 50, 1, 0, 0);
		}

	}

	this->_car->Draw();
	glPopMatrix();

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