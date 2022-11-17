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
	//Input������
	input->Initialize(window->GetHwnd());

	//�J����
	camera->Initialize();

	//�Փ˔���
	collisionManager = make_unique<CollisionManager>();

#ifdef _DEBUG
	//�ꎞ��~
	sceneStopper = SceneStopper::GetInstance();
		
	debugText = std::make_unique<DebugText>();
	debugText->Initialize(1);

#endif // _DEBUG
}

void BaseScene::Update()
{
	//���͏��X�V
	input->Update();
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
	//�Փ˔���X�V
	CheckAllCollision();
	//�J����
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

	//���X�g�N���A
	collisionManager->CollisionClear();
}

void BaseScene::CheckCollisionPair(Collider *colliderA, Collider *colliderB)
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

bool BaseScene::CheckCollisionDetail(Collider *colliderA, Collider *colliderB)
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