#include "Player.h"

using namespace DirectX;

void Player::Initialize(std::string filePath)
{
	BaseObjects::Initialize(filePath);

	world.translation = {0,-131,200};
	world.UpdateMatrix();

	//Õ“Ë‘®«Ý’è
	SetCollisionAttribute(kCollisionAttributeMine);
	//Õ“Ë‘ÎÛ‚ðŽ©•ª‚Ì‘®«ˆÈŠO‚ÉÝ’è
	SetCollisionMask(kCollisionAttributeThier);
}

void Player::Update(Camera* camera, Input* input)
{
	this->input = input;
	IsGetCoin = false;

	//“ü—Í
	InputMovement();

	//ˆÚ“®§ŒÀ
	world.translation.x = max(world.translation.x, -90.f);
	world.translation.x = min(world.translation.x, 90.f);
	world.translation.z = max(world.translation.z, 180.f);
	world.translation.z = min(world.translation.z, 240.f);

	//c‰ñ“]
	world.rotation.x += XMConvertToRadians(20.f);


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
		IsGetCoin = true;
		return ;
	}
}

void Player::InputMovement()
{
	//ƒvƒŒƒCƒ„[
	if(input->Push(DIK_LEFT)){
		world.translation.x -= 2.f;
	}
	else if(input->Push(DIK_RIGHT)){
		world.translation.x += 2.f;
	}


	if(input->Push(DIK_UP)){
		world.translation.z += 2.f;
	}
	else if(input->Push(DIK_DOWN)){
		world.translation.z -= 2.f;
	}
}
