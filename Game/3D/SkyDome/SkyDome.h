#pragma once
#include "3D/BaseObjects.h"
class SkyDome : public BaseObjects
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
	void Update(Camera* camera);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 後処理
	/// </summary>
	void Finalize() override;

	bool GetIsDead() const {return IsDead;}

	//Setter
	void SetVector3(Vector3 position)	{world.translation = position;}
};

