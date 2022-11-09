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

	//衝突属性設定
	SetCollisionAttribute(kCollisionAttributeMine);
	//衝突対象を自分の属性以外に設定
	SetCollisionMask(kCollisionAttributeThier);
}

void Player::Update(Camera* camera, Input* input)
{
	this->input = input;
	IsScoreUp = false;
	IsScoreDown = false;

	//入力
	InputMovement();

	//ダメージ
	Damage();

	//縦回転
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
	//移動制限
	world.translation.x = max(world.translation.x, -90.f);
	world.translation.x = min(world.translation.x, 90.f);
	world.translation.z = max(world.translation.z, 180.f);
	world.translation.z = min(world.translation.z, 240.f);

	//水平移動
	//入力時
	if(input->Push(DIK_RIGHT))
	{
		//移動
		world.translation.x += MoveSp * (world.rotation.y / MaxRadian);

		//回転
		rotEaseTime = 0.f;
		if(world.rotation.y >= MaxRadian) return;

		//右向きなら回転加速
		if(world.rotation.y < 0.f) world.rotation.y += RotSp*2;
		world.rotation.y += RotSp;
	}
	else if(input->Push(DIK_LEFT))
	{
		//移動
		world.translation.x -= MoveSp * (world.rotation.y / -MaxRadian);

		//回転
		rotEaseTime = 0.f;
		if(world.rotation.y <= -MaxRadian) return;
		
		//右向きなら回転加速
		if(world.rotation.y > 0.f) world.rotation.y -= RotSp*2;
		world.rotation.y -= RotSp;
	}
	//未入力時
	else if(!input->Push(DIK_RIGHT)&&!input->Push(DIK_LEFT)){

		if(rotEaseTime >= 1.f){
			world.rotation.y = 0.f;
		}
		else if(world.rotation.y != 0.f){
			//そのた
			rotEaseTime += 1.f/30;
			world.rotation.y = (1.f-rotEaseTime) * world.rotation.y + rotEaseTime * 0.f;
		}
	}

	//前後移動
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
	//ダメージ無し時処理
	if(!IsDamage) return;

	//ダメージリセット
	if(returnTime >= ReturnTime){
		returnTime = 0.f;
		world.rotation.z = 0.f;
		IsDamage = false;

		return;
	}

	//回転、時間経過
	world.rotation.z += XMConvertToRadians(AnimSp);
	returnTime += 1.f/60.f;
}
