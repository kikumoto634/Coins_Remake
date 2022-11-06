#include "Grounds.h"

void Grounds::Initialize(std::string filePath)
{
	BaseObjects::Initialize(filePath);
}

void Grounds::Update(Camera *camera)
{
	if(world.translation.z <= 0) world.translation.z = 1200.f;
	world.translation.z -= 1.f;

	BaseObjects::Update(camera);
}

void Grounds::Draw()
{
	BaseObjects::Draw();
}

void Grounds::Finalize()
{
	BaseObjects::Finalize();
}
