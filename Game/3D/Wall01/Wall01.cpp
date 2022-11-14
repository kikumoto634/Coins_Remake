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

	//�Փˑ����ݒ�
	SetCollisionAttribute(kCollisionAttributeThier);
	//�ՓˑΏۂ������̑����ȊO�ɐݒ�
	SetCollisionMask(kCollisionAttributeMine);
}

void Wall01::Update(Camera *camera, HitStop* hitStop)
{
	this->hitStop = hitStop;

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
	hitStop->SetStopFrame(1.f);
	hitStop->HitStopStart();
	camera->ShakeStart();
	IsDead = true;
}
