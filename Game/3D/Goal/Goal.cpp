#include "Goal.h"

Goal::~Goal()
{
	Finalize();
}

void Goal::Initialize(std::string filePath)
{
	BaseObjects::Initialize(filePath);
	//衝突属性設定
	SetCollisionAttribute(kCollisionAttributeThier);
	//衝突対象を自分の属性以外に設定
	SetCollisionMask(kCollisionAttributeMine);
}

void Goal::Update(Camera *camera)
{
	//奥行き移動
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
	if(TouchCollision->GetName() == "Player"){
		IsGoal = true;
	}
}
