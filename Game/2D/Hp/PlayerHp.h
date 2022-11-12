#pragma once
#include "2D/BaseSprite.h"
#include "Window.h"
#include "Camera.h"

class PlayerHp : public BaseSprite
{
public:
	~PlayerHp();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(UINT textureNumber) override;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

	/// <summary>
	/// �㏈��
	/// </summary>
	void Finalize() override;

	//3D->2D�ϊ�
	Vector2 ChangeTransformation(Vector3 targetpos);

	/// <summary>
	/// �t�F�[�h�J�n
	/// </summary>
	void FadeStart()	{IsFade = true;}

	/// <summary>
	/// �j��J�n
	/// </summary>
	void BreakStart()	{IsBreak = true;}


	void IsInvisibleState(bool IsFlag)	{sprite->SetIsInvisible(IsFlag);}

	//Getter
	bool GetIsDead() const {return IsDead;}

	//Setter
	void SetHpNum(int num)	{HeartNum = num;}

private:
	//�t�F�[�h�A�E�g
	void FadeOut();

	//�j��
	void HeartBreak();

	//�x�N�g��*�s��
	Vector3 Vector3Transform( Vector3 &v,  DirectX::XMMATRIX &m);

private:
	Window* window = nullptr;
	Camera* camera = nullptr;

	int HeartNum = 1;

	///�t�F�[�h
	//���Ŏ���
	bool IsFade = false;
	float Fadetime = 0.f;
	const float FadeInvisibleTime = 1.5f;

	//�j��
	bool IsBreak = false;
	float BreakTime = 0.f;
	const float BreakInvisibleTime = 0.75f;
};

