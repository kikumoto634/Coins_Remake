#pragma once
#include "2D/BaseSprite.h"

class ScoreSprite : public BaseSprite
{
public:
	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize(UINT textureNumber) override;

	/// <summary>
	/// XV
	/// </summary>
	void Update() override;

	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw() override;

	void Finalize() override;

	bool GetIsDead() const {return IsDead;}
};

