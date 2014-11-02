#pragma once

#define FRACTION 0.1

class Camera
{
private:
	float angle;
	float vectorDirectionX;
	float vectorDirectionZ;
	float xPosition;
	float zPosition;
public:
	Camera(void);
	~Camera(void);

	void TurnLeft ();
	void TurnRight ();
	void TurnUp ();
	void TurnDown ();

	float& GetPositionX ();
	float& GetPositionZ ();
	float& GetVectorX ();
	float& GetVectorZ ();
};

