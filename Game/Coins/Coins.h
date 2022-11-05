#pragma once
#include "BaseObjects.h"

class Coins : BaseObjects
{
//ƒƒ“ƒoŠÖ”
public:
	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize(std::string filePath) override;

	/// <summary>
	/// XV
	/// </summary>
	void Update(Camera* camera) override;

	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw() override;

	/// <summary>
	/// Œãˆ—
	/// </summary>
	void Finalize() override;
};

