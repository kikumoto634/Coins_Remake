#pragma once
#include "Sprite.h"
#include "Vector2.h"

class BaseSprite
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize(UINT textureNumber);

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// 後処理
	/// </summary>
	virtual void Finalize();

	//Setter
	void SetVector2(Vector2 position)	{this->position = position;}
	void SetSize(Vector2 size)	{this->size = size;}

protected:
	Sprite* sprite;
	Vector2 position = {0,0};
	Vector2 size = {100,100};

	bool IsDead = false;
};