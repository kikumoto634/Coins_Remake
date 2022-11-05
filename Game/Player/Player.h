#pragma once
#include "BaseObjects.h"
#include "Input.h"

class Player : BaseObjects
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

	//Getter
	Vector3 GetPos()	{return world.translation;}

	//Setter


private:
	/// <summary>
	/// ���͈ړ�
	/// </summary>
	void InputMovement();

//�����o�ϐ�
private:
	Input* input = nullptr;
};

