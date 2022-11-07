#pragma once
#include "2D/BaseSprite.h"
#include "Window.h"

class ScoreSprite : public BaseSprite
{
public:
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

	void Finalize() override;

	bool GetIsDead() const {return IsDead;}

	//3D->2D�ϊ�
	Vector2 ChangeTransformation(Vector3 targetpos);

private:
	//�t�F�[�h�A�E�g
	void FadeOut();

	//�x�N�g��*�s��
	Vector3 Vector3Transform( Vector3 &v,  DirectX::XMMATRIX &m);

private:
	Window* window = nullptr;

	//�������e���畽�s���e�ύX
	DirectX::XMMATRIX matView;
	DirectX::XMMATRIX matViewProjection;

	//���Ŏ���
	float time = 0.f;
	const float InvisibleTime = 1.0f;

	//�F
	float alpha = 1.f;
};

