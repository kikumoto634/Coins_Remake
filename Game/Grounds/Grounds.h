#pragma once
#include "BaseObjects.h"

class Grounds : public BaseObjects
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

	//Getter
	Vector3 GetPosition()	{return world.translation;}

	//Setter
	void SetVector3(Vector3 position)	{world.translation = position;}
};

