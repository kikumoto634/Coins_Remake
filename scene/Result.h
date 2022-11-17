#pragma once
#include "Sprite.h"

class Result
{
public:
	~Result();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(int texNumber);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update(bool IsGameEnd);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �㏈��
	/// </summary>
	void Finalize();

private:
	Sprite* sprite;
	Vector2 position = {0,0};
	Vector2 size = {100,100};

	bool IsEnd = false;
};

