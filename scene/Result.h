#pragma once
#include "Sprite.h"

class Result
{
public:
	~Result();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(int BackTexNumber, int fonrtexNumber);

	/// <summary>
	/// 更新
	/// </summary>
	void Update(bool IsGameOver, bool IsGameClear, int scoreValue);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 後処理
	/// </summary>
	void Finalize();

	//getter
	bool GetIsEnd()	{return IsEnd;}

private:
	//バック
	Sprite* back = nullptr;
	Vector2 backPosition = {0,0};
	Vector2 backSize = {100,100};

	//フォント
	Sprite* font = nullptr;
	Vector2 fontPosition = {0,0};
	Vector2 fontSize = {100,100};

	//スコアフォント
	static const int Num = 9;
	Sprite* scoreNumber[Num];
	Vector2 fontNumberPosition[Num];
	Vector2 fontNumberSize[Num];
	int score = 0;

	//pressZ
	Sprite* pressFont = nullptr;
	Vector2 pressFontPosition = {0,0};
	Vector2 pressFontSize = {100,100};

	bool IsEnd = false;

	float alpha = 0.f;
};

