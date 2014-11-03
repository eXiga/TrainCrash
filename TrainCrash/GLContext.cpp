#include "GLContext.h"
#include <GL/freeglut.h>

GLContext *GLContext::_context = NULL; 

GLContext::GLContext(int * argc, char ** argv) {
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(WINDOW_X_POSITION, WINDOW_Y_POSITION);	
	glutInitWindowSize(WINDOW_HEIGHT, WINDOW_WIDTH);
	glutCreateWindow("Train crash");
	glutDisplayFunc(DrawWrapper);
	glutDisplayFunc(DrawWrapper);
	glutIdleFunc(DrawWrapper);
	glutSpecialFunc(HandleKeyPressWrapper);
	glutReshapeFunc(ChangeSizeWrapper);
	glEnable(GL_DEPTH_TEST);

	this->_camera = new Camera ();
}

GLContext::~GLContext(void) {

}

void GLContext::SetContext(GLContext * context) {
	_context = context;
}

void drawSnowMan() {
	glColor3f(1.0f, 1.0f, 1.0f);

	// Draw Body
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f,20,20);

	// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f,20,20);

	// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f,10,10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f,10,10);
	glPopMatrix();

	// Draw Nose
	glColor3f(1.0f, 0.5f , 0.5f);
	glutSolidCone(0.08f,0.5f,10,2);
}

void GLContext::Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(	this->_camera->GetPositionX(), 1.0f, this->_camera->GetPositionZ(),
		this->_camera->GetPositionX() + this->_camera->GetVectorX(), 1.0f,  this->_camera->GetPositionZ() + this->_camera->GetVectorZ(),
		0.0f, 1.0f,  0.0f);

	// Draw ground
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f,  100.0f);
	glVertex3f( 100.0f, 0.0f,  100.0f);
	glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();

	// Draw 36 SnowMen
	for(int i = -3; i < 3; i++)
		for(int j=-3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i*10.0,0,j * 10.0);
			drawSnowMan();
			glPopMatrix();
		}

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
	gluPerspective(45, ratio, 1, 100);
	glMatrixMode(GL_MODELVIEW);
}

void GLContext::ChangeSizeWrapper(int width, int height) {
	_context->ChangeSize(width, height);
}

void GLContext::Start() {
	glutMainLoop();
}
