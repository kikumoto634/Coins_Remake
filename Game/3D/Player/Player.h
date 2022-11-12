#pragma once
#include "3D/BaseObjects.h"
#include "3D/Collider/Collider.h"

#include "2D/Hp/PlayerHp.h"

#include "Input.h"


class Player : public BaseObjects, public Collider
{
//メンバ関数
public:
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(std::string filePath) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update(Camera* camera, Input* input);


	/// <summary>
	/// 2D描画
	/// </summary>
	void Draw_2D();

	/// <summary>
	/// 3D描画
	/// </summary>
	void Draw_3D();

	/// <summary>
	/// 後処理
	/// </summary>
	void Finalize() override;

	//衝突判定
	void OnCollision(Collider* TouchCollision) override;

	//Getter
	const Vector3 GetPosition() override {return world.translation;}
	const Vector3 GetRotation() {return world.rotation;}

	const float GetWidth() override	{return width;}
	const float GetHeight()	override	{return height;}
	const float GetDepth()	override	{return depth;}
	const std::string GetName() override	{return name;}
	
	int GetHp()	const {return Hp;}
	bool GetIsDead() const {return IsDead;}

	int GetCoinCount() const {return CoinCount;}
	int GetScoreCount() const {return ScoreCount;}
	bool GetIsScoreUp() const {return IsScoreUp;}
	bool GetIsScoreDown() const {return IsScoreDown;}

	//Setter


private:


#pragma region 2D
	void Initialize2D();
	void Update2D();
	void Draw2D();
	void Finalize2D();
#pragma endregion

#pragma region 3D
	void Initialize3D();
	void Update3D();
	void Draw3D();
	void Finalize3D();
#pragma endregion

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
	static const int MaxHp = 3;

//メンバ変数
private:
	Input* input = nullptr;

	//Hp
	std::unique_ptr<PlayerHp> playerHp[MaxHp];


	//移動速度
	float MoveSp = 4.f;
	//回転(絶対値)
	float MaxRadian = DirectX::XMConvertToRadians(45.f);
	float RotSp = DirectX::XMConvertToRadians(1.f);
	float rotEaseTime = 0.f;

	//サイズ
	float width = 10;
	float height = 10;
	float depth = 10;
	std::string name = "Player";

	//コイン、スコア
	int CoinCount = 0;
	int ScoreCount = 0;
	bool IsScoreUp = false;
	bool IsScoreDown = false;

	//アニメーション速度
	float AnimSp = 0.f;
	float AnimNormalSp = 10.f;
	float AnimMaxSp = 15.f;
	float AnimMinSp = 5.f;

	//HP
	int Hp = MaxHp;

	//ダメージ
	bool IsDamage = false;
	float returnTime = 0.f;
};

