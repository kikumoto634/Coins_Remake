#pragma once
#include "Sprite.h"

class Result
{
public:
	~Result();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(int texNumber);

	/// <summary>
	/// 更新
	/// </summary>
	void Update(bool IsGameEnd);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 後処理
	/// </summary>
	void Finalize();

private:
	Sprite* sprite;
	Vector2 position = {0,0};
	Vector2 size = {100,100};

	bool IsEnd = false;
};

