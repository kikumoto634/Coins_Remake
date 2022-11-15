#include "Camera.h"

#include <iostream>
#include <random>

//using namespace DirectX;

Camera *Camera::GetInstance()
{
	static Camera instance;
	return &instance;
}

void Camera::Initialize()
{
	window = Window::GetInstance();

	const float distance = 20.f;	//ƒJƒƒ‰‚Ì‹——£

	//ƒJƒƒ‰
	view.eye = {0, -45.f, -distance};
	view.target = {0, -50.f, 0};
	view.up = {0, 1, 0};

	view.angle = _Angle;
	targetBase = view.target;

	view.UpdateViewMatrix();
	view.UpdateProjectionMatrix(window->GetWindowWidth(),window->GetWindowHeight());
}

void Camera::Update()
{
	Shake();
	view.target = targetBase + offset;

	view.matViewProjection = view.matView * view.matProjection;

	view.UpdateViewMatrix();
	view.UpdateProjectionMatrix(window->GetWindowWidth(),window->GetWindowHeight());
}

void Camera::Shake()
{
	if(!IsShake) return ;
	if(time >= _Power){
		time = 0.f;
		offset = {0.f,0.f,0.f};
		IsShake = false;
		return ;
	}

	float shakePower = (_Power - time);
	if(shakePower == 0) {
		time = _Power;
		return;
	}

	float num = (float)(rand() / (32768.0 + (shakePower - (shakePower/2))));

	offset.x = num;
	//offset.y = num;
	
	time += 1.f/60;
}

void Camera::AngleMove(float targetAngle)
{
	if(targetAngle >= view.angle){
		if(view.angle >= targetAngle){
			view.angle = targetAngle;
		}

		view.angle += 1.f;
	}
	else if(targetAngle <= view.angle){
		if(view.angle <= targetAngle){
			view.angle = targetAngle;
		}

		view.angle -= 1.f;
	}
}


