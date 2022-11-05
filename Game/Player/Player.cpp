#include "Player.h"

void Player::Initialize(std::string filePath)
{
	BaseObjects::Initialize(filePath);

	world.translation = {0,-135,210};
	world.UpdateMatrix();
}

void Player::Update(Camera* camera, Input* input)
{
	this->input = input;

	//入力
	InputMovement();

	//プレイヤー
	world.translation.x = max(world.translation.x, -90.f);
	world.translation.x = min(world.translation.x, 90.f);
	world.translation.z = max(world.translation.z, 135.f);
	world.translation.z = min(world.translation.z, 295.f);

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
}

void Player::InputMovement()
{
	//プレイヤー
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
