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

	sp = Sprite::Create(0, Vector2(110,0));
	sp->SetSize(Vector2(100,100));


#ifdef _DEBUG
	//�ꎞ��~
	sceneStopper = SceneStopper::GetInstance();
#endif // _DEBUG
}

void BaseScene::Update()
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

#pragma region ���͏���

	if(input->Push(DIK_SPACE)){
		sp->SetColor({1,0,0,1});
	}
	else{
		sp->SetColor({1,1,1,1});
	}

#pragma endregion

#pragma region �ėp�@�\�X�V
	//���͏��X�V
	input->Update();
	//�J����
	camera->Update();
#pragma endregion
}

void BaseScene::Draw()
{
	sp->Draw();
}

void BaseScene::Finalize()
{
	delete sp;
	sp = nullptr;
}
