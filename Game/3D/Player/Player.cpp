#include "Player.h"

using namespace DirectX;

Player::~Player()
{
	Finalize();
}

void Player::Initialize(std::string filePath)
{
	BaseObjects::Initialize(filePath);

	Initialize2D();
	Initialize3D();

	//衝突属性設定
	SetCollisionAttribute(kCollisionAttributeMine);
	//衝突対象を自分の属性以外に設定
	SetCollisionMask(kCollisionAttributeThier);
}

void Player::Update(Camera* camera, Input* input)
{
	this->input = input;

	Update2D();
	Update3D();

	BaseObjects::Update(camera);
}

void Player::Draw_2D()
{
	Draw2D();
}

void Player::Draw_3D()
{
	Draw2D();
	Draw3D();

	BaseObjects::Draw();
}

void Player::Finalize()
{
	Finalize2D();
	Finalize3D();

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
		Hp -= 1;
		IsDamage = true;
		return ;
	}
}

#pragma region 2D処理
void Player::Initialize2D()
{
	for(int i = 0; i < MaxHp; i++){
		playerHp[i] = std::make_unique<PlayerHp>();
		playerHp[i]->Initialize(4);
	}
}

void Player::Update2D()
{
	//スコア
	IsScoreUp = false;
	IsScoreDown = false;

	//体力
	for(int i = 0; i < Hp; i++){
		playerHp[i]->Update();
		playerHp[i]->SetVector2(playerHp[i]->ChangeTransformation(Vector3(world.translation.x +i*20-20, world.translation.y+30, world.translation.z)));
	}
}

void Player::Draw2D()
{
	//体力
	for(int i = 0; i < Hp; i++){
		playerHp[i]->Draw();
	}
}

void Player::Finalize2D()
{
	//体力
	for(int i = 0; i < MaxHp; i++){
		playerHp[i]->Finalize();
	}
}
#pragma endregion

#pragma region 3D処理
void Player::Initialize3D()
{
	AnimSp = AnimNormalSp;

	world.translation = {0,-131,200};
	world.UpdateMatrix();
}

void Player::Update3D()
{
	//死亡
	Dead();
	if(IsDead) return;

	//入力
	InputMovement();
	//ダメージ
	Damage();

	//縦回転
	if(world.rotation.x >= XMConvertToRadians(360.f)) world.rotation.x = 0.f;
	world.rotation.x += XMConvertToRadians(AnimSp);
}

void Player::Draw3D()
{
}

void Player::Finalize3D()
{
}
#pragma endregion

void Player::InputMovement()
{
	//移動制限
	world.translation.x = max(world.translation.x, -90.f);
	world.translation.x = min(world.translation.x, 90.f);
	world.translation.z = max(world.translation.z, 120.f);
	world.translation.z = min(world.translation.z, 300.f);

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
	if(input->Push(DIK_UP)){
		world.translation.z += MoveSp * (AnimSp / AnimMaxSp);
		
		if(AnimSp >= AnimMaxSp) return;
		AnimSp += 0.05f;
	}
	else if(input->Push(DIK_DOWN)){
		world.translation.z -= MoveSp * (AnimMinSp / AnimSp);
		
		if(AnimSp <= AnimMinSp) return;
		AnimSp -= 0.1f;
	}
	else if(!input->Push(DIK_UP)&&!input->Push(DIK_DOWN)){
		AnimSp = AnimNormalSp;
	}
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

	//Hp表示
	for(int i = 0; i < Hp; i++){
		playerHp[i]->FadeStart();
	}
}

void Player::Dead()
{
	if(input->Trigger(DIK_5)){
		IsDead = true;
	}

	if(!IsDead) return;

	if(DeadAnimSp <= 0.f) {
		world.rotation.x = XMConvertToRadians(360);
		world.rotation.y = XMConvertToRadians(90.f);
		world.rotation.z = XMConvertToRadians(90.f);
		return;
	}
	DeadAnimSp -= 1.f/240;

	if(time >= 1.f) return;
	time += 0.01f;
	world.rotation.x = (1-time)*XMConvertToRadians(world.rotation.x) + (time)*XMConvertToRadians(360);
	world.rotation.y = (1-time)*XMConvertToRadians(world.rotation.y) + (time)*XMConvertToRadians(90.f);
	world.rotation.z = (1-time)*XMConvertToRadians(world.rotation.z) + (time)*XMConvertToRadians(90.f);
}
