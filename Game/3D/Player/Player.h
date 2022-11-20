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
	void Update(Camera* camera, Input* input = nullptr);


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
	bool GetIsAccelerator()const {return IsAccelerator;}
	float GetDeadAnimSp() {return (DeadAnimSp/AnimNormalSp);}

	float GetMaxAcceleratorGage()	{return AcceleratorGageMax;}
	float GetAcceleratorGage()	{return acceleratorGage;}

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

	/// <summary>
	/// 死亡
	/// </summary>
	void Dead();

	/// <summary>
	/// アクセル
	/// </summary>
	void InputAccelerator();

#ifdef _DEBUG

#endif // _DEBUG


//定数
private:
	//体力、ダメージリターン
	const float ReturnTime = 2.f;
	static const int MaxHp = 3;

	//アニメーション速度
	const float AnimNormalSp = 10.f;
	const float AnimMaxSp = 15.f;
	const float AnimMinSp = 5.f;

	//移動速度
	const float NormalMoveSp = 4.f;
	const float MaxMoveSp = 6.f;

	//移動回転
	const float NormalRotSp = DirectX::XMConvertToRadians(1.f);
	const float MaxRotSp = DirectX::XMConvertToRadians(2.5f);

	//加速
	//ゲージ
	const float AcceleratorGageMax = 10.f;
	//視野角
	const float AcceleratorCameraAngle = 70.f;

//メンバ変数
private:
	Input* input = nullptr;

	//Hp
	std::unique_ptr<PlayerHp> playerHp[MaxHp];

	//移動速度
	float MoveSp = NormalMoveSp;
	//回転(絶対値)
	float MaxRadian = DirectX::XMConvertToRadians(45.f);
	float rotEaseTime = 0.f;
	float RotSp = NormalRotSp;

	//サイズ
	float width = 5;
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
	float DeadAnimSp = AnimNormalSp;

	//HP
	int Hp = MaxHp;

	//ダメージ
	bool IsDamage = false;
	float returnTime = 0.f;

	//死亡
	bool IsDead = false;
	float time = 0.f;

	//ゴール
	bool IsGoal = false;

	//加速
	bool IsAccelerator = false;
	//加速ゲージ
	float acceleratorGage = 0.f;
};

