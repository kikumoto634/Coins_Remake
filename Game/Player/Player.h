#pragma once
#include "FbxModelManager.h"
#include "FbxModelObject.h"
#include "WorldTransform.h"
#include "Vector3.h"

#include "Camera.h"
#include "Input.h"

class Player
{
//�����o�֐�
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	
	/// <summary>
	/// �X�V
	/// </summary>
	void Update(Camera* camera, Input* input);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �㏈��
	/// </summary>
	void Finalize();

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
	//�v���C���[
	FbxModelManager* model;
	FbxModelObject* object;
	WorldTransform world;

	Camera* camera = nullptr;
	Input* input = nullptr;
};

