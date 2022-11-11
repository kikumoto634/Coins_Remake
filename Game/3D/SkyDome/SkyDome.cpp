#include "SkyDome.h"


void SkyDome::Initialize(std::string filePath)
{
	BaseObjects::Initialize(filePath);
}

void SkyDome::Update(Camera *camera)
{
	BaseObjects::Update(camera);
}

void SkyDome::Draw()
{
	BaseObjects::Draw();
}

void SkyDome::Finalize()
{
	BaseObjects::Finalize();
}
