#pragma once
#include "BaseObjects.h"
#include "Collider/Collider.h"
#include "Input.h"

class Player : public BaseObjects, public Collider
{
//�����o�֐�
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(std::string filePath) override;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update(Camera* camera, Input* input);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

	/// <summary>
	/// �㏈��
	/// </summary>
	void Finalize() override;

	//�Փ˔���
	void OnCollision(Collider* TouchCollision) override;

	//Getter
	const Vector3 GetPosition() override {return world.translation;}

	const float GetWidth() override	{return width;}
	const float GetHeight()	override	{return height;}
	const float GetDepth()	override	{return depth;}
	const std::string GetName() override	{return name;}
	
	bool GetIsDead() const {return IsDead;}

	int GetCoinCount() const {return CoinCount;}

	//Setter


private:
	/// <summary>
	/// ���͈ړ�
	/// </summary>
	void InputMovement();

//�����o�ϐ�
private:
	Input* input = nullptr;

	float width = 10;
	float height = 10;
	float depth = 10;
	std::string name = "Player";

	int CoinCount = 0;
};

