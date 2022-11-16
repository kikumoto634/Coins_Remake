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
};

