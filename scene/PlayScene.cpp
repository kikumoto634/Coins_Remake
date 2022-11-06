#include "PlayScene.h"

using namespace std;

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
	player = make_unique<Player>();
	player->Initialize("player");

	//コイン
	for(int i = 0; i < 20;i++){
		CoinPop({0,-135,280 + (float)i*20});
	}

	//地面
	groundModel = FbxLoader::GetInstance()->LoadModeFromFile("ground");
	for(int i = 0; i < 20; i++){
		groundObject[i] = FbxModelObject::Create(groundModel);

		groundWorld[i].Initialize();
		groundWorld[i].translation = {0,-150,(float)i*210};
		groundWorld[i].UpdateMatrix();
	}
#pragma endregion

#pragma region 汎用機能初期化
#pragma endregion
}

void PlayScene::Update()
{
	/// <summary>
	/// シーンベース
	/// </summary>
	BaseScene::Update();

#pragma region 入力処理
#pragma endregion

#pragma region 2D更新
#pragma endregion

#pragma region 3D更新
	//プレイヤー
	player->Update(camera, input);

	//コイン
	coin.remove_if([](unique_ptr<Coins>& obj){
		return obj->GetIsDead();
	});
	for(unique_ptr<Coins>& obj : coin){
		obj->Update(camera);
	}

	//地面
	for(int i = 0; i < 20; i++){
		groundWorld[i].UpdateMatrix();
		groundObject[i]->Update(groundWorld[i], camera);
	}
#pragma endregion

#pragma region 汎用機能更新
	//衝突判定リスト追加
	collisionManager->SetCollision(player.get());
	for(const std::unique_ptr<Coins>& obj : coin)
	{
		collisionManager->SetCollision(obj.get());
	}
#pragma endregion

#ifdef _DEBUG
	debugText->Printf(0,0,1.f,"Camera:Eye	 X:%f Y:%f Z:%f", camera->GetEye().x,camera->GetEye().y,camera->GetEye().z);
	debugText->Printf(0,16,1.f,"Camera:Target X:%f Y:%f Z:%f", camera->GetTarget().x,camera->GetTarget().y,camera->GetTarget().z);
	debugText->Printf(0, 48, 1.f, "Player:Pos X:%f Y:%f Z:%f", player->GetPosition().x, player->GetPosition().y, player->GetPosition().z);
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
	player->Draw();

	//コイン
	for(unique_ptr<Coins>& obj : coin){
		obj->Draw();
	}

	//地面
	for(int i = 0; i < 20; i++){
		groundObject[i]->Draw();
	}
#pragma endregion

#pragma region 2D描画UI
	Sprite::SetPipelineState();
#pragma endregion 

	/// <summary>
	/// シーンベース
	/// </summary>
	BaseScene::EndDraw();
}

void PlayScene::Finalize()
{
	/// <summary>
	/// シーンベース
	/// </summary>
	BaseScene::Finalize();

#pragma region 3D後処理
	//プレイヤー
	player->Finalize();

	//コイン
	for(unique_ptr<Coins>& obj : coin){
		obj->Finalize();
	}

	//地面
	for(int i = 0; i < 20; i++){
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

void PlayScene::CoinPop(Vector3 position)
{
	unique_ptr<Coins> newcoin = make_unique<Coins>();
	newcoin->Initialize("coin");
	newcoin->SetVector3(position);

	coin.push_back(move(newcoin));
}
