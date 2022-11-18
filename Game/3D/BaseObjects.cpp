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
	if(IsDead) {
		world.translation = {0,0, -1500};
		world.UpdateMatrix();
		return;
	}

	this->camera = camera;
	world.UpdateMatrix();
	object->Update(world, this->camera);
}

void BaseObjects::Draw()
{
	if(IsDead) return;

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
