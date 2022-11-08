#pragma once
#include "3D/BaseObjects.h"
#include "3D/Collider/Collider.h"
#include "Input.h"

class Player : public BaseObjects, public Collider
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

	//衝突判定
	void OnCollision(Collider* TouchCollision) override;

	//Getter
	const Vector3 GetPosition() override {return world.translation;}

	const float GetWidth() override	{return width;}
	const float GetHeight()	override	{return height;}
	const float GetDepth()	override	{return depth;}
	const std::string GetName() override	{return name;}
	
	bool GetIsDead() const {return IsDead;}

	int GetCoinCount() const {return CoinCount;}
	int GetScoreCount() const {return ScoreCount;}
	bool GetIsScoreUp() const {return IsScoreUp;}
	bool GetIsScoreDown() const {return IsScoreDown;}

	//Setter


private:
	/// <summary>
	/// 入力移動
	/// </summary>
	void InputMovement();

	/// <summary>
	/// ダメージ
	/// </summary>
	void Damage();

//定数
private:
	const float ReturnTime = 2.f;

//メンバ変数
private:
	Input* input = nullptr;

	float width = 10;
	float height = 10;
	float depth = 10;
	std::string name = "Player";

	int CoinCount = 0;
	int ScoreCount = 0;
	bool IsScoreUp = false;
	bool IsScoreDown = false;

	float MoveSp = 2.f;
	float AnimSp = 15.f;

	bool IsDamage = false;
	float returnTime = 0.f;
};

