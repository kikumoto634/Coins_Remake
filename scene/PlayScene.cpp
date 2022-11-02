#include "PlayScene.h"

PlayScene::PlayScene(DirectXCommon *dxCommon, Window *window)
	: BaseScene(
		dxCommon,
		window)
{
}

void PlayScene::Application()
{
	/// <summary>
	/// �V�[���x�[�X
	/// </summary>
	BaseScene::Application();

}

void PlayScene::Initialize()
{
	/// <summary>
	/// �V�[���x�[�X
	/// </summary>
	BaseScene::Initialize();

#pragma region 2D������
	sp = Sprite::Create(0, Vector2(110,0));
	sp->SetSize(Vector2(100,100));
#pragma endregion 
}

void PlayScene::Update()
{
	/// <summary>
	/// �V�[���x�[�X
	/// </summary>
	BaseScene::Update();

#pragma region ���͏���

	if(input->Push(DIK_SPACE)){
		sp->SetColor({1,0,0,1});
	}
	else{
		sp->SetColor({1,1,1,1});
	}

#pragma endregion

	/// <summary>
	/// �V�[���x�[�X
	/// </summary>
	BaseScene::EndUpdate();
}

void PlayScene::Draw()
{
	/// <summary>
	/// �V�[���x�[�X
	/// </summary>
	BaseScene::Draw();

#pragma region 2D�`��
	sp->Draw();
#pragma endregion 
}

void PlayScene::Finalize()
{
	/// <summary>
	/// �V�[���x�[�X
	/// </summary>
	BaseScene::Finalize();

#pragma region 2D�㏈��
	delete sp;
	sp = nullptr;
#pragma endregion 
}
