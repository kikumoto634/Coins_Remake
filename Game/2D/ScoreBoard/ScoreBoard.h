#pragma once
#include "2D/BaseSprite.h"

class ScoreBoard : public BaseSprite
{
public:
	~ScoreBoard();

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
