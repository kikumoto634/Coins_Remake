#include "BaseScene.h"

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

#ifdef _DEBUG
	//一時停止
	sceneStopper = SceneStopper::GetInstance();
		
	debugText = std::make_unique<DebugText>();
	debugText->Initialize(1);

#endif // _DEBUG
}

void BaseScene::Update()
{
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
	//入力情報更新
	input->Update();
	//カメラ
	camera->Update();
#pragma endregion
}

void BaseScene::Draw()
{
}

void BaseScene::Finalize()
{
}
