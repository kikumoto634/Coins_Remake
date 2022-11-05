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
	player->Initialize("player");

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

	collisionManager = make_unique<CollisionManager>();
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
	if(coin->GetIsDead()){
		coin->Finalize();
	}
	coin->Update(camera);

	//�n��
	for(int i = 0; i < 10; i++){
		groundWorld[i].UpdateMatrix();
		groundObject[i]->Update(groundWorld[i], camera);
	}
#pragma endregion

#pragma region �ėp�@�\�X�V
	//�J����
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

void PlayScene::CheckAllCollision()
{
	//���X�g�N���A
	collisionManager->CollisionClear();
	//���X�g�ǉ�
	collisionManager->SetCollision(player.get());
	collisionManager->SetCollision(coin.get());

	//�������蔻��
	//���X�g���̃y�A�𑍓�����
	std::list<Collider*>::iterator itrA = collisionManager->colliders.begin();
	for(; itrA != collisionManager->colliders.end(); ++itrA){
		//�C�e���[�^A����R���C�_�[A���擾
		Collider* colliderA = *itrA;

		//�C�e���[�^B�̓C�e���[�^A�̎��̗v�f�����(�d��������)
		std::list<Collider*>::iterator itrB = itrA;
		itrB++;

		for(; itrB != collisionManager->colliders.end(); ++itrB){
			//�C�e���[�^B����R���C�_�[B���擾
			Collider* colliderB = *itrB;

			//�y�A�̓����蔻��
			CheckCollisionPair(colliderA, colliderB);
		}
	}
}

void PlayScene::CheckCollisionPair(Collider *colliderA, Collider *colliderB)
{
	//�Փ˃t�B���^�����O
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
	//�{�b�N�X���m�̓����蔻��
	if(colliderA->GetPosition().x-colliderA->GetWidth() > colliderB->GetPosition().x+colliderB->GetWidth())		return false;
	if(colliderA->GetPosition().x+colliderA->GetWidth() < colliderB->GetPosition().x-colliderB->GetWidth())		return false;
	if(colliderA->GetPosition().y-colliderA->GetHeight() > colliderB->GetPosition().y+colliderB->GetHeight())	return false;
	if(colliderA->GetPosition().y+colliderA->GetHeight() < colliderB->GetPosition().y-colliderB->GetHeight())	return false;
	if(colliderA->GetPosition().z-colliderA->GetDepth() > colliderB->GetPosition().z+colliderB->GetDepth())		return false;
	if(colliderA->GetPosition().z+colliderA->GetDepth() < colliderB->GetPosition().z-colliderB->GetDepth())		return false;

	return true;
}
