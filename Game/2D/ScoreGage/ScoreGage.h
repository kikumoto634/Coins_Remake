#pragma once
#include "2D/BaseSprite.h"

class ScoreGage : public BaseSprite
{
public:
	~ScoreGage();

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

	//Settter
	void SetGageCurrent(float value)	{current = value;}
	void SetGageMax(float value)	{Max = value;}

private:
	//�Q�[�W
	Sprite* empty = nullptr;
	Sprite* full = nullptr;

	float Max = 1.f;
	float current = 0.f;

	float gageSize = 512.f;
};

