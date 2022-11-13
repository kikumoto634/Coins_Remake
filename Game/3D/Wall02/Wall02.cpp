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

	//Õ“Ë‘®«Ý’è
	SetCollisionAttribute(kCollisionAttributeThier);
	//Õ“Ë‘ÎÛ‚ðŽ©•ª‚Ì‘®«ˆÈŠO‚ÉÝ’è
	SetCollisionMask(kCollisionAttributeMine);
}

void Wall02::Update(Camera *camera, HitStop *hitStop)
{
	this->hitStop = hitStop;

	if(world.translation.z <= -100){
		IsDead = true;
	}

	//‰œs‚«ˆÚ“®
	if(world.translation.z <= 0) IsDead = true;
	world.translation.z -= DepthSp;

	//‰¡ˆÚ“®
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
	if(fallTime <= FallTime) return;

	world.translation.x -= 3.f;
	if(world.translation.y >= -120.f) world.translation.y -= 1.f;
	world.rotation.z += DirectX::XMConvertToRadians(6.f);
}
