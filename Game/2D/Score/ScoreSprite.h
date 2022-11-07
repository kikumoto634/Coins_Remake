#pragma once
#include "2D/BaseSprite.h"

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
};

