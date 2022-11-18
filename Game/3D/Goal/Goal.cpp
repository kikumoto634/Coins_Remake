#include "Goal.h"

Goal::~Goal()
{
	Finalize();
}

void Goal::Initialize(std::string filePath)
{
	BaseObjects::Initialize(filePath);
	//Õ“Ë‘®«İ’è
	SetCollisionAttribute(kCollisionAttributeThier);
	//Õ“Ë‘ÎÛ‚ğ©•ª‚Ì‘®«ˆÈŠO‚Éİ’è
	SetCollisionMask(kCollisionAttributeMine);
}

void Goal::Update(Camera *camera)
{
	//‰œs‚«ˆÚ“®
	if(world.translation.z <= 0) IsDead = true;
	world.translation.z -= DepthSp;

	BaseObjects::Update(camera);
}

void Goal::Draw()
{
	BaseObjects::Draw();
}

void Goal::Finalize()
{
	BaseObjects::Finalize();
}

void Goal::OnCollision(Collider *TouchCollision)
{
}
