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

	//衝突属性設定
	SetCollisionAttribute(kCollisionAttributeThier);
	//衝突対象を自分の属性以外に設定
	SetCollisionMask(kCollisionAttributeMine);
}

void Coins::Update(Camera* camera)
{
	//回転
	if(world.rotation.y >= XMConvertToRadians(360.f))	world.rotation.y = XMConvertToRadians(0.f);
	world.rotation.y += XMConvertToRadians(1.f);

	//奥行き移動
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
