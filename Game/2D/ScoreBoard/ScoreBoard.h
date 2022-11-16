#pragma once
#include "2D/BaseSprite.h"
#include "Window.h"
#include "Camera.h"

class ScoreBoard : public BaseSprite
{
public:
	~ScoreBoard();

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
};

