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
	if(world.translation.z <= DeletePosZ) world.translation.z = PopPosZ;
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
