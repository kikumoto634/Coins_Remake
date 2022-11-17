#pragma once
#include "Sprite.h"

class Result
{
public:
	~Result();

	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize(int texNumber);

	/// <summary>
	/// XV
	/// </summary>
	void Update(bool IsGameEnd);

	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw();

	/// <summary>
	/// Œãˆ—
	/// </summary>
	void Finalize();

private:
	Sprite* sprite;
	Vector2 position = {0,0};
	Vector2 size = {100,100};

	bool IsEnd = false;
};

