#include "Wall01.h"

Wall01::~Wall01()
{
	Finalize();
}

void Wall01::Initialize(std::string filePath)
{
	BaseObjects::Initialize(filePath);
	//�Փˑ����ݒ�
	SetCollisionAttribute(kCollisionAttributeThier);
	//�ՓˑΏۂ������̑����ȊO�ɐݒ�
	SetCollisionMask(kCollisionAttributeMine);
}

void Wall01::Update(Camera *camera)
{
	if(world.translation.z <= -100){
		IsDead = true;
	}

	//���s���ړ�
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
	IsDead = true;
}
