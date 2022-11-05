#include "BaseObjects.h"

void BaseObjects::Initialize(std::string filePath)
{
	//プレイヤー
	model = FbxLoader::GetInstance()->LoadModeFromFile(filePath);
	object = FbxModelObject::Create(model);
	world.Initialize();
	world.UpdateMatrix();
}

void BaseObjects::Update(Camera *camera)
{
	this->camera = camera;
	world.UpdateMatrix();
	object->Update(world, this->camera);
}

void BaseObjects::Draw()
{
	//プレイヤー
	object->Draw();
}

void BaseObjects::Finalize()
{
	delete model;
	model = nullptr;
	delete object;
	object = nullptr;
	world = {};
}
