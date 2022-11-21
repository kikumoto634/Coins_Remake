#include "Coins.h"

using namespace DirectX;

Coins::~Coins()
{
	Finalize();
}

void Coins::Initialize(std::string filePath)
{
	BaseObjects::Initialize(filePath);

	world.scale = Vector3(1.5f,1.5f,1.5f);
	world.UpdateMatrix();

	//Õ“Ë‘®«İ’è
	SetCollisionAttribute(kCollisionAttributeThier);
	//Õ“Ë‘ÎÛ‚ğ©•ª‚Ì‘®«ˆÈŠO‚Éİ’è
	SetCollisionMask(kCollisionAttributeMine);
}

void Coins::Update(Camera* camera)
{
	//‰ñ“]
	if(world.rotation.y >= XMConvertToRadians(360.f))	world.rotation.y = XMConvertToRadians(0.f);
	world.rotation.y += XMConvertToRadians(1.f);

	//‰œs‚«ˆÚ“®
	if(world.translation.z <= 0) IsDead = true;
	world.translation.z -= DepthSp;

	BaseObjects::Update(camera);
}

void Coins::Draw()
{
	BaseObjects::Draw();
}

void Coins::Finalize()
{
	BaseObjects::Finalize();
}

void Coins::OnCollision(Collider *TouchCollision)
{
	IsDead = true;
}
