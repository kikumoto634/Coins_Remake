#include "Wall02.h"

Wall02::~Wall02()
{
	Finalize();
}

void Wall02::Initialize(std::string filePath)
{
	BaseObjects::Initialize(filePath);

	world.scale = Vector3(0.5f,0.5f,0.5f);
	world.UpdateMatrix();

	//衝突属性設定
	SetCollisionAttribute(kCollisionAttributeThier);
	//衝突対象を自分の属性以外に設定
	SetCollisionMask(kCollisionAttributeMine);
}

void Wall02::Update(Camera *camera, HitStop *hitStop)
{
	this->hitStop = hitStop;

	if(world.translation.z <= -100){
		IsDead = true;
	}

	//奥行き移動
	if(world.translation.z <= 0) IsDead = true;
	world.translation.z -= DepthSp;

	//横移動
	Movement();


	BaseObjects::Update(camera);
}

void Wall02::Draw()
{
	BaseObjects::Draw();
}

void Wall02::Finalize()
{
	BaseObjects::Finalize();
}

void Wall02::OnCollision(Collider *TouchCollision)
{
	hitStop->SetStopFrame(1.f);
	hitStop->HitStopStart();
	camera->ShakeStart();
	IsDead = true;
}

void Wall02::Movement()
{
	fallTime += 1.f/60;

	if(world.translation.y >= -120.f) world.translation.y -= MoveSp;

	if(!IsLRFlag){
		world.translation.x -= 4.f;
		world.rotation.z += DirectX::XMConvertToRadians(6.f);
	}
	else if(IsLRFlag) {
		world.translation.x += 4.f;
		world.rotation.z -= DirectX::XMConvertToRadians(6.f);
	}
}
