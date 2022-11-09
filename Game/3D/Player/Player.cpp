#include "Player.h"

using namespace DirectX;

Player::~Player()
{
	Finalize();
}

void Player::Initialize(std::string filePath)
{
	BaseObjects::Initialize(filePath);

	AnimSp = AnimNormalSp;

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
	//�ړ�����
	world.translation.x = max(world.translation.x, -90.f);
	world.translation.x = min(world.translation.x, 90.f);
	world.translation.z = max(world.translation.z, 180.f);
	world.translation.z = min(world.translation.z, 240.f);

	//�����ړ�
	//���͎�
	if(input->Push(DIK_RIGHT))
	{
		//�ړ�
		world.translation.x += MoveSp * (world.rotation.y / MaxRadian);

		//��]
		rotEaseTime = 0.f;
		if(world.rotation.y >= MaxRadian) return;

		//�E�����Ȃ��]����
		if(world.rotation.y < 0.f) world.rotation.y += RotSp*2;
		world.rotation.y += RotSp;
	}
	else if(input->Push(DIK_LEFT))
	{
		//�ړ�
		world.translation.x -= MoveSp * (world.rotation.y / -MaxRadian);

		//��]
		rotEaseTime = 0.f;
		if(world.rotation.y <= -MaxRadian) return;
		
		//�E�����Ȃ��]����
		if(world.rotation.y > 0.f) world.rotation.y -= RotSp*2;
		world.rotation.y -= RotSp;
	}
	//�����͎�
	else if(!input->Push(DIK_RIGHT)&&!input->Push(DIK_LEFT)){

		if(rotEaseTime >= 1.f){
			world.rotation.y = 0.f;
		}
		else if(world.rotation.y != 0.f){
			//���̂�
			rotEaseTime += 1.f/30;
			world.rotation.y = (1.f-rotEaseTime) * world.rotation.y + rotEaseTime * 0.f;
		}
	}

	//�O��ړ�
	/*if(input->Push(DIK_UP)){
		AnimSp = AnimMaxSp;
		world.translation.z += MoveSp;
	}
	else if(input->Push(DIK_DOWN)){
		AnimSp = AnimMinSp;
		world.translation.z -= MoveSp;
	}
	else if(!input->Push(DIK_UP)&&!input->Push(DIK_DOWN)){
		AnimSp = AnimNormalSp;
	}*/
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
