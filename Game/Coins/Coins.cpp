#include "Coins.h"

using namespace DirectX;

void Coins::Initialize(std::string filePath)
{
	BaseObjects::Initialize(filePath);
	//�Փˑ����ݒ�
	SetCollisionAttribute(kCollisionAttributeThier);
	//�ՓˑΏۂ������̑����ȊO�ɐݒ�
	SetCollisionMask(kCollisionAttributeMine);
}

void Coins::Update(Camera* camera)
{
	//��]
	if(world.rotation.y >= XMConvertToRadians(360.f))	world.rotation.y = XMConvertToRadians(0.f);
	world.rotation.y += XMConvertToRadians(1.f);

	//���s���ړ�
	if(world.translation.z <= 0) world.translation.z = 1200.f;
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
