#include "Camera.h"
#include <math.h>

Camera::Camera(void) {
	this->angle = 0.0f;
	this->vectorDirectionX = 0.0f;
	this->vectorDirectionZ = -1.0f;
	this->xPosition = 0.0f;
	this->zPosition = 5.0f;
}

Camera::~Camera(void) {

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
