#pragma once
#include "3D/BaseObjects.h"
#include "3D/Collider/Collider.h"

class Coins : public BaseObjects, public Collider
{
//メンバ関数
public:

	~Coins();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(std::string filePath) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update(Camera* camera);

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

	//Setter
	void SetVector3(Vector3 position)	{world.translation = position;}
	void SetDepthSp(float Sp)	{DepthSp = Sp;}

private:
	float width = 15;
	float height = 15;
	float depth = 15;
	std::string name = "Coin";

	float DepthSp = 0.f;
};

