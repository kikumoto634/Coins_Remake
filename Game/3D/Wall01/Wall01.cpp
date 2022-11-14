#include "Wall01.h"

Wall01::~Wall01()
{
	Finalize();
}

void Wall01::Initialize(std::string filePath)
{
	BaseObjects::Initialize(filePath);

	world.scale = Vector3(0.2f,0.2f,0.2f);
	world.UpdateMatrix();

	//Õ“Ë‘®«Ý’è
	SetCollisionAttribute(kCollisionAttributeThier);
	//Õ“Ë‘ÎÛ‚ðŽ©•ª‚Ì‘®«ˆÈŠO‚ÉÝ’è
	SetCollisionMask(kCollisionAttributeMine);
}

void Wall01::Update(Camera *camera, HitStop* hitStop)
{
	this->hitStop = hitStop;

	if(world.translation.z <= -100){
		IsDead = true;
	}

	//‰œs‚«ˆÚ“®
	if(world.translation.z <= 0) IsDead = true;
	world.translation.z -= DepthSp;

	BaseObjects::Update(camera);
}

void Wall01::Draw()
{
	BaseObjects::Draw();
}

void Wall01::Finalize()
{
	BaseObjects::Finalize();
}

void Wall01::OnCollision(Collider *TouchCollision)
{
	hitStop->SetStopFrame(1.f);
	hitStop->HitStopStart();
	camera->ShakeStart();
	IsDead = true;
}
