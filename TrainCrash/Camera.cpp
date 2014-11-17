#include "Camera.h"
#include <math.h>
#include <gl/freeglut.h>

Camera::Camera(void) {
	this->angle = 0.0f;
	this->vectorDirectionX = 0.0f;
	this->vectorDirectionZ = -1.0f;
	this->xPosition = 0.0f;
	this->zPosition = 5.0f;
}

Camera::~Camera(void) {

}

void Camera::Look(double eyex, double eyey, double eyez, double centerx, double centery, double centerz, double upx, double upy, double upz) {
	gluLookAt(eyex, eyey, eyez,
		centerx, centery, centerz,
		upx, upy, upz);
}

void Camera::TurnLeft() {
	this->angle -= 0.01f;
	this->vectorDirectionX = sin(this->angle);
	this->vectorDirectionZ = -cos(this->angle);
}

void Camera::TurnRight() {
	this->angle += 0.01f;
	this->vectorDirectionX = sin(this->angle);
	this->vectorDirectionZ = -cos(this->angle);
}

void Camera::TurnDown() {
	this->xPosition -= vectorDirectionX * FRACTION;
	this->zPosition -= vectorDirectionZ * FRACTION;
}

void Camera::TurnUp() {
	this->xPosition += vectorDirectionX * FRACTION;
	this->zPosition += vectorDirectionZ * FRACTION;
}

float& Camera::GetVectorX() {
	return this->vectorDirectionX;
}

float& Camera::GetVectorZ() {
	return this->vectorDirectionZ;
}

float& Camera::GetPositionX() {
	return this->xPosition;
}

float& Camera::GetPositionZ() {
	return this->zPosition;
}
