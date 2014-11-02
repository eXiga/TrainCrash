#pragma once
#include "Camera.h"

#define WINDOW_X_POSITION 100
#define WINDOW_Y_POSITION 100
#define WINDOW_HEIGHT 320
#define WINDOW_WIDTH 320
#define APP_NAME "Train Crash"

class GLContext
{
private:
	Camera * _camera;

public:
	GLContext(int * argc, char ** argv);
	~GLContext(void);
	void Start ();

private:
	void Draw (void);
	void KeyboardHandler (int, int, int);
	void ChangeSize (int, int);
};

