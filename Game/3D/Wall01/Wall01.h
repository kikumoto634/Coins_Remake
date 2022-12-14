#pragma once
#include "3D/BaseObjects.h"
#include "3D/Collider/Collider.h"
#include "System/HitStop.h"


class Wall01 : public BaseObjects, public Collider
{
//メンバ関数
public:
	~Wall01();

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

	//Setter
	void SetVector3(Vector3 position)	{world.translation = position;}
	void SetDepthSp(float Sp)	{DepthSp = Sp;}

//メンバ変数
private:
	float width = 17;
	float height = 17;
	float depth = 17;
	std::string name = "Wall01";

	float DepthSp = 0.f;

	HitStop* hitStop = nullptr;
};

