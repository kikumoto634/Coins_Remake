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
#pragma endregion 

#pragma region 3D初期化
	//プレイヤー
	playerModel = FbxLoader::GetInstance()->LoadModeFromFile("Player");
	playerObject = FbxModelObject::Create(playerModel);
	playerWorld.Initialize();
	playerWorld.translation = {0,-135,210};
	playerWorld.UpdateMatrix();

	//地面
	groundModel = FbxLoader::GetInstance()->LoadModeFromFile("ground");
	for(int i = 0; i < 10; i++){
		groundObject[i] = FbxModelObject::Create(groundModel);

		groundWorld[i].Initialize();
		groundWorld[i].translation = {0,-150,(float)i*210};
		groundWorld[i].UpdateMatrix();
	}
#pragma endregion

#pragma region 汎用機能初期化
	eye = camera->GetEye();
	target = camera->GetTarget();
#pragma endregion
}

void PlayScene::Update()
{
	/// <summary>
	/// シーンベース
	/// </summary>
	BaseScene::Update();

#pragma region 入力処理

	//プレイヤー
	if(input->Push(DIK_LEFT)){
		playerWorld.translation.x -= 2.f;
	}
	else if(input->Push(DIK_RIGHT)){
		playerWorld.translation.x += 2.f;
	}
	if(input->Push(DIK_UP)){
		playerWorld.translation.z += 2.f;
	}
	else if(input->Push(DIK_DOWN)){
		playerWorld.translation.z -= 2.f;
	}

#ifdef _DEBUG
	//カメラ
	if(input->Push(DIK_LSHIFT)){
		if(input->Push(DIK_DOWN)){
			target.y -= XMConvertToRadians(4.f);
		}
		else if(input->Push(DIK_UP)){
			target.y += XMConvertToRadians(4.f);
		}
		if(input->Push(DIK_S)){
			target.y -= 1.f;
			eye.y -= 1.f;
		}
		else if(input->Push(DIK_W)){
			target.y += 1.f;
			eye.y += 1.f;
		}
	}
#endif // _DEBUG
#pragma endregion

#pragma region 汎用機能更新
	//カメラ
	camera->SetEye({playerWorld.translation.x, eye.y, eye.z});
	camera->SetTarget({playerWorld.translation.x, target.y, target.z});
#pragma endregion

#pragma region 2D更新
#pragma endregion

#pragma region 3D更新
	//プレイヤー
	playerWorld.translation.x = max(playerWorld.translation.x, -90.f);
	playerWorld.translation.x = min(playerWorld.translation.x, 90.f);
	playerWorld.translation.z = max(playerWorld.translation.z, 135.f);
	playerWorld.translation.z = min(playerWorld.translation.z, 295.f);

	playerWorld.UpdateMatrix();
	playerObject->Update(playerWorld, camera);

	//地面
	for(int i = 0; i < 10; i++){
		groundWorld[i].UpdateMatrix();
		groundObject[i]->Update(groundWorld[i], camera);
	}
#pragma endregion

#ifdef _DEBUG
	debugText->Printf(0,0,1.f,"Camera:Eye	 X:%f Y:%f Z:%f", camera->GetEye().x,camera->GetEye().y,camera->GetEye().z);
	debugText->Printf(0,16,1.f,"Camera:Target X:%f Y:%f Z:%f", camera->GetTarget().x,camera->GetTarget().y,camera->GetTarget().z);

	debugText->Printf(0, 48, 1.f, "Player:Pos X:%f Y:%f Z:%f", playerWorld.translation.x, playerWorld.translation.y, playerWorld.translation.z);
#endif // _DEBUG


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

#pragma region 2D背景

#pragma endregion

#pragma region 3D描画
	//プレイヤー
	playerObject->Draw();

	//地面
	for(int i = 0; i < 10; i++){
		groundObject[i]->Draw();
	}
#pragma endregion

#pragma region 2D描画UI
	Sprite::SetPipelineState();

#pragma endregion 

#ifdef _DEBUG
	debugText->DrawAll();
#endif // _DEBUG

}

void PlayScene::Finalize()
{
	/// <summary>
	/// シーンベース
	/// </summary>
	BaseScene::Finalize();

#pragma region 3D後処理

	for(int i = 0; i < 10; i++){
		delete groundObject[i];
		groundObject[i] = nullptr;
		groundWorld[i] = {};
	}
	delete groundModel;
	groundModel = nullptr;

#pragma endregion

#pragma region 2D後処理

#pragma endregion 
}
