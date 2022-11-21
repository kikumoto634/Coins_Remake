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

	//�Փˑ����ݒ�
	SetCollisionAttribute(kCollisionAttributeMine);
	//�ՓˑΏۂ������̑����ȊO�ɐݒ�
	SetCollisionMask(kCollisionAttributeThier);
}

void Player::Update(Camera* camera, Input* input)
{
	if(input != nullptr)this->input = input;
	this->camera = camera;

	Update2D();
	Update3D();

#ifdef _DEBUG
	if(input != nullptr && input->Trigger(DIK_7)){
		acceleratorGage = AcceleratorGageMax;
	}
#endif // _DEBUG

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
		if(!IsAccelerator)		acceleratorGage += 0.4f;
		else if(IsAccelerator)  acceleratorGage += 0.2f;
		acceleratorGage = min(acceleratorGage, AcceleratorGageMax);
		IsScoreUp = true;
		return ;
	}
	else if(TouchCollision->GetName() == "Wall01"){
		if(IsAccelerator) {
			ScoreCount += 100;
			acceleratorGage += 0.1f;
			acceleratorGage = min(acceleratorGage, AcceleratorGageMax);
			IsScoreUp = true;
			return;
		}
		ScoreCount -= 100;
		IsScoreDown = true;
		Hp -= 1;
		IsDamage = true;
		return ;
	}
	else if(TouchCollision->GetName() == "Goal"){
		IsGoal = true;
	}
}

#pragma region _2D����
void Player::Initialize2D()
{
	for(int i = 0; i < MaxHp; i++){
		playerHp[i] = std::make_unique<PlayerHp>();
		playerHp[i]->Initialize(4);
	}
}

void Player::Update2D()
{
	//�X�R�A
	IsScoreUp = false;
	IsScoreDown = false;

	//�̗�
	for(int i = 0; i < Hp; i++){
		playerHp[i]->Update();
		playerHp[i]->SetVector2(playerHp[i]->ChangeTransformation(Vector3(world.translation.x +i*20-20, world.translation.y+30, world.translation.z)));
	}
}

void Player::Draw2D()
{
	//�̗�
	for(int i = 0; i < Hp; i++){
		playerHp[i]->Draw();
	}
}

void Player::Finalize2D()
{
	//�̗�
	for(int i = 0; i < MaxHp; i++){
		playerHp[i]->Finalize();
	}
}
#pragma endregion

#pragma region _3D����
void Player::Initialize3D()
{
	AnimSp = AnimNormalSp;

	world.translation = {0,-131,200};
	world.UpdateMatrix();
}

void Player::Update3D()
{
	//���S
	Dead();
	if(IsDead) return;

	//����
	InputMovement();
	//����
	InputAccelerator();
	if(!IsAccelerator && camera->GetIniAngle() != camera->GetAngle()){
		camera->AngleMove(camera->GetIniAngle());
	}

	//�_���[�W
	Damage();

	//�c��]
	if(world.rotation.x >= XMConvertToRadians(360.f-AnimSp)) world.rotation.x = 0.f;
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
	if(!input) return;
	if(IsGoal) {
		acceleratorGage = AcceleratorGageMax;
		return;
	}

	//�ړ�����
	world.translation.x = max(world.translation.x, -90.f);
	world.translation.x = min(world.translation.x, 90.f);
	world.translation.z = max(world.translation.z, 120.f);
	world.translation.z = min(world.translation.z, 300.f);

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

	//Hp�\��
	for(int i = 0; i < Hp; i++){
		playerHp[i]->FadeStart();
	}
}

void Player::Dead()
{
	if(Hp <= 0) IsDead = true;

#ifdef _DEBUG

	if(input != nullptr && input->Trigger(DIK_6)){
		IsDead = true;
	}

#endif // _DEBUG

	if(!IsDead) return;

	if(DeadAnimSp <= 0.f) {
		world.rotation.x = XMConvertToRadians(360);
		world.rotation.y = XMConvertToRadians(90.f);
		world.rotation.z = XMConvertToRadians(90.f);
		return;
	}
	DeadAnimSp -= 1.f/25;

	if(time >= 1.f) return;
	time += 0.01f;
	world.rotation.x = (1-time)*XMConvertToRadians(world.rotation.x) + (time)*XMConvertToRadians(360);
	world.rotation.y = (1-time)*XMConvertToRadians(world.rotation.y) + (time)*XMConvertToRadians(90.f);
	world.rotation.z = (1-time)*XMConvertToRadians(world.rotation.z) + (time)*XMConvertToRadians(90.f);
}

void Player::InputAccelerator()
{
	if(!input) return;

	if(input->Trigger(DIK_Z)){
		IsAccelerator = true;
	}

	if(!IsAccelerator) return;

	camera->AngleMove(AcceleratorCameraAngle);
	acceleratorGage -= 1.f/60;
	AnimSp = AnimMaxSp;
	MoveSp = MaxMoveSp;
	RotSp = MaxRotSp;

	if(acceleratorGage <= 0){
		IsAccelerator = false;
		acceleratorGage = 0.f;
		AnimSp = AnimNormalSp;
		MoveSp = NormalMoveSp;
		RotSp = NormalRotSp;
	}
}
