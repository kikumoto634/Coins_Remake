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
	coin = make_unique<Coins>();
	coin->Initialize("coin");

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

	collisionManager = make_unique<CollisionManager>();
#pragma endregion
}

void PlayScene::Update()
{
	/// <summary>
	/// シーンベース
	/// </summary>
	BaseScene::Update();

#pragma region 入力処理


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

#pragma region 2D更新
#pragma endregion

#pragma region 3D更新
	//プレイヤー
	player->Update(camera, input);

	//コイン
	if(coin->GetIsDead()){
		coin->Finalize();
	}
	coin->Update(camera);

	//地面
	for(int i = 0; i < 10; i++){
		groundWorld[i].UpdateMatrix();
		groundObject[i]->Update(groundWorld[i], camera);
	}
#pragma endregion

#pragma region 汎用機能更新
	//カメラ
	eye.x = player->GetPosition().x;
	target.x = player->GetPosition().x;
	camera->SetEye(eye);
	camera->SetTarget(target);
#pragma endregion

#ifdef _DEBUG
	debugText->Printf(0,0,1.f,"Camera:Eye	 X:%f Y:%f Z:%f", camera->GetEye().x,camera->GetEye().y,camera->GetEye().z);
	debugText->Printf(0,16,1.f,"Camera:Target X:%f Y:%f Z:%f", camera->GetTarget().x,camera->GetTarget().y,camera->GetTarget().z);

	debugText->Printf(0, 48, 1.f, "Player:Pos X:%f Y:%f Z:%f", player->GetPosition().x, player->GetPosition().y, player->GetPosition().z);

	debugText->Printf(0, 80, 1.f,"coin Dead:%d", coin->GetIsDead());
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
	coin->Draw();

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
	//プレイヤー
	player->Finalize();

	//コイン
	coin->Finalize();

	//地面
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

void PlayScene::CheckAllCollision()
{
	//リストクリア
	collisionManager->CollisionClear();
	//リスト追加
	collisionManager->SetCollision(player.get());
	collisionManager->SetCollision(coin.get());

	//総当たり判定
	//リスト内のペアを総当たり
	std::list<Collider*>::iterator itrA = collisionManager->colliders.begin();
	for(; itrA != collisionManager->colliders.end(); ++itrA){
		//イテレータAからコライダーAを取得
		Collider* colliderA = *itrA;

		//イテレータBはイテレータAの次の要素から回す(重複判定回避)
		std::list<Collider*>::iterator itrB = itrA;
		itrB++;

		for(; itrB != collisionManager->colliders.end(); ++itrB){
			//イテレータBからコライダーBを取得
			Collider* colliderB = *itrB;

			//ペアの当たり判定
			CheckCollisionPair(colliderA, colliderB);
		}
	}
}

void PlayScene::CheckCollisionPair(Collider *colliderA, Collider *colliderB)
{
	//衝突フィルタリング
	if(colliderA->GetCollisionAttribute() != colliderB->GetCollisionMask() || colliderB->GetCollisionAttribute() != colliderA->GetCollisionMask()){
		return;
	}

	if(CheckCollisionDetail(colliderA, colliderB)){
		colliderA->OnCollision(colliderB);
		colliderB->OnCollision(colliderA);
	}
}

bool PlayScene::CheckCollisionDetail(Collider *colliderA, Collider *colliderB)
{
	//ボックス同士の当たり判定
	if(colliderA->GetPosition().x-colliderA->GetWidth() > colliderB->GetPosition().x+colliderB->GetWidth())		return false;
	if(colliderA->GetPosition().x+colliderA->GetWidth() < colliderB->GetPosition().x-colliderB->GetWidth())		return false;
	if(colliderA->GetPosition().y-colliderA->GetHeight() > colliderB->GetPosition().y+colliderB->GetHeight())	return false;
	if(colliderA->GetPosition().y+colliderA->GetHeight() < colliderB->GetPosition().y-colliderB->GetHeight())	return false;
	if(colliderA->GetPosition().z-colliderA->GetDepth() > colliderB->GetPosition().z+colliderB->GetDepth())		return false;
	if(colliderA->GetPosition().z+colliderA->GetDepth() < colliderB->GetPosition().z-colliderB->GetDepth())		return false;

	return true;
}
