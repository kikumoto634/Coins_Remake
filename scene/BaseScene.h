#pragma once
#include "DirectXCommon.h"
#include "Window.h"
#include "Input.h"
#include "Camera.h"

#include "Sprite.h"

#ifdef _DEBUG
#include "SceneStopper.h"
#endif // _DEBUG

class BaseScene
{
//�����o�֐�
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	BaseScene(DirectXCommon* dxCommon, Window* window);

	/// <summary>
	/// �N����
	/// </summary>
	virtual void Application();

	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update();

	/// <summary>
	/// ��X�V
	/// </summary>
	void EndUpdate();

	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// �㏈��
	/// </summary>
	virtual void Finalize();

//�����o�ϐ�
protected:

#pragma region �ėp�@�\
	//�؂����
	DirectXCommon* dxCommon = nullptr;
	Window* window = nullptr;
	
	//�쐬
	Input* input = nullptr;
	Camera* camera = nullptr;
#pragma endregion


#ifdef _DEBUG
	SceneStopper* sceneStopper = nullptr;
#endif // _DEBUG

};

