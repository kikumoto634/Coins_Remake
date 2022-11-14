#include "Grounds.h"

Grounds::~Grounds()
{
	Finalize();
}

void Grounds::Initialize(std::string filePath)
{
	BaseObjects::Initialize(filePath);

	world.scale.z = 10.f;
}

void Grounds::Update(Camera *camera)
{
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
