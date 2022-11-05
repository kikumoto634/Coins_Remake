#include "Coins.h"

void Coins::Initialize(std::string filePath)
{
	BaseObjects::Initialize(filePath);

	world.translation = {0,-135,280};
	world.UpdateMatrix();
}

void Coins::Update(Camera* camera)
{
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
