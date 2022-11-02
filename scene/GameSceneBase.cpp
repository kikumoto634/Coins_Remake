#include "GameSceneBase.h"

GameSceneBase::~GameSceneBase()
{
	Sprite::StaticFinalize();
}

void GameSceneBase::Initialize()
{
	//�e�N�X�`��
	TextureManager::Load(0, "Texture.jpg");

	//�X�v���C�g
	//Sprite::StaticInitialize(dxCommon, window->GetWindowWidth(), window->GetWindowHeight());
}

void GameSceneBase::Draw()
{
	Sprite::SetPipelineState();
}
