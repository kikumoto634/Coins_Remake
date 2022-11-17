#include "BaseScene.h"

using namespace std;

BaseScene::BaseScene(DirectXCommon* dxCommon, Window* window)
{
	this->dxCommon = dxCommon;
	this->window = window;
}

void BaseScene::Application()
{
	input = Input::GetInstance();
	camera = Camera::GetInstance();
}

void BaseScene::Initialize()
{
	//Input初期化
	input->Initialize(window->GetHwnd());

	//カメラ
	camera->Initialize();

	//衝突判定
	collisionManager = make_unique<CollisionManager>();

#ifdef _DEBUG
	//一時停止
	sceneStopper = SceneStopper::GetInstance();
		
	debugText = std::make_unique<DebugText>();
	debugText->Initialize(1);

#endif // _DEBUG
}

void BaseScene::Update()
{
	//入力情報更新
	input->Update();
}

void BaseScene::EndUpdate()
{
#ifdef _DEBUG
#pragma region 一時停止
	//入力
	if(input->Trigger(DIK_F1)){
		if(!sceneStopper->GetIsSceneStop()){
			sceneStopper->SetIsSceneStop(true);
		}
		else if(sceneStopper->GetInstance()){
			sceneStopper->SetIsSceneStop(false);
		}
	}
	//停止
	if(sceneStopper->GetIsSceneStop()) return;
#pragma endregion
#endif // _DEBUG

#pragma region 汎用機能更新
	//衝突判定更新
	CheckAllCollision();
	//カメラ
	camera->Update();
#pragma endregion
}

void BaseScene::Draw()
{
}

void BaseScene::EndDraw()
{
#ifdef _DEBUG
	debugText->DrawAll();
#endif // _DEBUG
}

void BaseScene::Finalize()
{
}

void BaseScene::CheckAllCollision()
{
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

	//リストクリア
	collisionManager->CollisionClear();
}

void BaseScene::CheckCollisionPair(Collider *colliderA, Collider *colliderB)
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

bool BaseScene::CheckCollisionDetail(Collider *colliderA, Collider *colliderB)
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