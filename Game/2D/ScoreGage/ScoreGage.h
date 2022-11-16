#pragma once
#include "2D/BaseSprite.h"

class ScoreGage : public BaseSprite
{
public:
	~ScoreGage();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(UINT textureNumber) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	void Finalize() override;
};

