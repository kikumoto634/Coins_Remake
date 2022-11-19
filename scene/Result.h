#pragma once
#include "Sprite.h"

class Result
{
public:
	~Result();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(int BackTexNumber, int fonrtexNumber);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update(bool IsGameOver, bool IsGameClear, int scoreValue);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �㏈��
	/// </summary>
	void Finalize();

	//getter
	bool GetIsEnd()	{return IsEnd;}

private:
	//�o�b�N
	Sprite* back = nullptr;
	Vector2 backPosition = {0,0};
	Vector2 backSize = {100,100};

	//�t�H���g
	Sprite* font = nullptr;
	Vector2 fontPosition = {0,0};
	Vector2 fontSize = {100,100};

	//�X�R�A�t�H���g
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

