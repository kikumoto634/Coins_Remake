#include "Grounds.h"

void Grounds::Initialize(std::string filePath)
{
	BaseObjects::Initialize(filePath);
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
