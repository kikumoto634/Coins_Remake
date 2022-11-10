#include "HitStop.h"

void HitStop::Initialize()
{
}

bool HitStop::Update(Camera* camera)
{
	this->camera = camera;

	if(!IsHitStop) return false;

	if(frame >= stopFrame){
		Reset();
		return false;
	}
	frame += 1.f;

	return true;
}

void HitStop::HitStopStart()
{
	IsHitStop = true;
	camera->SetAngle(cameraViewAngle);
}

void HitStop::Reset()
{
	frame = 0.f;
	camera->ReSetAngle();
	IsHitStop = false;
}
