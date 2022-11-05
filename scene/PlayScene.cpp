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
#pragma endregion 

#pragma region 3D������
	//�v���C���[
	player = make_unique<Player>();
	player->Initialize();

	//�R�C��
	coin = make_unique<Coins>();
	coin->Initialize("coin");

	//�n��
	groundModel = FbxLoader::GetInstance()->LoadModeFromFile("ground");
	for(int i = 0; i < 10; i++){
		groundObject[i] = FbxModelObject::Create(groundModel);

		groundWorld[i].Initialize();
		groundWorld[i].translation = {0,-150,(float)i*210};
		groundWorld[i].UpdateMatrix();
	}
#pragma endregion

#pragma region �ėp�@�\������
	eye = camera->GetEye();
	target = camera->GetTarget();
#pragma endregion
}

void PlayScene::Update()
{
	/// <summary>
	/// �V�[���x�[�X
	/// </summary>
	BaseScene::Update();

#pragma region ���͏���


#ifdef _DEBUG
	//�J����
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

#pragma region 2D�X�V
#pragma endregion

#pragma region 3D�X�V
	//�v���C���[
	player->Update(camera, input);

	//�R�C��
	coin->Update(camera);

	//�n��
	for(int i = 0; i < 10; i++){
		groundWorld[i].UpdateMatrix();
		groundObject[i]->Update(groundWorld[i], camera);
	}
#pragma endregion

#pragma region �ėp�@�\�X�V
	//�J����
	eye.x = player->GetPos().x;
	target.x = player->GetPos().x;
	camera->SetEye(eye);
	camera->SetTarget(target);
#pragma endregion

#ifdef _DEBUG
	debugText->Printf(0,0,1.f,"Camera:Eye	 X:%f Y:%f Z:%f", camera->GetEye().x,camera->GetEye().y,camera->GetEye().z);
	debugText->Printf(0,16,1.f,"Camera:Target X:%f Y:%f Z:%f", camera->GetTarget().x,camera->GetTarget().y,camera->GetTarget().z);

	debugText->Printf(0, 48, 1.f, "Player:Pos X:%f Y:%f Z:%f", player->GetPos().x, player->GetPos().y, player->GetPos().z);
#endif // _DEBUG


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

#pragma region 2D�w�i

#pragma endregion

#pragma region 3D�`��
	//�v���C���[
	player->Draw();

	//�R�C��
	coin->Draw();

	//�n��
	for(int i = 0; i < 10; i++){
		groundObject[i]->Draw();
	}
#pragma endregion

#pragma region 2D�`��UI
	Sprite::SetPipelineState();

#pragma endregion 

#ifdef _DEBUG
	debugText->DrawAll();
#endif // _DEBUG

}

void PlayScene::Finalize()
{
	/// <summary>
	/// �V�[���x�[�X
	/// </summary>
	BaseScene::Finalize();

#pragma region 3D�㏈��
	//�v���C���[
	player->Finalize();

	//�R�C��
	coin->Finalize();

	//�n��
	for(int i = 0; i < 10; i++){
		delete groundObject[i];
		groundObject[i] = nullptr;
		groundWorld[i] = {};
	}
	delete groundModel;
	groundModel = nullptr;

#pragma endregion

#pragma region 2D�㏈��

#pragma endregion 
}
