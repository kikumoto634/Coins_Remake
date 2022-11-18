#include "Goal.h"

Goal::~Goal()
{
	Finalize();
}

void Goal::Initialize(std::string filePath)
{
	BaseObjects::Initialize(filePath);
	//�Փˑ����ݒ�
	SetCollisionAttribute(kCollisionAttributeThier);
	//�ՓˑΏۂ������̑����ȊO�ɐݒ�
	SetCollisionMask(kCollisionAttributeMine);
}

void Goal::Update(Camera *camera)
{
	//���s���ړ�
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
