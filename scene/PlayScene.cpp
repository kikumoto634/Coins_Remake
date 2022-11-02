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
	/// シーンベース
	/// </summary>
	BaseScene::Application();

}

void PlayScene::Initialize()
{
	/// <summary>
	/// シーンベース
	/// </summary>
	BaseScene::Initialize();

#pragma region 2D初期化
	sp = Sprite::Create(0, Vector2(110,0));
	sp->SetSize(Vector2(100,100));
#pragma endregion 
}

void PlayScene::Update()
{
	/// <summary>
	/// シーンベース
	/// </summary>
	BaseScene::Update();

#pragma region 入力処理

	if(input->Push(DIK_SPACE)){
		sp->SetColor({1,0,0,1});
	}
	else{
		sp->SetColor({1,1,1,1});
	}

#pragma endregion

	/// <summary>
	/// シーンベース
	/// </summary>
	BaseScene::EndUpdate();
}

void PlayScene::Draw()
{
	/// <summary>
	/// シーンベース
	/// </summary>
	BaseScene::Draw();

#pragma region 2D描画
	sp->Draw();
#pragma endregion 
}

void PlayScene::Finalize()
{
	/// <summary>
	/// シーンベース
	/// </summary>
	BaseScene::Finalize();

#pragma region 2D後処理
	delete sp;
	sp = nullptr;
#pragma endregion 
}
