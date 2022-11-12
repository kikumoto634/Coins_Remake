#pragma once
#include "3D/BaseObjects.h"
#include "3D/Collider/Collider.h"

#include "2D/Hp/PlayerHp.h"

#include "Input.h"


class Player : public BaseObjects, public Collider
{
//�����o�֐�
public:
	~Player();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(std::string filePath) override;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update(Camera* camera, Input* input);


	/// <summary>
	/// 2D�`��
	/// </summary>
	void Draw_2D();

	/// <summary>
	/// 3D�`��
	/// </summary>
	void Draw_3D();

	/// <summary>
	/// �㏈��
	/// </summary>
	void Finalize() override;

	//�Փ˔���
	void OnCollision(Collider* TouchCollision) override;

	//Getter
	const Vector3 GetPosition() override {return world.translation;}
	const Vector3 GetRotation() {return world.rotation;}

	const float GetWidth() override	{return width;}
	const float GetHeight()	override	{return height;}
	const float GetDepth()	override	{return depth;}
	const std::string GetName() override	{return name;}
	
	int GetHp()	const {return Hp;}
	bool GetIsDead() const {return IsDead;}

	int GetCoinCount() const {return CoinCount;}
	int GetScoreCount() const {return ScoreCount;}
	bool GetIsScoreUp() const {return IsScoreUp;}
	bool GetIsScoreDown() const {return IsScoreDown;}

	//Setter


private:


#pragma region 2D
	void Initialize2D();
	void Update2D();
	void Draw2D();
	void Finalize2D();
#pragma endregion

#pragma region 3D
	void Initialize3D();
	void Update3D();
	void Draw3D();
	void Finalize3D();
#pragma endregion

	/// <summary>
	/// ���͈ړ�
	/// </summary>
	void InputMovement();

	/// <summary>
	/// �_���[�W
	/// </summary>
	void Damage();

//�萔
private:
	const float ReturnTime = 2.f;
	static const int MaxHp = 3;

//�����o�ϐ�
private:
	Input* input = nullptr;

	//Hp
	std::unique_ptr<PlayerHp> playerHp[MaxHp];


	//�ړ����x
	float MoveSp = 4.f;
	//��](��Βl)
	float MaxRadian = DirectX::XMConvertToRadians(45.f);
	float RotSp = DirectX::XMConvertToRadians(1.f);
	float rotEaseTime = 0.f;

	//�T�C�Y
	float width = 10;
	float height = 10;
	float depth = 10;
	std::string name = "Player";

	//�R�C���A�X�R�A
	int CoinCount = 0;
	int ScoreCount = 0;
	bool IsScoreUp = false;
	bool IsScoreDown = false;

	//�A�j���[�V�������x
	float AnimSp = 0.f;
	float AnimNormalSp = 10.f;
	float AnimMaxSp = 15.f;
	float AnimMinSp = 5.f;

	//HP
	int Hp = MaxHp;

	//�_���[�W
	bool IsDamage = false;
	float returnTime = 0.f;
};

