#pragma once
#include "Camera.h"

class GLContext
{
private:
	const static int WINDOW_X_POSITION = 100;
	const static int WINDOW_Y_POSITION = 100;
	const static int WINDOW_HEIGHT = 320;
	const static int WINDOW_WIDTH = 320;
protected:
	static GLContext * _context;
	Camera * _camera;	
public:
	GLContext(int * argc, char ** argv);
	~GLContext(void);
	void SetContext (GLContext * context);
	void Start ();

	Camera* GetCamera ();
	void SetCamera (Camera * camera);

private:
	void Draw (void);
	static void DrawWrapper (void);

	void HandleKeyPress (int, int, int);
	static void HandleKeyPressWrapper (int, int, int);

	void ChangeSize (int, int);
	static void ChangeSizeWrapper (int, int);
};

