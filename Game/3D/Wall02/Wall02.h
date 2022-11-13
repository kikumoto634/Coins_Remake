#pragma once
#include "3D/BaseObjects.h"
#include "3D/Collider/Collider.h"
#include "System/HitStop.h"

class Wall02 :public BaseObjects, public Collider
{
//メンバ関数
public:
	~Wall02();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(std::string filePath) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update(Camera* camera, HitStop* hitStop);

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

	//Setter
	void SetVector3(Vector3 position)	{world.translation = position;}
	void SetDepthSp(float Sp)	{DepthSp = Sp;}

private:
	/// <summary>
	/// 移動
	/// </summary>
	void Movement();

//定数
private:
	const float FallTime = 1.0f;//1s ~ 2s

//メンバ変数
private:
	float width = 20;
	float height = 20;
	float depth = 20;
	std::string name = "Wall01";

	float DepthSp = 0.f;

	float fallTime = 0.f;
	bool IsLRFlag = false;//(false:左移動, true:右移動)

	HitStop* hitStop = nullptr;
};

