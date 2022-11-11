#include "OutArea.h"

OutArea::~OutArea()
{
	Finalize();
}

void OutArea::Initialize(std::string filePath)
{
	BaseObjects::Initialize(filePath);
}

void OutArea::Update(Camera *camera)
{
	if(world.translation.z <= 0) world.translation.z = 1200.f;
	world.translation.z -= DepthSp;

	BaseObjects::Update(camera);
}

void OutArea::Draw()
{
	BaseObjects::Draw();
}

void OutArea::Finalize()
{
	BaseObjects::Finalize();
}
