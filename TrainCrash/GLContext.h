#pragma once
#include "Camera.h"
#include "Skybox.h"
#include "Terrain.h"

class GLContext
{
private:
	const static int WINDOW_X_POSITION = 100;
	const static int WINDOW_Y_POSITION = 100;
	const static int WINDOW_HEIGHT = 800;
	const static int WINDOW_WIDTH = 600;
protected:
	static GLContext * _context;
	Camera * _camera;
	Skybox * _skybox;
	Terrain * _terrain;
public:
	GLContext(int * argc, char ** argv);
	~GLContext(void);
	void SetContext (GLContext * context);
	void Start ();

	void SetCamera (Camera * camera);
	void SetSkybox (Skybox * skybox);
	void SetTerrain (Terrain * terrain);
private:
	void Draw (void);
	static void DrawWrapper (void);

	void HandleKeyPress (int, int, int);
	static void HandleKeyPressWrapper (int, int, int);

	void ChangeSize (int, int);
	static void ChangeSizeWrapper (int, int);
};

