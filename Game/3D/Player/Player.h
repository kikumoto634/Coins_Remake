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
	void Update(Camera* camera, Input* input = nullptr);


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
	bool GetIsAccelerator()const {return IsAccelerator;}
	float GetDeadAnimSp() {return (DeadAnimSp/AnimNormalSp);}

	float GetMaxAcceleratorGage()	{return AcceleratorGageMax;}
	float GetAcceleratorGage()	{return acceleratorGage;}

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

	/// <summary>
	/// ���S
	/// </summary>
	void Dead();

	/// <summary>
	/// �A�N�Z��
	/// </summary>
	void InputAccelerator();

#ifdef _DEBUG

#endif // _DEBUG


//�萔
private:
	//�̗́A�_���[�W���^�[��
	const float ReturnTime = 2.f;
	static const int MaxHp = 3;

	//�A�j���[�V�������x
	const float AnimNormalSp = 10.f;
	const float AnimMaxSp = 15.f;
	const float AnimMinSp = 5.f;

	//�ړ����x
	const float NormalMoveSp = 4.f;
	const float MaxMoveSp = 6.f;

	//�ړ���]
	const float NormalRotSp = DirectX::XMConvertToRadians(1.f);
	const float MaxRotSp = DirectX::XMConvertToRadians(2.5f);

	//����
	//�Q�[�W
	const float AcceleratorGageMax = 10.f;
	//����p
	const float AcceleratorCameraAngle = 70.f;

//�����o�ϐ�
private:
	Input* input = nullptr;

	//Hp
	std::unique_ptr<PlayerHp> playerHp[MaxHp];

	//�ړ����x
	float MoveSp = NormalMoveSp;
	//��](��Βl)
	float MaxRadian = DirectX::XMConvertToRadians(45.f);
	float rotEaseTime = 0.f;
	float RotSp = NormalRotSp;

	//�T�C�Y
	float width = 5;
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
	float DeadAnimSp = AnimNormalSp;

	//HP
	int Hp = MaxHp;

	//�_���[�W
	bool IsDamage = false;
	float returnTime = 0.f;

	//���S
	bool IsDead = false;
	float time = 0.f;

	//�S�[��
	bool IsGoal = false;

	//����
	bool IsAccelerator = false;
	//�����Q�[�W
	float acceleratorGage = 0.f;
};

