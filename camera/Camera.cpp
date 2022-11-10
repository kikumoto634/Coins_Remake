#include "Camera.h"

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
	if((int)time >= _Power){
		time = 0;
		offset = {0,0,0};
		IsShake = false;
		return ;
	}

	int shakePower = _Power - (int)time;
	offset.x = (float)(rand()%shakePower - (shakePower/2));
	offset.y = (float)(rand()%shakePower - (shakePower/2));
	//offset.z = (float)(rand()%shakePower - (shakePower/2));

	time += 1.f/30;
}


