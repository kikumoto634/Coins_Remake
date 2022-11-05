#include "Coins.h"

using namespace DirectX;

void Coins::Initialize(std::string filePath)
{
	BaseObjects::Initialize(filePath);

	world.translation = {0,-135,280};
	world.UpdateMatrix();
}

void Coins::Update(Camera* camera)
{
	if(world.rotation.y >= XMConvertToRadians(360.f))	world.rotation.y = XMConvertToRadians(0.f);
	world.rotation.y += XMConvertToRadians(1.f);

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
