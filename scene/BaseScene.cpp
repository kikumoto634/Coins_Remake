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
	//Input������
	input->Initialize(window->GetHwnd());

	//�J����
	camera->Initialize();

#ifdef _DEBUG
	//�ꎞ��~
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
#pragma region �ꎞ��~
	//����
	if(input->Trigger(DIK_F1)){
		if(!sceneStopper->GetIsSceneStop()){
			sceneStopper->SetIsSceneStop(true);
		}
		else if(sceneStopper->GetInstance()){
			sceneStopper->SetIsSceneStop(false);
		}
	}
	//��~
	if(sceneStopper->GetIsSceneStop()) return;
#pragma endregion
#endif // _DEBUG

#pragma region �ėp�@�\�X�V
	//���͏��X�V
	input->Update();
	//�J����
	camera->Update();
#pragma endregion
}

void BaseScene::Draw()
{
}

void BaseScene::Finalize()
{
}
