#pragma once
#include "BaseObjects.h"
#include "Input.h"

class Player : BaseObjects
{
//メンバ関数
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(std::string filePath) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update(Camera* camera, Input* input);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 後処理
	/// </summary>
	void Finalize() override;

	//Getter
	Vector3 GetPos()	{return world.translation;}

	//Setter


private:
	/// <summary>
	/// 入力移動
	/// </summary>
	void InputMovement();

//メンバ変数
private:
	Input* input = nullptr;
};

