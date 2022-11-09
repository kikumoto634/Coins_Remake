#include "Player.h"

using namespace DirectX;

Player::~Player()
{
	Finalize();
}

void Player::Initialize(std::string filePath)
{
	BaseObjects::Initialize(filePath);

	world.translation = {0,-131,200};
	world.UpdateMatrix();

	//�Փˑ����ݒ�
	SetCollisionAttribute(kCollisionAttributeMine);
	//�ՓˑΏۂ������̑����ȊO�ɐݒ�
	SetCollisionMask(kCollisionAttributeThier);
}

void Player::Update(Camera* camera, Input* input)
{
	this->input = input;
	IsScoreUp = false;
	IsScoreDown = false;

	//����
	InputMovement();

	//�_���[�W
	Damage();

	//�ړ�����
	world.translation.x = max(world.translation.x, -90.f);
	world.translation.x = min(world.translation.x, 90.f);
	world.translation.z = max(world.translation.z, 180.f);
	world.translation.z = min(world.translation.z, 240.f);

	//�c��]
	if(world.rotation.x >= XMConvertToRadians(360.f)) world.rotation.x = 0.f;
	world.rotation.x += XMConvertToRadians(AnimSp);

	BaseObjects::Update(camera);
}

void Player::Draw()
{
	BaseObjects::Draw();
}

void Player::Finalize()
{
	BaseObjects::Finalize();
}

void Player::OnCollision(Collider *TouchCollision)
{
	if(TouchCollision->GetName() == "Coin"){
		CoinCount = CoinCount + 1;
		ScoreCount += 100;
		IsScoreUp = true;
		return ;
	}
	else if(TouchCollision->GetName() == "Wall01"){
		ScoreCount -= 100;
		IsScoreDown = true;
		IsDamage = true;
		return ;
	}
}

void Player::InputMovement()
{
	//�v���C���[
	if(input->Push(DIK_LEFT)){
		world.translation.x -= MoveSp;
	}
	else if(input->Push(DIK_RIGHT)){
		world.translation.x += MoveSp;
	}


	if(input->Push(DIK_UP)){
		world.translation.z += MoveSp;
	}
	else if(input->Push(DIK_DOWN)){
		world.translation.z -= MoveSp;
	}
}

void Player::Damage()
{
	//�_���[�W����������
	if(!IsDamage) return;

	//�_���[�W���Z�b�g
	if(returnTime >= ReturnTime){
		returnTime = 0.f;
		world.rotation.z = 0.f;
		IsDamage = false;

		return;
	}

	//��]�A���Ԍo��
	world.rotation.z += XMConvertToRadians(AnimSp);
	returnTime += 1.f/60.f;
}
